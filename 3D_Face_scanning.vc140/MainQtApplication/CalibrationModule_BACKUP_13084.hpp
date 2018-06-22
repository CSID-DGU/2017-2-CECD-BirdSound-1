#pragma once
#ifndef CALIB_H
#define CALIB_H
#include <QtWidgets/QMainWindow>
#include "ui_CalibrationModule.h"
#include "opencv2/opencv.hpp"
#include "WorkerThread.hpp"
#undef foreach //Q_FOREACH
#include <fstream>
#include <vector>
#include <string>
#include "../DepthModule/device.h"

using namespace realsense;

class CalibrationModule : public QWidget
{
<<<<<<< HEAD
	Q_OBJECT
		enum class streamType {  infrared_left, infrared_right, color };
	const int max_shot_num = 10;
=======
	Q_OBJECT 
		enum class streamType { infrared_left, infrared_right, color };
>>>>>>> 7f4bd3be40c0de851b1abf7442358153311f28ec
public:
	QString toQstr(std::string);
	CalibrationModule(QWidget *parent = Q_NULLPTR);
	void startDetection();
	void startDetection(RS_400_STREAM_TYPE stream);
	void sycCam();
	void stopDetection();;
	void stopDetection(RS_400_STREAM_TYPE stream) {
		if (stream == RS400_STREAM_COLOR) {
			ui.rgbStart->setEnabled(true);
			ui.rgbStop->setEnabled(false);
			ui.rgbCapture->setEnabled(false);

			updateSysMsg("stop color stream detection!");
			emit stopColorDetect();
		}
		else if (stream == RS400_STREAM_INFRARED1) {
			ui.leftStart->setEnabled(true);
			ui.leftStop->setEnabled(false);
			ui.leftCapture->setEnabled(false);
			updateSysMsg("stop left stream detection!");
			emit stopIR1Detect();
		}
		else if (stream == RS400_STREAM_INFRARED2) {
			ui.leftStart->setEnabled(true);
			ui.leftStop->setEnabled(false);
			ui.leftCapture->setEnabled(false);
			updateSysMsg("stop right stream detection!");
			emit stopIR2Detect();
		}
	};

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
	void updateCaptureNum(int captureNum, RS_400_STREAM_TYPE m_stream);
	void flagCalibration(std::vector<std::vector<cv::Point3f>> object_points, std::vector<std::vector<cv::Point2f>> image_points, RS_400_STREAM_TYPE m_stream);

signals:
	void syncLeft();
	void startColorDetect();
	void startIR1Detect();
	void startIR2Detect();
	void stopColorDetect();
	void stopIR1Detect();
	void stopIR2Detect();

private:
	void updateSysMsg(string msg) {
		ui.message->moveCursor(QTextCursor::End);
		ui.message->insertPlainText(toQstr("[SYSTEM] "+msg+"\n"));
		ui.message->moveCursor(QTextCursor::End);
	};
	std::mutex m;
	Ui::CalibrationModule ui;
	WorkerThread *workerColor;
	WorkerThread *workerIR1;
	WorkerThread *workerIR2;



	bool m_rgbCalib_flag = false;
	bool m_leftCalib_flag = false;
	bool m_rightCalib_flag = false;

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
	int numSquares = numCornersHor * numCornersVer;
	std::vector<std::vector<cv::Point3f>> m_color_object_points;
	std::vector<std::vector<cv::Point3f>> m_left_object_points;
	std::vector<std::vector<cv::Point3f>> m_right_object_points;
	std::vector<std::vector<cv::Point3f>> m_object_points;


	std::vector<std::vector<cv::Point2f>> m_colorImage_points;
	std::vector<std::vector<cv::Point2f>> m_leftImage_points;
	std::vector<std::vector<cv::Point2f>> m_rightrImage_points;

	std::vector<cv::Point2f> m_pointBufColor;

	std::vector<cv::Point2f> m_pointBufRight;

};


#endif