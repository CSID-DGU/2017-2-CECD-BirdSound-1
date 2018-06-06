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

	ui.rgbCount->setText(toQstr("0/" + max_shot_num));
	ui.leftCount->setText(toQstr("0/" + max_shot_num));
	ui.rightCount->setText(toQstr("0/" + max_shot_num));
	
	connect(ui.allStart, &QPushButton::clicked, [this] {startDetection(); });
	connect(ui.rgbStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_COLOR); });
	connect(ui.leftStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_INFRARED1); });
	//connect(ui.rightStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_INFRARED2); });
	
	connect(ui.allStop, &QPushButton::clicked, [this] {stopDetection(); });
	connect(ui.rgbStop, &QPushButton::clicked, [this] {stopDetection(RS400_STREAM_COLOR); });
	connect(ui.leftStop, &QPushButton::clicked, [this] {stopDetection(RS400_STREAM_INFRARED1); });
	connect(ui.leftStop, &QPushButton::clicked, [this] {stopDetection(RS400_STREAM_INFRARED2); });
	

	connect(ui.startCalibrate, &QPushButton::clicked, [this] {calibration(); });

	//Start each Streaming
	WorkerThread *workerColor = new WorkerThread(m_device, RS_400_STREAM_TYPE::RS400_STREAM_COLOR, max_shot_num);
	WorkerThread *workerIR1 = new WorkerThread(m_device, RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1, max_shot_num);
	WorkerThread *workerIR2 = new WorkerThread(m_device, RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2, max_shot_num);
	connect(workerColor, &WorkerThread::updateColorPixmap, this, &CalibrationModule::updateColor);
	connect(workerIR1, &WorkerThread::updateIR1Pixmap, this, &CalibrationModule::updateIR1);
	connect(workerIR2, &WorkerThread::updateIR2Pixmap, this, &CalibrationModule::updateIR2);
	workerColor->start();
	workerIR1->start();
	workerIR2->start();

	//Detection set/unset
	connect(this, &CalibrationModule::startColorDetect, workerColor, &WorkerThread::setDetection);
	connect(this, &CalibrationModule::startIR1Detect, workerIR1, &WorkerThread::setDetection);
	connect(this, &CalibrationModule::startIR1Detect, workerIR2, &WorkerThread::setDetection);

	connect(this, &CalibrationModule::stopColorDetect, workerColor, &WorkerThread::unsetDetection);
	connect(this, &CalibrationModule::stopIR1Detect, workerIR1, &WorkerThread::unsetDetection);
	connect(this, &CalibrationModule::stopIR1Detect, workerIR2, &WorkerThread::unsetDetection);

	//set capture signal
	connect(ui.allCapture, &QPushButton::clicked, workerColor, &WorkerThread::capture);
	connect(ui.allCapture, &QPushButton::clicked, workerIR1, &WorkerThread::capture);
	connect(ui.allCapture, &QPushButton::clicked, workerIR2, &WorkerThread::capture);
	connect(ui.rgbCapture, &QPushButton::clicked, workerColor, &WorkerThread::capture);
	connect(ui.leftCapture, &QPushButton::clicked, workerIR1, &WorkerThread::capture);
	connect(ui.leftCapture, &QPushButton::clicked, workerIR2, &WorkerThread::capture);
	//connect(ui.rightCapture, &QPushButton::clicked, workerIR2, &WorkerThread::capture);

	//update Capture number
	connect(workerColor, &WorkerThread::updateCapture, this, &CalibrationModule::updateCaptureNum);
	connect(workerIR1, &WorkerThread::updateCapture, this, &CalibrationModule::updateCaptureNum);
	connect(workerIR2, &WorkerThread::updateCapture, this, &CalibrationModule::updateCaptureNum);

//	connect(workerIR1, &WorkerThread::syncIRCam, this, &CalibrationModule::sycCam);
	//notify ready 2 calibration
	connect(workerColor, &WorkerThread::ready2Calibration, this, &CalibrationModule::flagCalibration);
	connect(workerIR1, &WorkerThread::ready2Calibration, this, &CalibrationModule::flagCalibration);
	connect(workerIR2, &WorkerThread::ready2Calibration, this, &CalibrationModule::flagCalibration);
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
void CalibrationModule::sycCam() {
	emit syncLeft();
}

