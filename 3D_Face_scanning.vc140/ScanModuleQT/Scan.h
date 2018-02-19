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

	void InsertFrame(rs2::frame &frame)
	{
		frames.push_back(frame);
	}

	~Scan()
	{
		Viewer->DestroyVariables();

		delete Viewer;
		if(points !=NULL && points!=nullptr)	
			points->Delete();
		points = NULL;
		frames.clear();
	}
	Scan()
	{
		points = nullptr;
		Viewer = new MeshPreview();
		Viewer->setSize(5);//if omp type parameter is 5, else parameter to nothing or 1
		Viewer->Create3DScene();
	}

	void frames2Points();
	void frames2PointsCutOutlier();
	std::string saveImage(rs2::frame &frame, std::string filepath, int filetype){}
	void ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize);
	void frame2Points(const rs2::frame& frame);

	/*mode0 : omp  mode1 : omp with simd   else serial*/
	void MeshConstruction(int mode, int saveType, int ThreadSize = 4);
	void viewRawStream();
	
	void ReleaseModel()
	{
		
		if (points != NULL && points!=nullptr)
		{
			points->Delete();
			points=NULL;
		}

		points = vtkPoints::New();
	
		Viewer->ReleaseModel();
		Viewer->GetRenderWindow()->Modified();

		frames.clear();

	}
	void Delete()
	{
		points->Delete();
		points = NULL;

		Viewer->DestroyVariables();
		Viewer = NULL;

		frames.clear();
	}

	MeshPreview *Viewer;

private:
	vtkPoints *points;
	vtkRenderer* MeshConstruct(vtkPoints *point, int saveType);
	double getDistane(double *src, double *tar);
	void cellInsert(vtkCellArray *cell, int number, long long index1, long long index2, long long index3, long long disp=0);
	void MeshConstructWithOMP(vtkPoints *point, int saveType, int ThreadSize);
	vtkRenderer* MeshConstructWithOMPnSIMD(vtkPoints *point, int saveType, int ThreadSize);


};