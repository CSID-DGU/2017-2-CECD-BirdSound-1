#pragma once

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
	
public:
	Scan()
	{
		points = nullptr;
	}

	
	
	std::string saveImage(rs2::frame &frame, std::string filepath, int filetype){
	}

	/*mode0 : omp  mode1 : omp with simd   else serial*/
	void frame2Points(const rs2::frame& frame);
	void MeshConstruction(int mode, int saveType, int ThreadSize = 4);
	void viewRawStream();


private:
	vtkPoints *points;
	vtkRenderer* MeshConstruct(vtkPoints *point, int saveType);
	double getDistane(double *src, double *tar);
	void cellInsert(vtkCellArray *cell, int number, long long index1, long long index2, long long index3, long long disp=0);
	vtkRenderer* MeshConstructWithOMP(vtkPoints *point, int saveType, int ThreadSize);
	vtkRenderer* MeshConstructWithOMPnSIMD(vtkPoints *point, int saveType, int ThreadSize);

};