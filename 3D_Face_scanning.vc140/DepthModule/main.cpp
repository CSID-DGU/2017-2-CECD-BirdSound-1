#pragma once

#include "device.h"
#include <stdio.h>


using namespace realsense;
int main(void) {
	string devSerialNumber = getFirstSerial();
	Device* device = new Device(devSerialNumber);
	device->printDeviceInfo();
	//device->printSensorInfo();
	device->EnableEmitter(0.0f);
	device->selectSensorAndStreamProps();
	
	/*while (1) {
		auto f = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		cv::Mat image(cv::Size(640, 480), CV_8UC3, (void*)f.get_data(), cv::Mat::AUTO_STEP);
		cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
		cv::imshow("namedWindow", image);
		cv::waitKey(1);
	}*/
	//Infrared #1 (640x480 / Y8 / 30Hz)

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

	//auto frame = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
	//auto vsp = frame.get_profile().as<rs2::video_stream_profile>();
	//cout << vsp.stream_name();
	//while (1) {
	//	auto f = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
	//	auto rightFrame = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
	//	//cv::Mat image(cv::Size(vsp.width(), vsp.height()), CV_8U, (void*)f.get_data(), cv::Mat::AUTO_STEP);
	//	cv::Mat image2(cv::Size(640, 480), CV_8U, (void*)rightFrame.get_data(), cv::Mat::AUTO_STEP);
	//	cv::Mat image(cv::Size(vsp.width(), vsp.height()), CV_8U, (void*)f.get_data(), cv::Mat::AUTO_STEP);
	//	cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
	//	cv::imshow("namedWindow", image);
	//	cv::imshow("namedWindow", image2);
	//	cv::waitKey(1);
	//}

}

//
///*** CV**/
//rs2::frame _lastFrame;
//
//int numCornersHor;
//int numCornersVer;
//
//printf("Enter number of corners along width: ");
//scanf("%d", &numCornersHor);
//
//printf("Enter number of corners along height: ");
//scanf("%d", &numCornersVer);
//
//int numSquares = numCornersHor * numCornersVer;
//vector<cv::Point2d> corners;
//cv::Size board_sz = cv::Size(numCornersHor, numCornersVer);
//
///*** CV**/
//while (1) {
//
//	
//	
//	bool found = cv::findChessboardCorners(image, board_sz, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
//
//	if (found)
//	{
//		cv::cornerSubPix(image, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
//		cv::drawChessboardCorners(image, board_sz, corners, found);
//	}
//};
