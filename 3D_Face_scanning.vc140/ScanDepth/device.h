#ifndef DEVICE_H
#define DEVICE_H

#include "common.h"
#include "libRealsense2\rs.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
enum { color, depth };

using namespace std;

class Realsense {
	uint32_t deviceNum = NULL;
	rs2::device_list deviceList;
public:
	void init();
	void info(int);
	void startStreaming(int, int);
	void stopStreaming();
	void capture();
private:
	bool isInit();
};

#endif