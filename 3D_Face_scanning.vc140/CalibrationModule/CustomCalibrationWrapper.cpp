#include "DS5CalibCoefficients.h"
//#include "DSDynamicCalibration.h"
#include "CustomCalibration.h"
#include "CustomCalibrationWrapper.h"
#include <vector>
using namespace std;
using namespace cv;
using namespace dscam;
#define mCustomCalibratorData ((CustomCalibratorData*)mData)
#define ccwhandle ((CustomCalibrationWrapper*)handle)
namespace CustomCalibWrapper
{
	struct CustomCalibratorData
	{
		vector<vector<vector<Point2f> > > corners;
		Size chessboardSize;
		float chessboardSquareSize;
	};
	CustomCalibrationWrapper::CustomCalibrationWrapper(void *rs400Dev, int chessboardWidth,
	int chessboardHeight, float chessboardSquareSize, int numCameras, int numImages)
	{
		mRs400Device = rs400Dev;
		mData = new CustomCalibratorData();
		mCustomCalibratorData->chessboardSize = Size(chessboardWidth, chessboardHeight);
		mCustomCalibratorData->chessboardSquareSize = chessboardSquareSize;
		mCustomCalibratorData->corners.resize(numCameras);
		for (int i = 0; i < numCameras; i++)
			mCustomCalibratorData->corners[i].resize(numImages);
	}
	CustomCalibrationWrapper::~CustomCalibrationWrapper()
	{
		if (mData)
		{
			delete mData;
			mData = NULL;
		}
	}
	bool CustomCalibrationWrapper::AddImage(uint8_t* image, int width, int height, int
		stride, int cameraIndex, int imageIndex)
	{
		Mat imgMat(Size(width, height), CV_8U, image, stride);
		return DetectChessboard(imgMat, mCustomCalibratorData->chessboardSize,
			mCustomCalibratorData->corners[cameraIndex][imageIndex]);
	}
	int CustomCalibrationWrapper::CalculateCalibration(int lrWidth, int lrHeight, int
		rgbWidth, int rgbHeight)
	{
		try
		{
			bool hasRGB = mCustomCalibratorData->corners.size() > 2;
			Mat Kl, Dl, Kr, Dr, Rlr, Tlr;
			CalibrateDepthCamera(mCustomCalibratorData->corners[0],
				mCustomCalibratorData->corners[1], mCustomCalibratorData->chessboardSize,
				mCustomCalibratorData->chessboardSquareSize, Size(lrWidth, lrHeight), Kl, Dl, Kr, Dr,
				Rlr, Tlr);
			Mat Kc, Dc, Rlc, Tlc;
			if (hasRGB)
				CalibrateRGBCamera(mCustomCalibratorData->corners[0],
					mCustomCalibratorData->corners[2], mCustomCalibratorData->chessboardSize,
					mCustomCalibratorData->chessboardSquareSize, Size(rgbWidth, rgbHeight), Kl, Dl, Kc, Dc,
					Rlc, Tlc);
			else
			{
				Kc = Mat::zeros(3, 3, CV_64F);
				Dc = Mat::zeros(1, 5, CV_64F);
				Rlc = Mat::zeros(3, 3, CV_64F);
				Tlc = Mat::zeros(3, 1, CV_64F);
			}
			int resolutionLR[2] = { lrWidth, lrHeight };
			double focalLengthLeft[2] = { Kl.at<double>(0,0), Kl.at<double>(1,1) };
			double principalPointLeft[2] = { Kl.at<double>(0,2), Kl.at<double>(1,2)
			};
			double distortionLeft[5] = { Dl.at<double>(0,0), Dl.at<double>(0,1),
				Dl.at<double>(0,2), Dl.at<double>(0,3), Dl.at<double>(0,4) };
			double focalLengthRight[2] = { Kr.at<double>(0,0), Kr.at<double>(1,1) };
			double principalPointRight[2] = { Kr.at<double>(0,2), Kr.at<double>(1,2)
			};
			double distortionRight[5] = { Dr.at<double>(0,0), Dr.at<double>(0,1),
				Dr.at<double>(0,2), Dr.at<double>(0,3), Dr.at<double>(0,4) };
			double rotationLR[9] = { Rlr.at<double>(0,0), Rlr.at<double>(0,1),
				Rlr.at<double>(0,2), Rlr.at<double>(1,0), Rlr.at<double>(1,1),
				Rlr.at<double>(1,2), Rlr.at<double>(2,0), Rlr.at<double>(2,1),
				Rlr.at<double>(2,2) };
			double translationLR[3] = { Tlr.at<double>(0,0), Tlr.at<double>(1,0),
				Tlr.at<double>(2,0) };
			int resolutionRGB[2] = { rgbWidth, rgbHeight };
			double focalLengthRGB[2] = { Kc.at<double>(0,0), Kc.at<double>(1,1) };
			double principalPointRGB[2] = { Kc.at<double>(0,2), Kc.at<double>(1,2) };
			double distortionRGB[5] = { Dc.at<double>(0,0), Dc.at<double>(0,1),
				Dc.at<double>(0,2), Dc.at<double>(0,3), Dc.at<double>(0,4) };
			double rotationLC[9] = { Rlc.at<double>(0,0), Rlc.at<double>(0,1),
				Rlc.at<double>(0,2), Rlc.at<double>(1,0), Rlc.at<double>(1,1),
				Rlc.at<double>(1,2), Rlc.at<double>(2,0), Rlc.at<double>(2,1),
				Rlc.at<double>(2,2) };
			double translationLC[3] = { Tlc.at<double>(0,0), Tlc.at<double>(1,0),
				Tlc.at<double>(2,0) };
			DynamicCalibrationAPI::DSDynamicCalibration* dyCalib = new DynamicCalibrationAPI::DSDynamicCalibration(); dyCalib->Initialize(mRs400Device,
			DynamicCalibrationAPI::DSDynamicCalibration::CalibrationMode::CAL_MODE_USER_CUSTOM, lrWidth, lrHeight);
			int status = dyCalib->WriteCustomCalibrationParameters(resolutionLR,
				focalLengthLeft, principalPointLeft, distortionLeft, focalLengthRight,
				principalPointRight, distortionRight, rotationLR, translationLR,
				hasRGB, resolutionRGB, focalLengthRGB, principalPointRGB,
				distortionRGB, rotationLC, translationLC);
			return status;
		}
		catch (...)
		{
			return -1;
		}
	}
}