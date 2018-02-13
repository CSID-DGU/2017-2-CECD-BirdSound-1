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

	Scan()
	{
		points = nullptr;
	}
	/**
	input				frames 
	op					frame
	*/
	void frames2Points()
	{
		if (points == nullptr)
		{
			points = vtkPoints::New();
		}

		rs2::pointcloud pc;
		rs2::points rsPoints;
		std::vector<const rs2::vertex*> ver;

		for (int i = 0; i < frames.size(); i++)
		{
			rsPoints = pc.calculate(frames[i]);
			ver.push_back(rsPoints.get_vertices());
		}

		for (int j = 0; j < 1280 * 720; j++)
		{
			int cnt = 0;
			double X, Y, Z;
			X = Y = Z=0;

			for (int i = 0; i < frames.size(); i++)
			{
				if (ver[i][j].z != 0 && ver[i][j].z < 1 && ver[i][j].z > -1)
				{
					X += ver[i][j].x;
					Y += ver[i][j].y;
					Z += ver[i][j].z;
					cnt++;
				}			
			}
			
			if(cnt==0)
				points->InsertNextPoint(0, 0, 0);
			else
			{
				X /= cnt; Y /= cnt; Z /= cnt;
				points->InsertNextPoint(X, Y, Z);
			}
		}
	
		ver.clear();
		frames.clear();

	}



	
	void frames2PointsCutOutlier()
	{
		if (points == nullptr)
		{
			points = vtkPoints::New();
		}

		rs2::pointcloud pc;
		rs2::points rsPoints;
		std::vector<const rs2::vertex*> ver;

		for (int i = 0; i < frames.size(); i++)
		{
			rsPoints = pc.calculate(frames[i]);
			ver.push_back(rsPoints.get_vertices());
		}

		for (int j = 0; j < 1280 * 720; j++)
		{

			std::vector<double> X, Y, Z;
			for (int i = 0; i < frames.size(); i++)
			{
				if (ver[i][j].z != 0 && ver[i][j].z < 1 && ver[i][j].z > -1)
				{
					X.push_back(ver[i][j].x);
					Y.push_back(ver[i][j].y);
					Z.push_back(ver[i][j].z);
				}
			}

			double _X, _Y, _Z;
			_X = _Y = _Z = 0;

			std::sort(X.begin(),X.end());
			std::sort(Y.begin(), Y.end());
			std::sort(Z.begin(), Z.end());

			int cnt = 0;
			for (int i = X.size()*0.3; i < X.size()*0.7; i++)
			{
				_X += X[i];
				_Y += Y[i];
				_Z += Z[i];
				cnt++;
			}
			if (cnt <= 1)
				points->InsertNextPoint(0, 0, 0);
			else
			{
				_X /= cnt; _Y /= cnt; _Z /= cnt;
				points->InsertNextPoint(_X, _Y, _Z);
			}

			X.clear(); Y.clear(); Z.clear();

			//std::cout << j << " ";
		}

		ver.clear();
		frames.clear();

	}
	std::string saveImage(rs2::frame &frame, std::string filepath, int filetype){
	}

	
	void frame2Points(const rs2::frame& frame);

	/*mode0 : omp  mode1 : omp with simd   else serial*/
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