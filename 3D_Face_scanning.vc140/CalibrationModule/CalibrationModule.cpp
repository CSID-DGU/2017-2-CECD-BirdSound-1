#include "CalibrationModule.h"

using namespace realsense;

CalibrationModule::CalibrationModule(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	string devSerialNumber = getFirstSerial();
	m_device = new Device(devSerialNumber);
	ui.camName->setText(toQstr(m_device->info.name));
	ui.serialNum->setText(toQstr(m_device->info.serial));
	ui.firmwareVer->setText(toQstr(m_device->info.fw_ver));

	connect(ui.startStreaming, &QPushButton::clicked, [this] {startStreaming(streamType::color); });
	connect(ui.rgbStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_COLOR); });
	connect(ui.leftStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED1); });
	connect(ui.rightStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED2); });
	
	connect(ui.captrueImage, &QPushButton::clicked, [this] {capture(); });
	connect(ui.rgbCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_COLOR); });
	connect(ui.leftCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED1); });
	connect(ui.rightCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED2); });

	connect(ui.stopStreaming, &QPushButton::clicked, [this] {stopStreaming(); });
	

	connect(ui.startCalibration, &QPushButton::clicked, [this] {calibration(); });
}

void CalibrationModule::startStreaming(streamType st) {

	cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);

	m_device->EnableEmitter(0.0f);
	m_device->selectSensorAndStreamProps();



	int numSquares = numCornersHor * numCornersVer;
	cv::Size board_sz = cv::Size(numCornersHor, numCornersVer);
	m_streamingAll = true;

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
	}
}

void CalibrationModule::capture() {
	capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
	capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
	capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
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
	m_streamingAll = false;
	m_device->stopStreaming(RS_400_SENSOR::RGB_CAMERA);
	m_device->stopStreaming(RS_400_SENSOR::STEREO_MODULE);
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