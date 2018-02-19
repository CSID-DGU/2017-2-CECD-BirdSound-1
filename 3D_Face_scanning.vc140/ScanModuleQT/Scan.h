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
	void eraseFrame()
	{
		frames.clear();
	}
	void InsertFrame(rs2::frame &frame)
	{
		frames.push_back(frame);
	}

	Scan()
	{
		points = nullptr;
		Viewer = new MeshPreview();
	}

	void frames2Points();
	void frames2PointsCutOutlier();
	std::string saveImage(rs2::frame &frame, std::string filepath, int filetype){}
	void ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize);
	void frame2Points(const rs2::frame& frame);

	/*mode0 : omp  mode1 : omp with simd   else serial*/
	vtkRenderer* MeshConstruction(int mode, int saveType, int ThreadSize = 4);
	void viewRawStream();
	
	void ReleaseModel()
	{
		if (points != NULL)
		{
			points->Reset();
			points->Delete();
			points=NULL;
		}

		points = vtkPoints::New();


		vtkActorCollection *actors;
	


		actors = Viewer->GetRenderer()->GetActors();
		const int NumberOfActors= actors->GetNumberOfItems();
		std::cout << NumberOfActors << "\n";
		for (int i = 0; i<NumberOfActors; i++) 
		{
			std::cout << i << "째 actor삭제 ";
			vtkActor *temp = actors->GetNextActor();
			if (temp != NULL && temp != nullptr)
			{
				std::cout << i << " 완료 \n  ";
				Viewer->GetRenderer()->RemoveActor(temp);
				temp->Delete();
			}
			else std::cout << i << " 실패 \n  ";
		}

		Viewer->GetRenderWindow()->Modified();

	}
	void Delete()
	{
		points->Delete();
		points = NULL;

		Viewer->DestroyVariables();
		Viewer = NULL;
	}

	MeshPreview *Viewer;

private:

	
	vtkPoints *points;
	vtkRenderer* MeshConstruct(vtkPoints *point, int saveType);
	double getDistane(double *src, double *tar);
	void cellInsert(vtkCellArray *cell, int number, long long index1, long long index2, long long index3, long long disp=0);
	vtkRenderer* MeshConstructWithOMP(vtkPoints *point, int saveType, int ThreadSize);
	vtkRenderer* MeshConstructWithOMPnSIMD(vtkPoints *point, int saveType, int ThreadSize);


};