#include "CalibrationModule.hpp"
#include "WriteCalibration.hpp"
#include "../DepthModule/device.h"
#include <ctime>
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

	ui.rgbCount->setText(toQstr("0/" + to_string(max_shot_num)));
	ui.leftCount->setText(toQstr("0/" + to_string(max_shot_num)));
	ui.rightCount->setText(toQstr("0/" + to_string(max_shot_num)));
	ui.allStop->setEnabled(false);
	ui.allStart->setEnabled(true);
	ui.rgbCapture->setEnabled(false);
	ui.leftCapture->setEnabled(false);
	ui.allCapture->setEnabled(false);
	ui.startCalibrate->setEnabled(false);

	connect(ui.allStart, &QPushButton::clicked, [this] {startDetection(); });
	connect(ui.rgbStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_COLOR); });
	connect(ui.leftStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_INFRARED1); });
	connect(ui.leftStart, &QPushButton::clicked, [this] {startDetection(RS400_STREAM_INFRARED2); });

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
	ui.allStart->setEnabled(false);
	ui.allStop->setEnabled(true);
	ui.rgbCapture->setEnabled(true);
	ui.leftCapture->setEnabled(true);
	ui.allCapture->setEnabled(true);
}

void CalibrationModule::startDetection(RS_400_STREAM_TYPE stream) {
	if (stream == RS400_STREAM_COLOR) {
		ui.rgbStart->setEnabled(false);
		ui.rgbCapture->setEnabled(true);
		updateSysMsg("color camera start detection!!");
		emit startColorDetect();
	}
	else if (stream == RS400_STREAM_INFRARED1) {
		ui.leftStart->setEnabled(false);
		ui.leftCapture->setEnabled(true);
		updateSysMsg("left camera start detection!!");
		emit startIR1Detect();
	}
	else if (stream == RS400_STREAM_INFRARED2) {
		ui.leftStart->setEnabled(false);
		ui.leftCapture->setEnabled(true);
		updateSysMsg("right camera start detection!!");
		emit startIR2Detect();
	}
}
void CalibrationModule::sycCam() {
	emit syncLeft();
}

void CalibrationModule::stopDetection() {
	ui.allStop->setEnabled(false);
	ui.allStart->setEnabled(true);
	ui.rgbCapture->setEnabled(false);
	ui.leftCapture->setEnabled(false);
	ui.allCapture->setEnabled(false);
	stopDetection(RS400_STREAM_COLOR);
	stopDetection(RS400_STREAM_INFRARED1);
	stopDetection(RS400_STREAM_INFRARED2);
}

//Flag stream for calibratoin & terminate thread(signal from thread)
//store calibration data;
void CalibrationModule::flagCalibration(std::vector<std::vector<cv::Point3f>> object_points, std::vector<std::vector<cv::Point2f>> image_points, RS_400_STREAM_TYPE m_stream) {

	if (m_stream == RS400_STREAM_COLOR) {
		ui.allCapture->setEnabled(false);
		ui.startCalibrate->setEnabled(true);
		ui.rgbCapture->setEnabled(false);
		m_rgbCalib_flag = true;
		m_color_object_points = object_points;
		m_colorImage_points = image_points;
	}
	else if (m_stream == RS400_STREAM_INFRARED1) {
		ui.allCapture->setEnabled(false);
		ui.startCalibrate->setEnabled(true);
		ui.leftCapture->setEnabled(false);
		m_leftCalib_flag = true;
		m_left_object_points = object_points;
		m_leftImage_points = image_points;
	}
	else if (m_stream == RS400_STREAM_INFRARED2) {
		ui.allCapture->setEnabled(false);
		ui.startCalibrate->setEnabled(true);
		//ui.rightCapture->setEnabled(false);
		m_rightCalib_flag = true;
		m_right_object_points = object_points;
		m_rightrImage_points = image_points;
	}
}

