#pragma once
#ifndef CALIB_H
#define CALIB_H
#include <QtWidgets/QMainWindow>
#include <qthread.h>
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
	void startStreaming();
	void startStreaming(RS_400_STREAM_TYPE stream);
	void stopStreaming();
	void stopStreaming(RS_400_STREAM_TYPE stream);
	void capture();
	void capture(RS_400_STREAM_TYPE stream);
	void calibration();

public slots:
void updateColor(QPixmap pixmap) {
	ui.rgbLabel->setPixmap(pixmap);
	ui.rgbLabel->setScaledContents(true);
	ui.rgbLabel->show();
};
void updateIR1(QPixmap pixmap) {
	ui.irLeftLabel->setPixmap(pixmap);
	ui.irLeftLabel->setScaledContents(true);
	ui.irLeftLabel->show();
}
void updateIR2(QPixmap pixmap) {
	ui.irRightLabel->setPixmap(pixmap);
	ui.irRightLabel->setScaledContents(true);
	ui.irRightLabel->show();
}

private:
	std::mutex m;
	Ui::CalibrationModule ui;
	

	int m_numCornersHor = 7, m_numCornersVer = 9;
	int m_numSquares = m_numCornersHor * m_numCornersVer;
	cv::Size m_board_sz = cv::Size(m_numCornersHor, m_numCornersVer);
	int m_w = 1920, m_h = 1080;
	bool m_streamingColor = false;
	bool m_streamingIR1 = false;
	bool m_streamingIR2 = false;
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

//Q_SIGNALS:
//	void CalibrationModule::updatePixmap(const QPixmap& pixmap, realsense::RS_400_STREAM_TYPE);
//
//public slots:
//	void CalibrationModule::updatePixmap(const QPixmap& pixmap, realsense::RS_400_STREAM_TYPE);

};


#endif