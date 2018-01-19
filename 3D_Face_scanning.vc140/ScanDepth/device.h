#ifndef DEVICE_H
#define DEVICE_H
#define MAX_CAM_NUM 3
#define MIN_CAM_NUM 0
#include "common.h"
#include "libRealsense2\rs.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
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
	void capture(int,int);
private:
	bool isInit();
	
};

#endif