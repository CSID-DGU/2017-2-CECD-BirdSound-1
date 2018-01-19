#pragma once
//#include "scan.h"
#include "device.h"


int main(void) {
	Realsense realsense;
	realsense.init();
	realsense.info(0);
	realsense.startStreaming(0,color);
	realsense.capture(0, color);
	
	
	cout << "" << endl;
	
}