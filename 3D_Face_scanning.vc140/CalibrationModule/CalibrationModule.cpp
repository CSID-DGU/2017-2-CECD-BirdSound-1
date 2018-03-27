#include "CalibrationModule.hpp"
#include "../DepthModule/device.h"
#include <thread>
#include <mutex>
using namespace realsense;

CalibrationModule::CalibrationModule(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	
	//Set static info
	string devSerialNumber = getFirstSerial();
	m_device = new Device(devSerialNumber);
	m_device->EnableEmitter(0.0f);
	ui.camName->setText(toQstr(m_device->info.name));
	ui.serialNum->setText(toQstr(m_device->info.serial));
	ui.firmwareVer->setText(toQstr(m_device->info.fw_ver));
	
	connect(ui.allStart, &QPushButton::clicked, [this] {startDetection(); });
	connect(ui.rgbStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_COLOR); });
	connect(ui.leftStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_INFRARED1); });
	connect(ui.rightStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_INFRARED2); });
	
	connect(ui.allCapture, &QPushButton::clicked, [this] {capture(); });
	connect(ui.rgbCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_COLOR); });
	connect(ui.leftCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED1); });
	connect(ui.rightCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED2); });

	connect(ui.allStop, &QPushButton::clicked, [this] {stopDetection(); });
	connect(ui.rgbStop, &QPushButton::clicked, [this] {stopDetection(RS400_STREAM_COLOR); });
	connect(ui.leftStop, &QPushButton::clicked, [this] {stopDetection(RS400_STREAM_INFRARED1); });
	connect(ui.rightStop, &QPushButton::clicked, [this] {stopDetection(RS400_STREAM_INFRARED2); });
	

	connect(ui.startCalibrate, &QPushButton::clicked, [this] {calibration(); });

	//Start each Streaming
	WorkerThread *workerColor = new WorkerThread(m_device, RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
	WorkerThread *workerIR1 = new WorkerThread(m_device, RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
	WorkerThread *workerIR2 = new WorkerThread(m_device, RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
	connect(workerColor, &WorkerThread::updateColorPixmap, this, &CalibrationModule::updateColor);
	connect(workerIR1, &WorkerThread::updateIR1Pixmap, this, &CalibrationModule::updateIR1);
	connect(workerIR2, &WorkerThread::updateIR2Pixmap, this, &CalibrationModule::updateIR2);
	workerColor->start();
	workerIR1->start();
	workerIR2->start();

	connect(this, &CalibrationModule::startColorDetect, workerColor, &WorkerThread::setDetection);
	connect(this, &CalibrationModule::startIR1Detect, workerIR1, &WorkerThread::setDetection);
	connect(this, &CalibrationModule::startIR2Detect, workerIR2, &WorkerThread::setDetection);

	connect(this, &CalibrationModule::stopColorDetect, workerColor, &WorkerThread::unsetDetection);
	connect(this, &CalibrationModule::stopIR1Detect, workerIR1, &WorkerThread::unsetDetection);
	connect(this, &CalibrationModule::stopIR2Detect, workerIR2, &WorkerThread::unsetDetection);
}

void CalibrationModule::startDetection() {
	startDetection(RS400_STREAM_COLOR);
	startDetection(RS400_STREAM_INFRARED1);
	startDetection(RS400_STREAM_INFRARED2);
}

void CalibrationModule::startDetection(RS_400_STREAM_TYPE stream) {
	if (stream == RS400_STREAM_COLOR) {
		updateSysMsg("color camera start detection!!");
		emit startColorDetect();
	}
	else if (stream == RS400_STREAM_INFRARED1) {
		updateSysMsg("left camera start detection!!");
		emit startIR1Detect();
	}
	else if (stream == RS400_STREAM_INFRARED2) {
		updateSysMsg("right camera start detection!!");
		emit startIR2Detect();
	}
}

void CalibrationModule::startStreaming() {
	
	

/*	int numSquares = numCornersHor * numCornersVer;
	cv::Size board_sz = cv::Size(numCornersHor, numCornersVer);
	bool m_streamingAll = true;

	while (m_streamingAll)
	{
		auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		auto fLeft = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		auto fRight = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
		int w = 640, h = 480;

		cv::Mat colorImage(cv::Size(w, h), CV_8UC3, (void*)fColor.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat leftImage(cv::Size(w, h), CV_8U, (void*)fLeft.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat rightImage(cv::Size(w, h), CV_8U, (void*)fRight.get_data(), cv::Mat::AUTO_STEP);
		cv::Mat gray_image;

		bool foundColor = cv::findChessboardCorners(colorImage, board_sz, m_pointBufColor, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		bool founLeft = cv::findChessboardCorners(leftImage, board_sz, m_pointBufLeft, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		bool founRight = cv::findChessboardCorners(rightImage, board_sz, m_pointBufRight, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		bool colorOK, leftOK, rightOK;
		if (foundColor)
		{
			cv::cvtColor(colorImage, gray_image, CV_BGR2GRAY);
			cv::cornerSubPix(gray_image, m_pointBufColor, cv::Size(7, 9), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(colorImage, cv::Size(7, 9), cv::Mat(m_pointBufColor), foundColor);
		}
		if (founLeft)
		{
			cornerSubPix(leftImage, m_pointBufLeft, cv::Size(7, 9), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(leftImage, cv::Size(7, 9), cv::Mat(m_pointBufLeft), founLeft);
		}
		if (founRight)
		{
			cornerSubPix(rightImage, m_pointBufRight, cv::Size(7, 9), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(rightImage, cv::Size(7, 9), cv::Mat(m_pointBufRight), founRight);
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
	}*/

}


void CalibrationModule::startStreaming(RS_400_STREAM_TYPE stream) {
		//m.lock();
		if (stream == RS400_STREAM_COLOR && m_streamingColor == false) {
			//use unrectified format for calibration. noted Custom_Calib_paper.pdf 2.4 11page.
			//IR1,2 = Y16, RGB = YUY2 (YUYV)
			//m_device->selectSensorAndStreamProps(stream, R1920_1080, YUYV, HZ15);
			m_device->selectSensorAndStreamProps(stream, R1920_1080, RGB8, HZ15);
			m_streamingColor = true;
			unique_ptr<uint32_t[]> colorBuf = unique_ptr<uint32_t[]>(new uint32_t[m_w*(m_h + 1)]);
			static int count = 0;
			while (m_streamingColor) {
				count++;
				auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
				//uint32_t *color = colorBuf.get();
				//ConvertYUY2ToRGBA((uint8_t*)fColor.get_data(), m_w, m_h, (uint8_t*)color);
				//cv::Mat colorImage(cv::Size(m_w, m_h), CV_8UC4, (uint8_t*)color, cv::Mat::AUTO_STEP);
				//cv::Mat gray_image;
				/*bool foundColor = cv::findChessboardCorners(colorImage, m_board_sz, m_pointBufColor, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
				if (foundColor)
				{
				cv::cvtColor(colorImage, gray_image, CV_BGR2GRAY);
				cv::cornerSubPix(gray_image, m_pointBufColor, cv::Size(7, 9), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
				cv::drawChessboardCorners(colorImage, cv::Size(7, 9), cv::Mat(m_pointBufColor), foundColor);
				}*/
				//cv::waitKey(1);
				QImage color_image((uchar*)fColor.get_data(), m_w, m_h, QImage::Format_RGB888);
				////QImage color_image(colorImage.data, m_w, m_h, QImage::Format_RGB888);
				QPixmap cbuf = QPixmap::fromImage(color_image);
				//emit updatePixmap(cbuf, RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
				
				ui.label->setText(toQstr(std::to_string(count)));
				//ui.rgbLabel->setPixmap(cbuf);
				//ui.rgbLabel->setScaledContents(true);
				//ui.rgbLabel->show();
			}
		}
		else if (stream == RS400_STREAM_INFRARED1 && m_streamingIR1 == false) {
			m_device->selectSensorAndStreamProps(stream, R1920_1080, Y16, HZ15);
			m_streamingIR1 = true;
			//auto leftBuf = unique_ptr<uint8_t[]>(new uint8_t[m_w*(m_h + 1)]);
			while (m_streamingIR1) {
				auto fLeft = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
				uint8_t *left = (uint8_t*)fLeft.get_data();
				ConvertLuminance16ToLuminance8((uint16_t*)fLeft.get_data(), m_w, m_h, left);


				//cv::Mat leftImage(cv::Size(m_w, m_h), CV_16U, (void*)fLeft.get_data(), cv::Mat::AUTO_STEP);


				cv::Mat left8(cv::Size(m_w, m_h), CV_8U, left, cv::Mat::AUTO_STEP);
				/*bool founLeft = cv::findChessboardCorners(left8, m_board_sz, m_pointBufLeft, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
				if (founLeft)
				{
				cornerSubPix(left8, m_pointBufLeft, cv::Size(m_numCornersHor, m_numCornersVer), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
				cv::drawChessboardCorners(left8, cv::Size(m_numCornersHor, m_numCornersVer), cv::Mat(m_pointBufLeft), founLeft);
				}*/
				cv::waitKey(1);
				QImage lq_image(left8.data, m_w, m_h, QImage::Format_Grayscale8);
				QPixmap lbuf = QPixmap::fromImage(lq_image);
				ui.irLeftLabel->setPixmap(lbuf);
				ui.irLeftLabel->setScaledContents(true);
				ui.irLeftLabel->show();
			}

		}
		else if (stream == RS400_STREAM_INFRARED2 && m_streamingIR2 == false) {
			m_device->selectSensorAndStreamProps(stream, R1920_1080, Y16, HZ15);
			m_streamingIR2 = true;
			//auto rightBuf = unique_ptr<uint8_t[]>(new uint8_t[m_w*(m_h + 1)]);
			while (m_streamingIR2) {
				auto fRight = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
				uint8_t *right = (uint8_t*)fRight.get_data();
				ConvertLuminance16ToLuminance8((uint16_t*)fRight.get_data(), m_w, m_h, right);

				//cv::Mat rightImage(cv::Size(m_w, m_h), CV_16U, (void*)fRight.get_data(), cv::Mat::AUTO_STEP);

				cv::Mat right8(cv::Size(m_w, m_h), CV_8U, right, cv::Mat::AUTO_STEP);
				/*bool founRight = cv::findChessboardCorners(right8, m_board_sz, m_pointBufRight, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
				if (founRight)
				{
				cornerSubPix(right8, m_pointBufRight, cv::Size(7, 9), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
				cv::drawChessboardCorners(right8, cv::Size(7, 9), cv::Mat(m_pointBufRight), founRight);
				}*/
				cv::waitKey(1);
				QImage rq_image(right8.data, m_w, m_h, QImage::Format_Grayscale8);
				QPixmap rbuf = QPixmap::fromImage(rq_image);
				ui.irRightLabel->setPixmap(rbuf);
				ui.irRightLabel->setScaledContents(true);
				ui.irRightLabel->show();
			}
		}
		//m.unlock();
}


void CalibrationModule::capture() {

	/*capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
	capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
	capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);*/
	/*vector<cv::Point3f> obj;
	for (int j = 0; j<numSquares; j++)
		obj.push_back(cv::Point3f(j / numCornersHor, j%numCornersHor, 0.0f));

	m_colorImage_points.push_back(m_pointBufColor);
	m_leftImage_points.push_back(m_pointBufLeft);
	m_rightrImage_points.push_back(m_pointBufRight);
	m_object_points.push_back(obj);
	m_stored++;
	std::string msg = "Now " + to_string(m_stored) + "image is saved.";
	ui.message->setText(toQstr(msg));*/
}

void CalibrationModule::capture(RS_400_STREAM_TYPE stream) {
	vector<cv::Point3f> obj;
	for (int j = 0; j<numSquares; j++)
		obj.push_back(cv::Point3f(j / numCornersHor, j%numCornersHor, 0.0f));
	std::string str;
	switch (stream) {
	case RS400_STREAM_COLOR:
		m_colorImage_points.push_back(m_pointBufColor);
		m_color_object_points.push_back(obj);
		m_color_stored++;
		str = to_string(m_color_stored) + "/20";
		ui.rgbCount->setText(toQstr(str));
		break;
	case RS400_STREAM_INFRARED1:
		m_leftImage_points.push_back(m_pointBufLeft);
		m_left_object_points.push_back(obj);
		m_left_stored++;
		str = to_string(m_left_stored) + "/20";
		ui.leftCount->setText(toQstr(str));
		break;
	case RS400_STREAM_INFRARED2:
		m_rightrImage_points.push_back(m_pointBufRight);
		m_right_object_points.push_back(obj);
		m_right_stored++;
		str = to_string(m_right_stored) + "/20";
		ui.rightCount->setText(toQstr(str));
		break;
	}

}

void CalibrationModule::stopStreaming() {
	//All stop streaming
	stopStreaming(RS400_STREAM_COLOR);
	stopStreaming(RS400_STREAM_INFRARED1);
	stopStreaming(RS400_STREAM_INFRARED2);
}

void CalibrationModule::stopStreaming(RS_400_STREAM_TYPE stream) {
	ui.rgbLabel->setText(toQstr(to_string(10)));
	if (stream == RS_400_STREAM_TYPE::RS400_STREAM_COLOR) {
		m_device->stopStreaming(stream);
		ui.rgbLabel->clear();
	}
	else if (stream == RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1) {
		m_device->stopStreaming(stream);
		ui.irLeftLabel->clear();
	}
	else if (stream == RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2) {
		m_device->stopStreaming(stream);
		ui.irRightLabel->clear();
	}
}

void CalibrationModule::calibration() {
	cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
	cv::Mat distCoeffs;
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
	
	int w = 640, h = 480;
	auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
	cv::Mat colorImage(cv::Size(w, h), CV_8UC3, (void*)fColor.get_data(), cv::Mat::AUTO_STEP);

	cv::calibrateCamera(m_color_object_points, m_colorImage_points, colorImage.size(), intrinsic, distCoeffs, rvecs, tvecs);


}


inline QString CalibrationModule::toQstr(std::string str) {
	return QString::fromUtf8(str.c_str());
}