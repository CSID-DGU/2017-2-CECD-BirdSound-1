#pragma once
#undef foreach
#undef Q_FOREACH


#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);


#include<vtkPoints.h>
#include<vtkOBJExporter.h>
#include<librealsense2\rs.hpp>
#include <iomanip>

#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkInteractorStyle.h>
#include<vtkCellArray.h>
#include<vtkPolyData.h>
#include<vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include<vtkimageData.h>
#include<vtkImageViewer2.h>

#include"vtkSTLWriter.h"
#include<string>

#include <utility>
#include <cstdint>

#include"../DepthModule/device.h"
#include"MeshPreview.h"
#include"DepthMapPreviewer.h"


#include"vtkImageMapper3D.h"

#include"vtkImageMedian3D.h"
#include"vtkImageActor.h"
#include"vtkImageGaussianSmooth.h"
#include"vtkSmoothPolyDataFilter.h"


#include<vector>
#include<omp.h>

enum { color, depth };
enum { omp, ompNsimd, serial };


class Scan
{
private:
	const int width = 1280;
	const int height = 720;
	const int INF = 999999999;
	std::vector<rs2::frame> frames;

public:

	void InsertFrame( rs2::frame &frame)
	{
		frames.push_back(frame);
	}

	~Scan()
	{
		if(points !=NULL && points!=nullptr)	
			points->Delete();
		points = NULL;
		frames.clear();
	}
	Scan()
	{
		points = nullptr;
	}

	void frames2Points();
	void frames2PointsCutOutlier();
	std::string saveImage(rs2::frame &frame, std::string filepath, int filetype){}

	void frame2Points(const rs2::frame& frame);

	/*mode0 : omp  mode1 : omp with simd   else serial*/
	void MeshConstruction(MeshPreview *viewer,int mode, int saveType, int ThreadSize = 4);

	/*
	texture를 MeshPreview에 저장하는 부분. fra에 파라미터로 rgb frame을 넣으면 된다. 
	*/
	void ScanTexture(MeshPreview *viewer, rs2::frame &fra)
	{
		


		double dimensions[3] = { 1280, 720, 1 };
		const int nComponents = viewer->m_ImageData->GetNumberOfScalarComponents();
		int nScalar = dimensions[2] * dimensions[1] * dimensions[0] * nComponents;

		viewer->m_ImageData->SetDimensions(dimensions[0], dimensions[1], dimensions[2]);
		viewer->m_ImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
		viewer->m_IsTexture = 1;
		viewer->m_ImageData->Modified();


		const unsigned char* data = static_cast<const unsigned char*>(fra.get_data());
		unsigned char* scalarPointer = static_cast<unsigned char*>(viewer->m_ImageData->GetScalarPointer(0, 0, 0));

		for (int i = 0; i < nScalar; i++)
		{
			scalarPointer[i] = data[i];
		}

		//viewer->m_Renderer->ResetCamera();
	}
	void printDepthMap(DepthMapPreviewer *viewer, realsense::Device* device, realsense::RS_400_STREAM_TYPE type);
	void ReleaseModel()
	{
		
		if (points != NULL && points!=nullptr)
		{
			points->Delete();
			points=NULL;
		}

		points = vtkPoints::New();
		frames.clear();

	}
	void Delete()
	{
		points->Delete();
		points = NULL;
		frames.clear();
	}

	/*
	사실 Filter class를 따로 구성하는것도 좋을 것 같음.
	*/
	void gaussianRad(DepthMapPreviewer *viewer, double rad)
	{
		vtkImageGaussianSmooth *gaus = vtkImageGaussianSmooth::New();
		gaus->SetInputData(viewer->GetImageData());
		gaus->SetRadiusFactor(rad);
		gaus->Update();

		viewer->m_ImageData->DeepCopy(gaus->GetOutput());
		viewer->m_ImageData->Modified();


		viewer->GetActor()->GetMapper()->SetInputConnection(gaus->GetOutputPort());
		//viewer->GetActor()->Modified();

		viewer->GetRenderWindow()->Modified();
		viewer->GetRenderWindow()->Render();
	}

