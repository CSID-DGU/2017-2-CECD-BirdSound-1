#pragma once
#ifndef DEMO_FIRST_H
#define DEMO_FIRST_H
#include <QtWidgets/QMainWindow>
#include "ui_demofirstpart.h"
#undef foreach //Q_FOREACH
#include <fstream>
#include <vector>
#include <string>
#include "../DepthModule/device.h"

using namespace realsense;

class DemoFirstPart : public QWidget
{
	Q_OBJECT
		enum class streamType { infrared_left, infrared_right, color };
public:
	QString toQstr(std::string);
	DemoFirstPart(QWidget *parent = Q_NULLPTR);
	void DemoFirstPart::startStreaming(RS_400_STREAM_TYPE stream);
	void startStreaming();
	//void stopStreaming();
	void capture();
	//void CalibrationModule::capture(RS_400_STREAM_TYPE stream);
	//void CalibrationModule::calibration();
private:
	Ui::DemoFirstPart ui;
	bool m_isStreaming = false;
	std::vector<std::thread> m_thread_pool;
	//bool m_streamingAll = false;
	//bool m_streamingColor = false;
	//bool m_streamingIR1 = false;
	//bool m_strmingIR2 = false;
	realsense::Device* m_device;
	bool m_streamingColor;
	bool m_streamingDepth;
	size_t m_color_height = 1080;
	size_t m_color_width = 1920;
	size_t m_depth_height = 720;
	size_t m_depth_width = 1280;
	rs2::frame m_frame_color;
	rs2::frame m_frame_depth;
	//int m_stored = 0;
	//int m_color_stored = 0;
	//int m_left_stored = 0;
	//int m_right_stored = 0;
	//int m_numBoard = 0, numCornersHor = 7, numCornersVer = 9;
	//int numSquares = numCornersHor*numCornersVer;
	//std::vector<std::vector<cv::Point3f>> m_color_object_points;
	//std::vector<std::vector<cv::Point3f>> m_left_object_points;
	//std::vector<std::vector<cv::Point3f>> m_right_object_points;
	//std::vector<std::vector<cv::Point3f>> m_object_points;

	//std::vector<std::vector<cv::Point2f>> m_colorImage_points;
	//std::vector<std::vector<cv::Point2f>> m_leftImage_points;
	//std::vector<std::vector<cv::Point2f>> m_rightrImage_points;

	//std::vector<cv::Point2f> m_pointBufColor;
	//std::vector<cv::Point2f> m_pointBufLeft;
	//std::vector<cv::Point2f> m_pointBufRight;
};

#endif