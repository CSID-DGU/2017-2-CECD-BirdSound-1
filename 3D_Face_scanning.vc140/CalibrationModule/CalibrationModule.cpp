#include "CalibrationModule.h"
#include "opencv2/opencv.hpp"
#undef foreach //Q_FOREACH
#include <fstream>
#include "../DepthModule/device.h"
using namespace realsense;

CalibrationModule::CalibrationModule(QWidget *parent) : QMainWindow(parent)
{

	ui.setupUi(this);
	//connect(ui.startStreaming, SIGNAL(clicked()), this, SLOT());
	connect(ui.startStreaming, &QPushButton::clicked, [this] {startStreaming(streamType::color); });

}

void CalibrationModule::startStreaming(streamType st) {

	cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
	vector<cv::Point2f> pointBufColor;
	vector<cv::Point2f> pointBufLeft;
	vector<cv::Point2f> pointBufRight;

	string devSerialNumber = getFirstSerial();
	Device* device = new Device(devSerialNumber);
	device->printDeviceInfo();
	device->EnableEmitter(0.0f);
	//device->printSensorInfo();
	device->selectSensorAndStreamProps();


	while (1)
	{
		auto fColor = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		auto fLeft = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		auto fRight = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
		int w = 640, h = 480;

		cv::Mat colorImage(cv::Size(w, h), CV_8UC3, (void*)fColor.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat leftImage(cv::Size(w, h), CV_8U, (void*)fLeft.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat rightImage(cv::Size(w, h), CV_8U, (void*)fRight.get_data(), cv::Mat::AUTO_STEP);


		bool foundColor = cv::findChessboardCorners(colorImage, cv::Size(7, 9), pointBufColor, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		bool founLeft = cv::findChessboardCorners(leftImage, cv::Size(7, 9), pointBufLeft, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		bool founRight = cv::findChessboardCorners(rightImage, cv::Size(7, 9), pointBufRight, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

		if (foundColor)
		{
			//cv::cornerSubPix(colorImage, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(colorImage, cv::Size(7, 9), cv::Mat(pointBufColor), foundColor);
		}
		if (founLeft)
		{
			//cv::cornerSubPix(colorImage, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(leftImage, cv::Size(7, 9), cv::Mat(pointBufLeft), founLeft);
		}
		if (founRight)
		{
			//cv::cornerSubPix(colorImage, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(rightImage, cv::Size(7, 9), cv::Mat(pointBufRight), founRight);
		}

		cv::waitKey(1);


		//QImage color_image((uchar*)fColor.get_data(), w, h, QImage::Format_RGB888);
		QImage color_image(colorImage.data, w, h, QImage::Format_RGB888);
		QImage lq_image(leftImage.data, w, h, QImage::Format_Grayscale8);
		QImage rq_image(rightImage.data, w, h, QImage::Format_Grayscale8);
		QPixmap cbuf = QPixmap::fromImage(color_image);
		QPixmap lbuf = QPixmap::fromImage(lq_image);
		QPixmap rbuf = QPixmap::fromImage(rq_image);
		ui.rgbLabel->setPixmap(cbuf);
		ui.irLeftLabel->setPixmap(lbuf);
		ui.irRightLabel->setPixmap(rbuf);
		ui.rgbLabel->setScaledContents(true);
		ui.irLeftLabel->setScaledContents(true);
		ui.irRightLabel->setScaledContents(true);
		ui.rgbLabel->show();
		ui.irLeftLabel->show();
		ui.irRightLabel->show();
	}
}