//3개의 스트림 모두 활성화 된 경우에 실행합니다.
void CalibrationModule::calibration() {
	updateSysMsg("Start Calibration...");
	this->stopDetection();
	if ((m_rgbCalib_flag == true) && (m_leftCalib_flag == true) && (m_rightCalib_flag == true)) {
		cv::Mat color_intrinsic(3, 3, CV_32F);
		cv::Mat left_intrinsic(3, 3, CV_32F);
		cv::Mat right_intrinsic(3, 3, CV_32F);

		cv::Mat color_distCoeffs(1, 5, CV_32F);
		cv::Mat left_distCoeffs(1, 5, CV_32F);
		cv::Mat right_distCoeffs(1, 5, CV_32F);

		cv::Mat rotation_matrix_left_right;
		cv::Mat rotation_matrix_left_color;
		cv::Mat translation_matrix_left_right;
		cv::Mat translation_matrix_left_color;


		int w = 1920, h = 1080;

		auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		unique_ptr<uint32_t[]> colorBuf = unique_ptr<uint32_t[]>(new uint32_t[1920 * (1080 + 1)]);
		uint32_t *color = colorBuf.get();
		ConvertYUY2ToRGBA((uint8_t*)fColor.get_data(), 1920, 1080, (uint8_t*)color);
		cv::Mat colorImage(cv::Size(w, h), CV_8UC4, (uint8_t*)color, cv::Mat::AUTO_STEP);

		auto fLeft = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
		auto leftBuf = unique_ptr<uint8_t[]>(new uint8_t[1920 * (1080 + 1)]);
		uint8_t *left = (uint8_t*)leftBuf.get();
		ConvertLuminance16ToLuminance8((uint16_t*)fLeft.get_data(), 1920, 1080, left);
		cv::Mat leftImage(cv::Size(w, h), CV_8U, (uint8_t*)left, cv::Mat::AUTO_STEP);

		auto fRight = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
		auto rightBuf = unique_ptr<uint8_t[]>(new uint8_t[1920 * (1080 + 1)]);
		uint8_t *right = (uint8_t*)rightBuf.get();
		ConvertLuminance16ToLuminance8((uint16_t*)fRight.get_data(), 1920, 1080, right);
		cv::Mat rightImage(cv::Size(w, h), CV_8U, (uint8_t*)right, cv::Mat::AUTO_STEP);

		// calibration each Camera
		cv::calibrateCamera(m_color_object_points, m_colorImage_points, colorImage.size(), color_intrinsic, color_distCoeffs, cv::noArray(), cv::noArray());
		cv::calibrateCamera(m_left_object_points, m_leftImage_points, leftImage.size(), left_intrinsic, left_distCoeffs, cv::noArray(), cv::noArray());
		cv::calibrateCamera(m_right_object_points, m_rightrImage_points, leftImage.size(), right_intrinsic, right_distCoeffs, cv::noArray(), cv::noArray());


			

			


		// stereo calibration IR Left-Right
		stereoCalibrate(m_left_object_points, m_leftImage_points, m_rightrImage_points, left_intrinsic, left_distCoeffs, right_intrinsic, right_distCoeffs, cv::Size(-1, -1), rotation_matrix_left_right, translation_matrix_left_right, cv::noArray(), cv::noArray());
		cv::Mat R1, R2, P1, P2, Q;
		cv::stereoRectify(left_intrinsic, left_distCoeffs, right_intrinsic, right_distCoeffs, leftImage.size(), rotation_matrix_left_right, translation_matrix_left_right, R1, R2, P1, P2, Q);

		// stereo calibration RGB-IR Left
		cv::Mat RR1, RR2, PP1, PP2, QQ;
		stereoCalibrate(m_left_object_points, m_leftImage_points, m_colorImage_points, left_intrinsic, left_distCoeffs, color_intrinsic, color_distCoeffs, cv::Size(-1, -1), rotation_matrix_left_color, translation_matrix_left_color, cv::noArray(), cv::noArray());
		cv::stereoRectify(left_intrinsic, left_distCoeffs, color_intrinsic, color_distCoeffs, leftImage.size(), rotation_matrix_left_color, translation_matrix_left_color, R1, R2, P1, P2, Q);

		int resolutionLR[2] = { w, h };
		double focalLengthLeft[2] = { left_intrinsic.at<double>(0,0), left_intrinsic.at<double>(1,1) };
		double principalPointLeft[2] = { left_intrinsic.at<double>(0,2), left_intrinsic.at<double>(1,2) };
		double distortionLeft[5] = { left_distCoeffs.at<double>(0,0), left_distCoeffs.at<double>(0,1), left_distCoeffs.at<double>(0,2), left_distCoeffs.at<double>(0,3), left_distCoeffs.at<double>(0,4) };

		double focalLengthRight[2] = { right_intrinsic.at<double>(0,0), right_intrinsic.at<double>(1,1) };
		double principalPointRight[2] = { right_intrinsic.at<double>(0,2), right_intrinsic.at<double>(1,2) };
		double distortionRight[5] = { right_distCoeffs.at<double>(0,0), right_distCoeffs.at<double>(0,1), right_distCoeffs.at<double>(0,2), right_distCoeffs.at<double>(0,3), right_distCoeffs.at<double>(0,4) };

		/*double rotationLR[9] = { rotation_matrix_left_right.at<double>(0,0), rotation_matrix_left_right.at<double>(0,1), rotation_matrix_left_right.at<double>(0,2), rotation_matrix_left_right.at<double>(1,0), rotation_matrix_left_right.at<double>(1,1),
			rotation_matrix_left_right.at<double>(1,2), rotation_matrix_left_right.at<double>(2,0), rotation_matrix_left_right.at<double>(2,1), rotation_matrix_left_right.at<double>(2,2) };
		double translationLR[3] = { translation_matrix_left_right.at<double>(0,0), translation_matrix_left_right.at<double>(1,0), translation_matrix_left_right.at<double>(2,0) };*/

		double rotationLR[9] = { rotation_matrix_left_right.at<double>(0,0), rotation_matrix_left_right.at<double>(0,1), rotation_matrix_left_right.at<double>(0,2), rotation_matrix_left_right.at<double>(1,0), rotation_matrix_left_right.at<double>(1,1),
			rotation_matrix_left_right.at<double>(1,2), rotation_matrix_left_right.at<double>(2,0), rotation_matrix_left_right.at<double>(2,1), rotation_matrix_left_right.at<double>(2,2) };
		double translationLR[3] = { translation_matrix_left_right.at<double>(0,0), translation_matrix_left_right.at<double>(1,0), translation_matrix_left_right.at<double>(2,0) };

		int resolutionRGB[2] = { w, h };
		double focalLengthRGB[2] = { color_intrinsic.at<double>(0,0), color_intrinsic.at<double>(1,1) };
		double principalPointRGB[2] = { color_intrinsic.at<double>(0,2), color_intrinsic.at<double>(1,2) };
		double distortionRGB[5] = { color_distCoeffs.at<double>(0,0), color_distCoeffs.at<double>(0,1), color_distCoeffs.at<double>(0,2), color_distCoeffs.at<double>(0,3), color_distCoeffs.at<double>(0,4) };

		/*double rotationLC[9] = { rotation_matrix_left_color.at<double>(0,0), rotation_matrix_left_color.at<double>(0,1), rotation_matrix_left_color.at<double>(0,2), rotation_matrix_left_color.at<double>(1,0), rotation_matrix_left_color.at<double>(1,1),
			rotation_matrix_left_color.at<double>(1,2), rotation_matrix_left_color.at<double>(2,0), rotation_matrix_left_color.at<double>(2,1), rotation_matrix_left_color.at<double>(2,2) };
		double translationLC[3] = { translation_matrix_left_color.at<double>(0,0), translation_matrix_left_color.at<double>(1,0), translation_matrix_left_color.at<double>(2,0) };*/

		double rotationLC[9] = { rotation_matrix_left_color.at<double>(0,0), rotation_matrix_left_color.at<double>(0,1), rotation_matrix_left_color.at<double>(0,2), rotation_matrix_left_color.at<double>(1,0), rotation_matrix_left_color.at<double>(1,1),
			rotation_matrix_left_color.at<double>(1,2), rotation_matrix_left_color.at<double>(2,0), rotation_matrix_left_color.at<double>(2,1), rotation_matrix_left_color.at<double>(2,2) };
		double translationLC[3] = { translation_matrix_left_color.at<double>(0,0), translation_matrix_left_color.at<double>(1,0), translation_matrix_left_color.at<double>(2,0) };


		string fileName = "Custom_CalibrationParameters.xml";

		CalibParamXmlWrite::WriteCustomCalibrationParametersToFile(fileName, resolutionLR, focalLengthLeft, principalPointLeft, distortionLeft, focalLengthRight,
			principalPointRight, distortionRight, rotationLR, translationLR, 1, resolutionRGB, focalLengthRGB, principalPointRGB,
			distortionRGB, rotationLC, translationLC);
		updateSysMsg("Calibration Complete. Saved as " + fileName);


		//캘리브 결과
		cv::Mat colorImageBGR;
		cv::Mat Calibrated;
		cv::cvtColor(colorImage, colorImageBGR, CV_RGBA2BGR);
		undistort(colorImageBGR, Calibrated, color_intrinsic, color_distCoeffs);
		cv::resize(colorImageBGR, colorImageBGR, cv::Size(1024, 576));
		cv::resize(Calibrated, Calibrated, cv::Size(1024, 576));
		imshow("Original", colorImageBGR);
		imshow("After Calibratoin", Calibrated);

		cv::Mat leftCalibrated;
		undistort(leftImage, leftCalibrated, left_intrinsic, left_distCoeffs);
		cv::resize(leftImage, leftImage, cv::Size(1024, 576));
		cv::resize(leftCalibrated, leftCalibrated, cv::Size(1024, 576));
		imshow("Left origin", leftImage);
		imshow("Left After Calibratoin", leftCalibrated);

		cv::Mat rightCalibrated;
		undistort(rightImage, rightCalibrated, right_intrinsic, right_distCoeffs);
		cv::resize(rightImage, rightImage, cv::Size(1024, 576));
		cv::resize(rightCalibrated, rightCalibrated, cv::Size(1024, 576));
		imshow("Right origin", rightImage);
		imshow("Right After Calibratoin", rightCalibrated);
		cv::waitKey(1);
	}

	//if (m_rgbCalib_flag == true) {
	//	cv::Mat intrinsic = cv::Mat(3, 3, CV_32F);
	//	cv::Mat distCoeffs = cv::Mat(1, 5, CV_32F);
	//	std::vector<cv::Mat> rvecs;
	//	std::vector<cv::Mat> tvecs;

	//	int w = 1920, h = 1080;
	//	auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
	//	unique_ptr<uint32_t[]> colorBuf = unique_ptr<uint32_t[]>(new uint32_t[1920 * (1080 + 1)]);
	//	uint32_t *color = colorBuf.get();
	//	ConvertYUY2ToRGBA((uint8_t*)fColor.get_data(), 1920, 1080, (uint8_t*)color);
	//	cv::Mat colorImage(cv::Size(w, h), CV_8UC4, (uint8_t*)color, cv::Mat::AUTO_STEP);



	//	cv::calibrateCamera(m_color_object_points, m_colorImage_points, colorImage.size(), intrinsic, distCoeffs, rvecs, tvecs);


	//	//캘리브 결과
	//	cv::Mat colorImageBGR;
	//	cv::Mat Calibrated;
	//	cv::cvtColor(colorImage, colorImageBGR, CV_RGBA2BGR);
	//	undistort(colorImageBGR, Calibrated, intrinsic, distCoeffs);
	//	cv::resize(colorImageBGR, colorImageBGR, cv::Size(1024, 576));
	//	cv::resize(Calibrated, Calibrated, cv::Size(1024, 576));
	//	imshow("Original", colorImageBGR);
	//	imshow("After Calibratoin", Calibrated);
	//	cv::waitKey(1);



	//	ofstream myfile;
	//	myfile.open("RGB Calibration result.txt");
	//	
	//	myfile << "Focal length x : " << intrinsic.at<double>(0, 0) <<"\n"; 
	//	myfile << "Focal length y : " << intrinsic.at<double>(1, 1) << "\n";
	//	myfile << "Principal point x : " << intrinsic.at<double>(0, 2) << "\n";
	//	myfile << "Principal point y : " << intrinsic.at<double>(1, 2) << "\n";

	//	myfile << "Distortion Coefficient k1 : " << distCoeffs.at<double>(0, 0) << "\n";
	//	myfile << "Distortion Coefficient k2 : " << distCoeffs.at<double>(0, 1) << "\n";
	//	myfile << "Distortion Coefficient p1 : " << distCoeffs.at<double>(0, 2) << "\n";
	//	myfile << "Distortion Coefficient p2 : " << distCoeffs.at<double>(0, 3) << "\n";
	//	myfile << "Distortion Coefficient k3 : " << distCoeffs.at<double>(0, 4) << "\n";
	//	myfile.close();

	//	//file write test

	//	/*cv::FileStorage fs("RGB.xml", cv::FileStorage::WRITE);
	//	fs << "CAMERA_MATRIX_INTRINSIC" << intrinsic;
	//	fs << "DISTORTION_COEFFECIENTS" << distCoeffs;
	//	fs.release();*/
	//}
	//if () {
	//	using namespace cv;
	//	Mat CM1 = Mat(3, 3, CV_64FC1);
	//	Mat CM2 = Mat(3, 3, CV_64FC1);
	//	Mat D1, D2;
	//	Mat R, T, E, F;

	//	int w = 1920, h = 1080;
	//	auto fLeft = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
	//	auto leftBuf = unique_ptr<uint8_t[]>(new uint8_t[1920 * (1080 + 1)]);
	//	uint8_t *left = (uint8_t*)leftBuf.get();
	//	ConvertLuminance16ToLuminance8((uint16_t*)fLeft.get_data(), 1920, 1080, left);
	//	cv::Mat leftImage(cv::Size(w, h), CV_8U, (uint8_t*)left, cv::Mat::AUTO_STEP);
	//	stereoCalibrate(m_left_object_points, m_leftImage_points, m_rightrImage_points,
	//		CM1, D1, CM2, D2, leftImage.size(), R, T, E, F);
	//	Mat R1, R2, P1, P2, Q;
	//	stereoRectify(CM1, D1, CM2, D2, leftImage.size(), R, T, R1, R2, P1, P2, Q);

	//	ofstream myfile;
	//	myfile.open("Left Calibration result.txt");

	//	myfile << "Left Focal length x : " << CM1.at<double>(0, 0) << "\n";
	//	myfile << "Left Focal length y : " << CM1.at<double>(1, 1) << "\n";
	//	myfile << "Left Principal point x : " << CM1.at<double>(0, 2) << "\n";
	//	myfile << "Left Principal point y : " << CM1.at<double>(1, 2) << "\n";

	//	myfile << "Left Distortion Coefficient k1 : " << D1.at<double>(0, 0) << "\n";
	//	myfile << "Left Distortion Coefficient k2 : " << D1.at<double>(0, 1) << "\n";
	//	myfile << "Left Distortion Coefficient p1 : " << D1.at<double>(0, 2) << "\n";
	//	myfile << "Left Distortion Coefficient p2 : " << D1.at<double>(0, 3) << "\n";
	//	myfile << "LEft Distortion Coefficient k3 : " << D1.at<double>(0, 4) << "\n";
	//	myfile.close();


	//	myfile.open("Right Calibration result.txt");

	//	myfile << "Right Focal length x : " << CM2.at<double>(0, 0) << "\n";
	//	myfile << "Right Focal length y : " << CM2.at<double>(1, 1) << "\n";
	//	myfile << "Right Principal point x : " << CM2.at<double>(0, 2) << "\n";
	//	myfile << "Right Principal point y : " << CM2.at<double>(1, 2) << "\n";

	//	myfile << "Right Distortion Coefficient k1 : " << D2.at<double>(0, 0) << "\n";
	//	myfile << "Right Distortion Coefficient k2 : " << D2.at<double>(0, 1) << "\n";
	//	myfile << "Right Distortion Coefficient p1 : " << D2.at<double>(0, 2) << "\n";
	//	myfile << "Right Distortion Coefficient p2 : " << D2.at<double>(0, 3) << "\n";
	//	myfile << "Right Distortion Coefficient k3 : " << D2.at<double>(0, 4) << "\n";
	//	myfile.close();

	//	myfile.open("Stereo Calibration result.txt");

	//	myfile << "Roate 0 : " << R.at<double>(0, 0) << "\n";
	//	myfile << "Roate 1 : " << R.at<double>(0, 1) << "\n";
	//	myfile << "Roate 2 : " << R.at<double>(0, 2) << "\n";
	//	myfile << "Roate 3 : " << R.at<double>(1, 0) << "\n";
	//	myfile << "Roate 4 : " << R.at<double>(1, 1) << "\n";
	//	myfile << "Roate 5 : " << R.at<double>(1, 2) << "\n";
	//	myfile << "Roate 6 : " << R.at<double>(2, 0) << "\n";
	//	myfile << "Roate 7 : " << R.at<double>(2, 1) << "\n";
	//	myfile << "Roate 8 : " << R.at<double>(2, 2) << "\n";

	//	myfile << "Translation 0 : " << R.at<double>(0, 0) << "\n";
	//	myfile << "Translation 1: " << R.at<double>(1, 0) << "\n";
	//	myfile << "Translation 2: " << R.at<double>(2, 0) << "\n";

	//	myfile.close();



	//}


}


inline QString CalibrationModule::toQstr(std::string str) {
	return QString::fromUtf8(str.c_str());
}

void CalibrationModule::updateCaptureNum(int captureNum, RS_400_STREAM_TYPE m_stream) {

	string  tmp = "/" + to_string(max_shot_num);
	if (m_stream == RS400_STREAM_COLOR) {
		ui.rgbCount->setText(toQstr(to_string(captureNum) + tmp));
		updateSysMsg("rgb camera capture!!");
	}
	else if (m_stream == RS400_STREAM_INFRARED1) {
		ui.leftCount->setText(toQstr(to_string(captureNum) + tmp));
		updateSysMsg("left camera capture!!");
	}
	else if (m_stream == RS400_STREAM_INFRARED2) {
		ui.rightCount->setText(toQstr(to_string(captureNum) + tmp));
		updateSysMsg("right camera capture!!");
	}
}
