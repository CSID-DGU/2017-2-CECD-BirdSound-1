#pragma once
//#include "scan.h"
#include "device.h"


int main(void) {
	Realsense realsense;
	realsense.init();
	realsense.info(0);
	realsense.startStreaming(0,depth);
	rs2::frame frame = realsense.capture(0, depth);
	realsense.frameToVtkPoints(frame);

	
	realsense.stopStreaming(0, depth);
	cout << "IS IT OK??" << endl;
	
}