#include "CalibrationModule.h"
#include <QtWidgets/QApplication>
#undef foreach //Q_FOREACH
#include "librealsense2\rs.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "../DepthModule/device.h"

using namespace std;
using namespace cv;



//bool CustomCalibrationWrapper::AddImage(uint8_t* image, int width, int height, int
//	stride, int cameraIndex, int imageIndex)
//{
//	Mat imgMat(Size(width, height), CV_8U, image, stride);
//	return DetectChessboard(imgMat, mCustomCalibratorData->chessboardSize,
//		mCustomCalibratorData->corners[cameraIndex][imageIndex]);
//}
//
//bool DetectChessboard(const Mat& image, const Size& chessboardSize, vector<Point2f>&
//	corners)
//{
//	// Find chessboard corners
//	if (!findChessboardCorners(image, chessboardSize, corners,
//		CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FILTER_QUADS))
//		return false;
//	// Refine them
//	cornerSubPix(image, corners, Size(11, 11), Size(-1, -1),
//		TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
//	return true;
//}
//
//bool GetProfile(rs2::stream_profile& profile, rs2_stream stream, int width, int
//	height,
//	int fps, int index)
//{
//	rs2::sensor sensor;
//	rs2_format format;
//	if (stream == rs2_stream::RS2_STREAM_INFRARED)
//	{
//		sensor = m_depthSensor;
//		format = rs2_format::RS2_FORMAT_Y16;
//	}
//	else
//	{
//		sensor = m_colorSensor;
//		format = rs2_format::RS2_FORMAT_YUYV;
//	}
//	vector<stream_profile> pfs = sensor.get_stream_profiles();
//	for (int i = 0; i < (int)pfs.size(); i++)
//	{
//		auto video = pfs[i].as<video_stream_profile>();
//		if ((pfs[i].format() == format)
//			&& (video.width() == width)
//			&& (video.height() == height)
//			&& (video.fps() == fps)
//			&& (video.stream_index() == index)
//			)
//		{
//			profile = pfs[i];
//			return true;
//		}
//	}
//	return false;
//}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CalibrationModule w;
	w.show();
	return a.exec();
}
