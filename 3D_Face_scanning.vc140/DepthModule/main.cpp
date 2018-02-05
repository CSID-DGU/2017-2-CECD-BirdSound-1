#pragma once

#include "device.h"

using namespace realsense;
int main(void) {
	string devSerialNumber = getFirstSerial();
	Device* device = new Device(devSerialNumber);
	device->printDeviceInfo();
	//device->printSensorInfo();
	device->selectSensorAndStreamProps();
	
	/*while (1) {
		auto f = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		cv::Mat image(cv::Size(640, 480), CV_8UC3, (void*)f.get_data(), cv::Mat::AUTO_STEP);
		cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
		cv::imshow("namedWindow", image);
		cv::waitKey(1);
	}*/

	while (1) {
		auto f = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		cv::Mat image(cv::Size(640, 480), CV_8U, (void*)f.get_data(), cv::Mat::AUTO_STEP);
		cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
		cv::imshow("namedWindow", image);
		cv::waitKey(1);
	}

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
