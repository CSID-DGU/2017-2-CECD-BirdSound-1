#ifndef DEVICE_H
#define DEVICE_H
#define MAX_CAM_NUM 3
#define MIN_CAM_NUM 0
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
#include "common.h"
#include "libRealsense2\rs.hpp"
#include "vtk-8.1\vtkPoints.h"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <sstream>
#include <map>

enum { color, depth };


using namespace std;

class Realsense {

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
	
private:
	bool isInit();
	void Realsense::restFrame(unit &cam_unit, int num);
	
};

#endif