	void gaussianStd(DepthMapPreviewer *viewer, double std)
	{
		vtkImageGaussianSmooth *gaus = vtkImageGaussianSmooth::New();
		gaus->SetInputData(viewer->GetImageData());
		gaus->SetStandardDeviation(std);
		gaus->Update();

		viewer->m_ImageData->DeepCopy(gaus->GetOutput());
		viewer->m_ImageData->Modified();


		viewer->GetActor()->GetMapper()->SetInputConnection(gaus->GetOutputPort());

		viewer->GetRenderWindow()->Modified();
		viewer->GetRenderWindow()->Render();
	}
	

	void imageMedian3D(DepthMapPreviewer *viewer, int value)
	{
		auto temp = viewer->GetImageData()->GetScalarPointer();
		unsigned short * _value = static_cast<unsigned short*>(temp);
		vtkImageMedian3D *Median2D = vtkImageMedian3D::New();


		Median2D->SetInputData(viewer->GetOriginImage());//얘는 원본 이미지로 할 것.
		Median2D->SetKernelSize(value, value, value);
		Median2D->Update();

		viewer->m_ImageData->DeepCopy(Median2D->GetOutput());
		viewer->m_ImageData->Modified();

		viewer->GetActor()->GetMapper()->SetInputConnection(Median2D->GetOutputPort());
		viewer->GetActor()->Modified();

		viewer->GetRenderWindow()->Modified();
		viewer->GetRenderWindow()->Render();
		Median2D->Delete();
	}


	void meshSmooth(MeshPreview *viewer, double Relaxation)
	{
		vtkSmoothPolyDataFilter* smoothFilter =vtkSmoothPolyDataFilter::New();
		smoothFilter->SetInputData(viewer->GetPolyDataAt(0));
		smoothFilter->SetNumberOfIterations(100);
		smoothFilter->SetRelaxationFactor(Relaxation);
		smoothFilter->FeatureEdgeSmoothingOff();
		smoothFilter->BoundarySmoothingOn();
		smoothFilter->Update();

		//viewer->GetRenderer()->RemoveActor(viewer->GetActorAt(0));
		//viewer->GetActorAt(0)->Delete();
		//viewer->GetActorAt(0) = vtkActor::New();

		//viewer->GetMapperAt(0)->Delete();
		//viewer->GetMapperAt(0) = vtkPolyDataMapper::New();

		//viewer->GetPolyDataAt(0)->ReleaseData();
		//viewer->GetPolyDataAt(0)->Delete();
		//viewer->GetPolyDataAt(0) = vtkPolyData::New();

		viewer->GetMapperAt(0)->SetInputData(smoothFilter->GetOutput());
		viewer->GetActorAt(0)->SetMapper(viewer->GetMapperAt(0));
		viewer->GetActorAt(0)->Modified();
		viewer->GetRenderWindow()->Modified();
		viewer->Rendering();
	}
	void upDataPoint(DepthMapPreviewer *viewer)
	{
		//auto temp= viewer->GetActor()->GetInput()->GetScalarPointer();
		auto pointer= viewer->GetImageData()->GetScalarPointer();

		unsigned short* value = static_cast<unsigned short*>(pointer);

		for (int i = 0; i < 1280*720; i++)
		{
			double orig[3];
			points->GetPoint(i, orig);
			double val = double(value[i]) / (8*1024.0);
			//std::cout << val << " ";			
			if (val == 0|| val<-1.0 || val>1.0)
				points->SetPoint(i, 0, 0, 0);

			else
				points->SetPoint(i, orig[0], orig[1], val);
		}
		
	}
	vtkPoints* GetPoints()		 { return points; }
private:
	vtkPoints *points;
	vtkRenderer* MeshConstruct(MeshPreview *viewer, vtkPoints *point, int saveType);
	double getDistane(double *src, double *tar);
	void cellInsert(vtkCellArray *cell, int number, long long index1, long long index2, long long index3, long long disp=0);
	void MeshConstructWithOMP(MeshPreview *viewer,vtkPoints *point, int saveType, int ThreadSize);
	vtkRenderer* MeshConstructWithOMPnSIMD(MeshPreview *viewer,vtkPoints *point, int saveType, int ThreadSize);
};