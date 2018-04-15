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

	void InsertFrame(rs2::frame &frame)	{frames.push_back(frame);}

	~Scan()
	{
		if (points != NULL && points != nullptr)
			points->Delete();
		points = NULL;
		frames.clear();
	}
	Scan()								{points = nullptr;}

	void frames2Points();
	void frames2PointsCutOutlier();
	std::string saveImage(rs2::frame &frame, std::string filepath, int filetype) {}

	void frame2Points(const rs2::frame& frame);

	/*mode0 : omp  mode1 : omp with simd   else serial*/
	void MeshConstruction(MeshPreview *viewer, int mode, int saveType, int ThreadSize = 4);
	void ScanTexture(MeshPreview *viewer, rs2::frame &fra);
	void ReleaseModel();
	void Delete();

	/*poly data 이렇게 그냥 두면 메모리 세지 않나?*/
	void meshSmooth(MeshPreview *viewer, double Relaxation);

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