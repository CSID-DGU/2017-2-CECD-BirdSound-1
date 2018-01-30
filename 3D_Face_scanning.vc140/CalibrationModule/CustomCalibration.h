/*
* INTEL CORPORATION PROPRIETARY INFORMATION
* This software is supplied under the terms of a license agreement
* or nondisclosure agreement with Intel Corporation and may not be
* copied or disclosed except in accordance with the terms of that
* agreement.
* Copyright(c) 2016-2017 Intel Corporation. All Rights Reserved.
*/
#ifndef CUSTOMCALIBRATION_H_
#define CUSTOMCALIBRATION_H_
#include <opencv2/opencv.hpp>
// Sample code that detects the chessboard from an image using OpenCV
bool DetectChessboard(const cv::Mat& image, const cv::Size& chessboardSize,
	std::vector<cv::Point2f>& corners);
// Sample code how to calculate depth camera calibration using OpenCV
double CalibrateDepthCamera(const std::vector<std::vector<cv::Point2f> >& cornersLeft,
	const std::vector<std::vector<cv::Point2f> >& cornersRight, const cv::Size&
	chessboardSize, float checkerSize, const cv::Size& imageSizeLR, cv::Mat& Kl, cv::Mat& Dl,
	cv::Mat& Kr, cv::Mat& Dr, cv::Mat& Rlr, cv::Mat& Tlr);
// Sample code how to calculate RGB camera calibration using OpenCV (this assumes gooddepth camera calibration)
double CalibrateRGBCamera(const std::vector<std::vector<cv::Point2f> >& cornersLeft,
	const std::vector<std::vector<cv::Point2f> >& cornersRGB, const cv::Size& chessboardSize,
	float checkerSize, const cv::Size& imageSizeRGB, const cv::Mat& Kl, const cv::Mat& Dl,
	cv::Mat& Kc, cv::Mat& Dc, cv::Mat& Rlc, cv::Mat& Tlc);
// Sample code how to recalculate RGB camera calibration extrinsics using OpenCV (thisassumes good depth camera calibration and instrinsics of the RGB camera)
double RecalibrateRGBCamera(const std::vector<std::vector<cv::Point2f> >& cornersLeft,
	const std::vector<std::vector<cv::Point2f> >& cornersRGB, const cv::Size& chessboardSize,
	float checkerSize, const cv::Mat& Kl, const cv::Mat& Dl, const cv::Mat& Kc, const
	cv::Mat& Dc, cv::Mat& Rlc, cv::Mat& Tlc);
#endif //CUSTOMCALIBRATION_H_