void CalibrationModule::startStreaming() {
	
}

//Flag stream for calibratoin & terminate thread(signal from thread)
//store calibration data;
void CalibrationModule::flagCalibration(std::vector<std::vector<cv::Point3f>> object_points, std::vector<std::vector<cv::Point2f>> image_points, RS_400_STREAM_TYPE m_stream) {
	
	if (m_stream == RS400_STREAM_COLOR) {
		ui.rgbCapture->setEnabled(false);
		m_rgbCalib_flag = true;
		m_color_object_points = object_points;
		m_colorImage_points = image_points;
	}
	else if (m_stream == RS400_STREAM_INFRARED1) {
		ui.leftCapture->setEnabled(false);
		m_leftCalib_flag = true;
		m_left_object_points = object_points;
		m_leftImage_points = image_points;
	}
	else if (m_stream == RS400_STREAM_INFRARED2) {
		//ui.rightCapture->setEnabled(false);
		m_rightCalib_flag = true;
		m_right_object_points = object_points;
		m_rightrImage_points = image_points;
	}
}

//3개의 스트림 모두 활성화 된 경우에 실행합니다.
void CalibrationModule::calibration() {

	
	if (m_rgbCalib_flag == true) {
		cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
		cv::Mat distCoeffs;
		std::vector<cv::Mat> rvecs;
		std::vector<cv::Mat> tvecs;

		int w = 1920, h = 1080;
		auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		unique_ptr<uint32_t[]> colorBuf = unique_ptr<uint32_t[]>(new uint32_t[1920 * (1080 + 1)]);
		uint32_t *color = colorBuf.get();
		ConvertYUY2ToRGBA((uint8_t*)fColor.get_data(), 1920, 1080, (uint8_t*)color);
		cv::Mat colorImage(cv::Size(w, h), CV_8UC4, (uint8_t*)color, cv::Mat::AUTO_STEP);

		cv::calibrateCamera(m_color_object_points, m_colorImage_points, colorImage.size(), intrinsic, distCoeffs, rvecs, tvecs);
		
		
		//캘리브 결과
		cv::Mat colorImageBGR;
		cv::Mat Calibrated;
		cv::cvtColor(colorImage, colorImageBGR, CV_RGBA2BGR);
		undistort(colorImageBGR, Calibrated, intrinsic, distCoeffs);
		cv::resize(colorImageBGR, colorImageBGR, cv::Size(1024, 576));
		cv::resize(Calibrated, Calibrated, cv::Size(1024, 576));
		imshow("Original", colorImageBGR);
		imshow("After Calibratoin", Calibrated);
		cv::waitKey(1);


		//file write test
		
		cv::FileStorage fs("RGB.xml",cv::FileStorage::WRITE);
		fs << "CAMERA_MATRIX_INTRINSIC" << intrinsic;
		fs << "DISTORTION_COEFFECIENTS" << distCoeffs;
		fs.release();
	}
	else if (m_leftCalib_flag == true) {
		cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
		cv::Mat distCoeffs;
		std::vector<cv::Mat> rvecs;
		std::vector<cv::Mat> tvecs;


		int w = 1920, h = 1080;
		auto fLeft = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		auto leftBuf = unique_ptr<uint8_t[]>(new uint8_t[1920 * (1080 + 1)]);
		uint8_t *left = (uint8_t*)leftBuf.get();
		ConvertLuminance16ToLuminance8((uint16_t*)fLeft.get_data(), 1920, 1080, left);
		cv::Mat leftImage(cv::Size(w, h), CV_8U, (uint8_t*)left, cv::Mat::AUTO_STEP);
		cv::calibrateCamera(m_left_object_points, m_leftImage_points, leftImage.size(), intrinsic, distCoeffs, rvecs, tvecs);

		
		//캘리브 결과
		cv::Mat Calibrated;
		undistort(leftImage, Calibrated, intrinsic, distCoeffs);
		cv::resize(leftImage, leftImage, cv::Size(1024, 576));
		cv::resize(Calibrated, Calibrated, cv::Size(1024, 576));
		imshow("Original", leftImage);
		imshow("After Calibratoin", Calibrated);
		cv::waitKey(1);
		
		cv::FileStorage fs("LEFT.xml", cv::FileStorage::WRITE);
		fs << "CAMERA_MATRIX_INTRINSIC" << intrinsic;
		fs << "DISTORTION_COEFFECIENTS" << distCoeffs;
		fs.release();
	}
	else if (m_rightCalib_flag == true) {
		cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
		cv::Mat distCoeffs;
		std::vector<cv::Mat> rvecs;
		std::vector<cv::Mat> tvecs;

		int w = 1920, h = 1080;
		auto fRight = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
		auto rightBuf = unique_ptr<uint8_t[]>(new uint8_t[1920*(1080 + 1)]);
		uint8_t *right = (uint8_t*)rightBuf.get();
		ConvertLuminance16ToLuminance8((uint16_t*)fRight.get_data(), 1920, 1080, right);
		cv::Mat rightImage(cv::Size(w, h), CV_8U, (uint8_t*)right, cv::Mat::AUTO_STEP);
		cv::calibrateCamera(m_right_object_points, m_rightrImage_points, rightImage.size(), intrinsic, distCoeffs, rvecs, tvecs);


		//캘리브 결과
		cv::Mat Calibrated;
		undistort(rightImage, Calibrated, intrinsic, distCoeffs);
		cv::resize(rightImage, rightImage, cv::Size(1024, 576));
		cv::resize(Calibrated, Calibrated, cv::Size(1024, 576));
		imshow("Original", rightImage);
		imshow("After Calibratoin", Calibrated);
		cv::waitKey(1);

		cv::FileStorage fs("RIGHT.xml", cv::FileStorage::WRITE);
		fs << "CAMERA_MATRIX_INTRINSIC" << intrinsic;
		fs << "DISTORTION_COEFFECIENTS" << distCoeffs;
		fs.release();

	}
	if ((m_leftCalib_flag == true) && (m_rightCalib_flag == true)) {
		using namespace cv;
		Mat CM1 = Mat(3, 3, CV_64FC1);
		Mat CM2 = Mat(3, 3, CV_64FC1);
		Mat D1, D2;
		Mat R, T, E, F;

		int w = 1920, h = 1080;
		auto fLeft = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		auto leftBuf = unique_ptr<uint8_t[]>(new uint8_t[1920 * (1080 + 1)]);
		uint8_t *left = (uint8_t*)leftBuf.get();
		ConvertLuminance16ToLuminance8((uint16_t*)fLeft.get_data(), 1920, 1080, left);
		cv::Mat leftImage(cv::Size(w, h), CV_8U, (uint8_t*)left, cv::Mat::AUTO_STEP);
		stereoCalibrate(m_left_object_points, m_leftImage_points, m_rightrImage_points,
			CM1, D1, CM2, D2, leftImage.size(), R, T, E, F, CALIB_FIX_INTRINSIC,
			cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 100, 1e-5));
		Mat R1, R2, P1, P2, Q;
		stereoRectify(CM1, D1, CM2, D2, leftImage.size(), R, T, R1, R2, P1, P2, Q);

	}

	
}


inline QString CalibrationModule::toQstr(std::string str) {
	return QString::fromUtf8(str.c_str());
}

void CalibrationModule::updateCaptureNum(int captureNum, RS_400_STREAM_TYPE m_stream) {

	string  tmp = "/" + max_shot_num;
	if (m_stream == RS400_STREAM_COLOR) {
		ui.rgbCount->setText(toQstr(to_string(captureNum) + tmp));
	}
	else if (m_stream == RS400_STREAM_INFRARED1) {
		ui.leftCount->setText(toQstr(to_string(captureNum) + tmp));
	}
	else if (m_stream == RS400_STREAM_INFRARED2) {
		ui.rightCount->setText(toQstr(to_string(captureNum) + tmp));
	}
}
