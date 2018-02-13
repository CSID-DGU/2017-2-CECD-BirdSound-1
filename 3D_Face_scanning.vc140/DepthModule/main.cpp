#pragma once

#include "device.h"
#include <opencv/cv.hpp>
#include <opencv/highgui.h>

#include <stdio.h>


using namespace realsense;
int main(void) {
	string devSerialNumber = getFirstSerial();
	Device* device = new Device(devSerialNumber);
	device->printDeviceInfo();
	device->printSensorInfo();
	device->EnableEmitter(0.0f);
	device->selectSensorAndStreamProps();
	//simple visual check
	while (1) {
		auto fLeft = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		auto fRight = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
		int w = 640, h = 480;
		cv::Mat leftImage(cv::Size(w, h), CV_8U, (void*)fLeft.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat rightImage(cv::Size(w, h), CV_8U, (void*)fRight.get_data(), cv::Mat::AUTO_STEP);

		cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
		cv::imshow("leftImage", leftImage);
		cv::imshow("rightImage", rightImage);
		cv::waitKey(1);
	}
}

