#pragma once
#undef foreach
#undef Q_FOREACH


#include "vtkAutoInit.h" 
//VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
//VTK_MODULE_INIT(vtkInteractionStyle);


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
//#include"DepthMapPreviewer.h"


#include"vtkImageMapper3D.h"

#include"vtkImageMedian3D.h"
#include"vtkImageActor.h"
#include"vtkImageGaussianSmooth.h"
#include"vtkSmoothPolyDataFilter.h"


#include<vector>
#include<omp.h>
#include<vtkFloatArray.h>


#include<math.h>
#include<vtkPointData.h>
#include<vtkPoints.h>
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

	void InsertFrame(rs2::frame &frame)
	{
		frames.push_back(frame);
	}

	~Scan()
	{
		if (points != NULL && points != nullptr)
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
	std::string saveImage(rs2::frame &frame, std::string filepath, int filetype) {}

	void frame2Points(const rs2::frame& frame);

	/*mode0 : omp  mode1 : omp with simd   else serial*/
	void MeshConstruction(MeshPreview *viewer, int mode, int saveType, int ThreadSize = 4);

	/*
	get texture
	*/
	void ScanTexture(MeshPreview *viewer, rs2::frame &fra)
	{
		const unsigned char* data = static_cast<const unsigned char*>(fra.get_data());
		double dimensions[3] = { 1280, 720, 1 };//이런거 4장이다.
			
		pc.map_to(fra);
		
		auto texCord = rsPoints.get_texture_coordinates();
		const int nComponents = 3;
		int nScalar = dimensions[0] * dimensions[1] * dimensions[2] * nComponents;

		int index = 0;
		int arrdisp[] = {	0 * 1280 * 720 / 4, 
							1 *	1280 * 720 / 4, 
							2 * 1280 * 720 / 4, 
							3 * 1280 * 720 / 4 };

		vtkSmartPointer<vtkFloatArray> textureCoordinates[4];
		for (int i = 0; i < 4; i++)
		{
			textureCoordinates[i] = vtkFloatArray::New();
			viewer->m_ImageData[i]->SetDimensions(dimensions[0], dimensions[1]/4, dimensions[2]);
			viewer->m_ImageData[i]->AllocateScalars(VTK_UNSIGNED_CHAR, nComponents);
			viewer->m_ImageData[i]->Modified();
			
			unsigned char* scalarPointer = static_cast<unsigned char*>(viewer->m_ImageData[i]->GetScalarPointer());

			std::cout << index << "에서 ";
			for (int j = 0; j < nScalar/4; j++)
			{
				scalarPointer[j] = data[index++];
			}
			std::cout << index << "까지\n";
			viewer->m_ImageData[i]->Modified();
			
			
			textureCoordinates[i]->SetNumberOfComponents(2);

			//vtkPoints *po = viewer->GetPolyDataAt(i)->GetPoints();
			
			for (int j = 0; j < 1280*720/4; j++)
			{
				float tuple[] = { texCord[arrdisp[i] + j].u, texCord[arrdisp[i] + j].v,0.0f };
				textureCoordinates[i]->InsertNextTuple(tuple);
			}
			textureCoordinates[i]->Modified();

			viewer->GetPolyDataAt(i)->GetPointData()->SetTCoords(textureCoordinates[i]);
			viewer->GetTextureAt(i)->SetInputData(viewer->GetImageData(i));
			viewer->GetTextureAt(i)->Modified();
			viewer->GetActorAt(i)->SetTexture(viewer->GetTextureAt(i));
			viewer->GetTextureAt(i)->Update();
			viewer->GetRenderWindow()->Modified();


			
		}



		//boundary actor
		/*viewer->m_ImageData[4]->SetDimensions(dimensions[0], 6, dimensions[2]);
		viewer->m_ImageData[4]->AllocateScalars(VTK_UNSIGNED_CHAR, nComponents);
		viewer->m_ImageData[4]->Modified();

		unsigned char* scalarPointer = static_cast<unsigned char*>(viewer->m_ImageData[4]->GetScalarPointer());

		std::cout << index << "에서 ";

		int index2 = 0;
		for (int i = 203400;i<=203400*3; i+=203400)
		{
			std::cout << index2 << "에서 ";
			for (int j = 0; j < 1280 * 2*3; j++)
			{
				scalarPointer[index2++] = data[j+ i];
			}
			std::cout << index2 << "까지\n";
		}
		std::cout << index << "까지\n";
		viewer->m_ImageData[4]->Modified();

		vtkSmartPointer<vtkFloatArray> textureCoordinates = vtkSmartPointer<vtkFloatArray>::New();
		textureCoordinates->SetNumberOfComponents(2);

		for (int i = 203400; i <= 203400 * 3; i += 203400)
		{
			
			for (int j = 0; j < 1280 * 2; j++)
			{
				float tuple[] = { texCord[j + i].u, texCord[j + i].v,0.0f };
				textureCoordinates->InsertNextTuple(tuple);
			}
		
		}
		textureCoordinates->Modified();

		viewer->GetPolyDataAt(4)->GetPointData()->SetTCoords(textureCoordinates);
		viewer->GetTextureAt(4)->SetInputData(viewer->GetImageData(4));
		viewer->GetTextureAt(4)->Modified();
		viewer->GetActorAt(4)->SetTexture(viewer->GetTextureAt(4));
		viewer->GetTextureAt(4)->Update();
		viewer->GetRenderWindow()->Modified();*/

	


		vtkRenderer *rend = vtkRenderer::New();
		vtkImageActor *act = vtkImageActor::New();
		act->SetInputData(viewer->m_ImageData[0]);
		act->Update();
		
		vtkRenderWindow *win = vtkRenderWindow::New();
		vtkRenderWindowInteractor *it = vtkRenderWindowInteractor::New();
		rend->ResetCamera();
		rend->AddActor(act);
		
		win->AddRenderer(rend);
		win->Start();
		it->SetRenderWindow(win);
		it->Start();
		viewer->m_Renderer->ResetCamera();
	}
	//void printDepthMap(DepthMapPreviewer *viewer, realsense::Device* device, realsense::RS_400_STREAM_TYPE type);
	void ReleaseModel()
	{

		if (points != NULL && points != nullptr)
		{
			points->Delete();
			points = NULL;
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

	/*poly data 이렇게 그냥 두면 메모리 세지 않나?*/
	void meshSmooth(MeshPreview *viewer, double Relaxation)
	{
		for (int i = 0; i < 4; i++) 
		{
			std::cout << i << " ";
			vtkSmoothPolyDataFilter* smoothFilter = vtkSmoothPolyDataFilter::New();
			smoothFilter->SetInputData(viewer->GetPolyDataAt(i));
			smoothFilter->SetNumberOfIterations(5);
			smoothFilter->SetRelaxationFactor(Relaxation);
			smoothFilter->FeatureEdgeSmoothingOff();
			smoothFilter->BoundarySmoothingOn();
			smoothFilter->Update();

			//viewer->GetRenderer()->RemoveActor(viewer->GetActorAt(0));
			//viewer->GetActorAt(0)->Delete();
			//viewer->GetActorAt(0) = vtkActor::New();

			//viewer->GetMapperAt(0)->Delete();
			//viewer->GetMapperAt(0) = vtkPolyDataMapper::New();

			/*viewer->GetPolyDataAt(i)->ReleaseData();
			viewer->GetPolyDataAt(i)->Delete();
			viewer->m_PolyData[i] = vtkPolyData::New();*/
			viewer->m_PolyData[i]->DeepCopy(smoothFilter->GetOutput());
			viewer->m_PolyData[i]->Modified();

			viewer->GetMapperAt(i)->SetInputData(viewer->m_PolyData[i]);
			viewer->GetMapperAt(i)->Modified();
		}
		/*기존의 poly Data를 release하고 deepcopy한다.*/
	/*	viewer->GetMapperAt(0)->SetInputData(smoothFilter->GetOutput());
		viewer->GetActorAt(0)->SetMapper(viewer->GetMapperAt(0));
		viewer->GetActorAt(0)->Modified();
		viewer->GetRenderWindow()->Modified();
		viewer->Rendering();*/
	}
	//void upDataPoint(DepthMapPreviewer *viewer)
	//{
	//	//auto temp= viewer->GetActor()->GetInput()->GetScalarPointer();
	//	auto pointer = viewer->GetImageData()->GetScalarPointer();

	//	unsigned short* value = static_cast<unsigned short*>(pointer);

	//	for (int i = 0; i < 1280 * 720; i++)
	//	{
	//		double orig[3];
	//		points->GetPoint(i, orig);
	//		double val = double(value[i]) / (8 * 1024.0);
	//		//std::cout << val << " ";			
	//		if (val == 0 || val<-1.0 || val>1.0)
	//			points->SetPoint(i, 0, 0, 0);

	//		else
	//			points->SetPoint(i, orig[0], orig[1], val);
	//	}

	//}
	vtkPoints* GetPoints() { return points; }
private:
	rs2::pointcloud pc;
	rs2::points rsPoints;
	vtkPoints *points;
	vtkRenderer* MeshConstruct(MeshPreview *viewer, vtkPoints *point, int saveType);
	double getDistane(double *src, double *tar);
	void cellInsert(vtkCellArray *cell, int number, long long index1, long long index2, long long index3, long long disp = 0);
	void MeshConstructWithOMP(MeshPreview *viewer, vtkPoints *point, int saveType, int ThreadSize);

};