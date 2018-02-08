#include "CalibrationModule.h"
#include "opencv2/opencv.hpp"
#undef foreach //Q_FOREACH
#include <fstream>
#include "../DepthModule/device.h"
using namespace realsense;

CalibrationModule::CalibrationModule(QWidget *parent): QMainWindow(parent)
{
	
	ui.setupUi(this);
	//connect(ui.startStreaming, SIGNAL(clicked()), this, SLOT());
	connect(ui.startStreaming, &QPushButton::clicked, [this] {startStreaming(streamType::color); });
	connect(ui.captrueImage, &QPushButton::clicked, [this] {captureFrame(); });

}

void CalibrationModule::startStreaming(streamType st) {

	
	//RS400Device* device = new RS400Device;


	//device->EnableAutoExposure(1.0f);

	
	string devSerialNumber = getFirstSerial();
	Device* device = new Device(devSerialNumber);
	device->printDeviceInfo();
	device->EnableEmitter(0.0f);
	//device->printSensorInfo();
	device->selectSensorAndStreamProps();

	cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
	while (1) 
	{
		auto fColor = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		auto fLeft = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		auto fRight = device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
		int w = 640, h = 480;

		
		cv::Mat colorImage(cv::Size(w, h), CV_8UC3, (void*)fColor.get_data(), cv::Mat::AUTO_STEP);
		ReorderY16((uint16_t*)fLeft.get_data(), 1920, 1080);
		cv::Mat leftImage(cv::Size(1920, 1080), CV_16U, (void*)fLeft.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat rightImage(cv::Size(1920, 1080), CV_16U, (void*)fRight.get_data(), cv::Mat::AUTO_STEP);

		
		/*cv::imshow("namedWindow", leftImage);
		cv::imshow("namedWindow", rightImage);*/
		cv::waitKey(1);

		
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

void CalibrationModule::captureFrame() {

}

