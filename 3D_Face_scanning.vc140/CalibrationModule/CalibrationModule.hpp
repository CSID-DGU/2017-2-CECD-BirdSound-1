#pragma once
#ifndef CALIB_H
#define CALIB_H
#include <QtWidgets/QMainWindow>
#include "ui_CalibrationModule.h"
#include "opencv2/opencv.hpp"
#undef foreach //Q_FOREACH
#include <fstream>
#include <vector>
#include <string>
#include "../DepthModule/device.h"

using namespace realsense;

class CalibrationModule : public QWidget
{
	Q_OBJECT
		enum class streamType { infrared_left, infrared_right, color };
public:
	QString toQstr(std::string);
	CalibrationModule(QWidget *parent = Q_NULLPTR);
	void startStreaming(streamType);
	void stopStreaming();
	void capture();
	void CalibrationModule::capture(RS_400_STREAM_TYPE stream);
	void CalibrationModule::calibration();
private:
	Ui::CalibrationModule ui;
	bool m_streamingAll = false;
	bool m_streamingColor = false;
	bool m_streamingIR1 = false;
	bool m_strmingIR2 = false;
	realsense::Device* m_device;
	int m_stored = 0;
	int m_color_stored = 0;
	int m_left_stored = 0;
	int m_right_stored = 0;
	int m_numBoard = 0, numCornersHor = 7, numCornersVer = 9;
	int numSquares = numCornersHor*numCornersVer;
	std::vector<std::vector<cv::Point3f>> m_color_object_points;
	std::vector<std::vector<cv::Point3f>> m_left_object_points;
	std::vector<std::vector<cv::Point3f>> m_right_object_points;
	std::vector<std::vector<cv::Point3f>> m_object_points;

	std::vector<std::vector<cv::Point2f>> m_colorImage_points;
	std::vector<std::vector<cv::Point2f>> m_leftImage_points;
	std::vector<std::vector<cv::Point2f>> m_rightrImage_points;
	
	std::vector<cv::Point2f> m_pointBufColor;
	std::vector<cv::Point2f> m_pointBufLeft;
	std::vector<cv::Point2f> m_pointBufRight;
};

#endif