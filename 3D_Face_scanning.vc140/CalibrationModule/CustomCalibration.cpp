/*
* INTEL CORPORATION PROPRIETARY INFORMATION
* This software is supplied under the terms of a license agreement
* or nondisclosure agreement with Intel Corporation and may not be
* copied or disclosed except in accordance with the terms of that
* agreement.
* Copyright(c) 2016-2017 Intel Corporation. All Rights Reserved.
*/
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>
#include "CustomCalibration.h"
using namespace std;
using namespace cv;
bool DetectChessboard(const Mat& image, const Size& chessboardSize, vector<Point2f>&
	corners)
{
	// Find chessboard corners
	if (!findChessboardCorners(image, chessboardSize, corners,
		CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FILTER_QUADS))
		return false;
	// Refine them
	cornerSubPix(image, corners, Size(11, 11), Size(-1, -1),
		TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
	return true;
}
static void CreateCorners3D(const Size& chessboardSize, float checkerSize, size_t
	numImages, vector<vector<Point3f> >& corners3D)
{
	corners3D.resize(numImages);
	corners3D[0].resize(chessboardSize.width * chessboardSize.height);
	for (int i = 0; i < chessboardSize.height; i++)
		for (int j = 0; j < chessboardSize.width; j++)
			corners3D[0][i * chessboardSize.width + j] = Point3f(j *
				checkerSize, i * checkerSize, 0.0f);
	for (size_t i = 1; i < numImages; i++)
		corners3D[i] = corners3D[0];
}
double CalibrateDepthCamera(const vector<vector<Point2f> >& cornersLeft, const
	vector<vector<Point2f> >& cornersRight, const Size& chessboardSize, float checkerSize,
	const Size& imageSizeLR, Mat& Kl, Mat& Dl, Mat& Kr, Mat& Dr, Mat& Rlr, Mat& Tlr)
{
	CV_Assert(cornersLeft.size() != 0 && cornersLeft.size() == cornersRight.size());
	CV_Assert(checkerSize > 0.0f);
	// Create 3D prototype of the corners
	vector<vector<Point3f> > corners3D;
	CreateCorners3D(chessboardSize, checkerSize, cornersLeft.size(), corners3D);
	// Calibrate each camera individualy
	calibrateCamera(corners3D, cornersLeft, imageSizeLR, Kl, Dl, noArray(),
		noArray(), CV_CALIB_FIX_ASPECT_RATIO, TermCriteria(TermCriteria::COUNT +
			TermCriteria::EPS, 60, DBL_EPSILON));
	calibrateCamera(corners3D, cornersRight, imageSizeLR, Kr, Dr, noArray(),
		noArray(), CV_CALIB_FIX_ASPECT_RATIO, TermCriteria(TermCriteria::COUNT +
			TermCriteria::EPS, 60, DBL_EPSILON));
	// Calibrate the extrinsics between them
	return stereoCalibrate(corners3D, cornersLeft, cornersRight, Kl, Dl, Kr, Dr,
		Size(-1, -1), Rlr, Tlr, noArray(), noArray(), CV_CALIB_FIX_INTRINSIC |
		CV_CALIB_USE_INTRINSIC_GUESS, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 300,
			DBL_EPSILON));
}
double CalibrateRGBCamera(const vector<vector<Point2f> >& cornersLeft, const
	vector<vector<Point2f> >& cornersRGB, const Size& chessboardSize, float checkerSize,
	const Size& imageSizeRGB, const Mat& Kl, const Mat& Dl, Mat& Kc, Mat& Dc, Mat& Rlc, Mat&
	Tlc)
{
	CV_Assert(cornersLeft.size() != 0 && cornersLeft.size() == cornersRGB.size());
	CV_Assert(checkerSize > 0.0f);
	// Create 3D prototype of the corners
	vector<vector<Point3f> > corners3D;
	CreateCorners3D(chessboardSize, checkerSize, cornersLeft.size(), corners3D);
	// Calibrate RGB camera
	calibrateCamera(corners3D, cornersRGB, imageSizeRGB, Kc, Dc, noArray(),
		noArray(), CV_CALIB_FIX_ASPECT_RATIO, TermCriteria(TermCriteria::COUNT +
			TermCriteria::EPS, 60, DBL_EPSILON));
	// Calibrate the extrinsics between them
	return stereoCalibrate(corners3D, cornersLeft, cornersRGB, Kl, Dl, Kc, Dc, Size(-
		1, -1), Rlc, Tlc, noArray(), noArray(), CV_CALIB_FIX_INTRINSIC |
		CV_CALIB_USE_INTRINSIC_GUESS, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 300,
			DBL_EPSILON));
}