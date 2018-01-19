#pragma once
//#include "scan.h"
#include "device.h"


int main(void) {
	Realsense realsense;
	realsense.init();
	realsense.info(0);
}