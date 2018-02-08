#pragma once
#include "../DepthModule/device.h"

using namespace realsense;
int main(void) {

	context ctx;
	device_list devl = ctx.query_devices();
	device dev = devl[0];



	string devSerialNumber = getFirstSerial();
	Device* device = new Device(devSerialNumber);
	device->printDeviceInfo();
	//device->printSensorInfo();
	device->EnableEmitter(0.0f);
	device->selectSensorAndStreamProps();

	cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);

	vector<cv::Point2f> pointBuf;
	vector<cv::Point2f> pointBuf1;
	vector<cv::Point2f> pointBuf2;



	while (1) {

		auto fColor = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		auto fLeft = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		auto fRight = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
		int w = 640, h = 480;
		cv::Mat colorImage(cv::Size(w, h), CV_8UC3, (void*)fColor.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat leftImage(cv::Size(w, h), CV_8U, (void*)fLeft.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat rightImage(cv::Size(w, h), CV_8U, (void*)fRight.get_data(), cv::Mat::AUTO_STEP);


		bool found = cv::findChessboardCorners(colorImage, cv::Size(7, 9), pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		bool foundir1 = cv::findChessboardCorners(leftImage, cv::Size(7, 9), pointBuf1, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		bool foundir2 = cv::findChessboardCorners(rightImage, cv::Size(7, 9), pointBuf2, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		if (found)
		{
			//cv::cornerSubPix(colorImage, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(colorImage, cv::Size(7, 9), cv::Mat(pointBuf), found);
		}
		if (foundir1)
		{
			//cv::cornerSubPix(colorImage, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(leftImage, cv::Size(7, 9), cv::Mat(pointBuf1), found);
		}
		if (foundir2)
		{
			//cv::cornerSubPix(colorImage, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(rightImage, cv::Size(7, 9), cv::Mat(pointBuf2), found);
		}


		cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
		cv::imshow("leftImage", leftImage);
		cv::imshow("rightImage", rightImage);
		cv::imshow("colorImage", colorImage);
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
//if (found)
//{
//	cv::cornerSubPix(image, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
//	cv::drawChessboardCorners(image, board_sz, corners, found);
//}
//};