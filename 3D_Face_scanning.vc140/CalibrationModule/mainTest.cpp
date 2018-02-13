#pragma once
#include "../DepthModule/device.h"
#include "opencv2\opencv.hpp"

using namespace realsense;
using namespace std;
using namespace cv;
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
	vector<vector<cv::Point3f>> object_points;
	vector<vector<cv::Point2f>> image_points;
	vector <cv::Point3f > obj;
		
	int wSq = 7, hSq = 9;
	int numSq = wSq*hSq;
	
	for (int j = 0; j<numSq; j++)
		obj.push_back(cv::Point3f(j / wSq, j%wSq, 0.0f));

	int numShot = 10;
	int success = 0;
	int wImage = 640, hImage = 480;
	Mat gray_image;
	Mat colorImage;
	while (1) {

		auto fColor = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		
		colorImage = Mat(cv::Size(wImage, hImage), CV_8UC3, (void*)fColor.get_data(), cv::Mat::AUTO_STEP);
		bool found = cv::findChessboardCorners(colorImage, cv::Size(wSq, hSq), pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

		if (found)
		{
			cv::cvtColor(colorImage, gray_image, CV_BGR2GRAY);
			cv::cornerSubPix(gray_image, pointBuf, cv::Size(wSq,hSq), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(colorImage, cv::Size(wSq, hSq), cv::Mat(pointBuf), found);
			cv::imshow("grayImage", gray_image);
		}
		cv::imshow("colorImage", colorImage); 
		
		char key = cv::waitKey(1); 
		if (key == ' ') {
			image_points.push_back(pointBuf);
			object_points.push_back(obj); 
			success++; 
			printf("Snap stored"); 
		
			if (success > numShot-1) break;
		}

	}
	
	Mat intrinsic = Mat(3, 3, CV_64F);
	Mat distCoeffs = Mat::zeros(8, 1, CV_64F);
	vector<Mat> rvecs;
	vector<Mat> tvecs;
	intrinsic.ptr<float>(0)[0] = 1;
	intrinsic.ptr<float>(1)[1] = 1;

	cv::calibrateCamera(object_points, image_points, Size(wImage,hImage), intrinsic, distCoeffs, rvecs, tvecs);
	
	Mat imageUndistored;
	
	while (1) {

		auto fColor = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		colorImage = Mat(cv::Size(wImage, hImage), CV_8UC3, (void*)fColor.get_data(), cv::Mat::AUTO_STEP);
		undistort(colorImage, imageUndistored, intrinsic, distCoeffs);
		imshow("original", colorImage);
		cv::waitKey(1);
		imshow("after", imageUndistored);
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