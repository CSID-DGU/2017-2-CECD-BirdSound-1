#ifndef DEVICE_H
#define DEVICE_H
#define MAX_CAM_NUM 3
#define MIN_CAM_NUM 0
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

#include "common.h"
#include "libRealsense2\rs.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <sstream>
#include <map>
#include<vtkPoints.h>
#include"vtkRenderWindow.h"
#include"vtkRenderer.h"
#include<vtkCellArray.h>
#include<vtkPolyData.h>
#include<vtkPolyDataMapper.h>

#include <vtkCamera.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkInteractorStyle.h>
#include"vtkSphereSource.h"
#include"vtkSTLWriter.h"
#include"vtkOBJExporter.h"
#include<omp.h>
#include<stdio.h>


#include <vtkImageData.h>
#include <vtkImageViewer2.h>


#include<fstream>
#include<vector>
#include<regex>
enum { color, depth };


using namespace std;

class Realsense {

	enum class filetype{stl,obj};
	typedef struct unit
	{
		std::map<int, rs2::frame> frames_per_stream;
		rs2::pipeline pipe;
		rs2::pipeline_profile profile;
	} unit;
	uint32_t deviceNum = NULL;
	rs2::device_list deviceList;
	std::map <int, unit> pipe_map;

public:
	void init();
	void info(int);
	void startStreaming(int, int);
	void stopStreaming(int, int);
	rs2::frame Realsense::capture(int devNum, int streamType, int restNum = 10);
	std::vector<rs2::frame> Realsense::capture(int devNum, int streamType, int frameNum, int restNum = 10);
	std::string Realsense::saveImage(rs2::frame &frame, string filepath, int filetype);
	vtkPoints* Realsense::frameToVtkPoints(rs2::frame &frame);
	
	
	/*1이면 stl 2면 obj로 저장*/
	void MeshConstruct(vtkPoints *points, int saveType = 3);
	/*save부분 미구현 추가할 것*/
	void MeshConstructWithOMP(vtkPoints *point, int saveType=3, int ThreadSize=4);
	void MeshConstructWithOMPnSIMD(vtkPoints *point, int saveType = 3, int ThreadSize = 4);
	void viewRawStream();

private:
	bool isInit();
	void restFrame(unit &cam_unit, int num);

private:
	const double INF = 99999999999;
	const int height = 720;
	const int width = 1280;

	double getDistane(double *src, double *tar);
	/*disp는 변위를 의미*/
	void cellInsert(vtkCellArray *cell, int number, int index1, int index2, int index3,int disp=0);
};

#endif