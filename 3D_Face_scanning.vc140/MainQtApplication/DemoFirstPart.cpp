#include "DemoFirstPart.hpp"
#include "../DepthModule/device.h"
#include "opencv2\opencv.hpp"
#include <thread>

using namespace realsense;

DemoFirstPart::DemoFirstPart(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	m_streamingColor = false;
	m_streamingDepth = false;
	string devSerialNumber = getFirstSerial();
	m_device = new Device(devSerialNumber);
	ui.camName->setText(toQstr(m_device->info.name));
	ui.serialNum->setText(toQstr(m_device->info.serial));
	ui.firmwareVer->setText(toQstr(m_device->info.fw_ver));

	connect(ui.startStreaming, &QPushButton::clicked, [this] {startStreaming(); });
	connect(ui.capture, &QPushButton::clicked, [this] {capture(); });
	
	connect(ui.Exposure, &QSlider::valueChanged, [this] {slidertest(); });
}

void DemoFirstPart::startStreaming() {
	cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
	m_isStreaming = true;
	m_device->EnableEmitter(1.0f);
	m_device->selectSensorAndStreamProps(RS_400_STREAM_TYPE::RS400_STREAM_COLOR, RS_400_RESOLUTION::R1920_1080, RS_400_FORMAT::RGB8, RS_400_FPS::HZ30);
	m_device->selectSensorAndStreamProps(RS400_STREAM_DEPTH, R1280_720, Z16, HZ30);;


	while (m_isStreaming) {
		m_frame_color = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		m_frame_depth = m_device->capture(RS400_STREAM_DEPTH);
		rs2::colorizer colorize;
		auto fCDepth = colorize.colorize(m_frame_depth);
		cv::waitKey(1);
		QImage color_image((uchar*)m_frame_color.get_data(), m_color_width, m_color_height, QImage::Format_RGB888);
		QImage depth_image((uchar*)fCDepth.get_data(), m_depth_width, m_depth_height, QImage::Format_RGB888);
		QPixmap cbuf = QPixmap::fromImage(color_image);
		QPixmap dbuf = QPixmap::fromImage(depth_image);
		ui.rgbLabel->setPixmap(cbuf);
		ui.depthLabel->setPixmap(dbuf);
		ui.rgbLabel->setScaledContents(true);
		ui.depthLabel->setScaledContents(true);
		ui.rgbLabel->show();
		ui.depthLabel->show();
	}
	
	
 }

void DemoFirstPart::startStreaming(RS_400_STREAM_TYPE stream) {
	//m.lock();

	if (stream == RS400_STREAM_COLOR && m_streamingColor == false) {

		cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
		m_isStreaming = true;
		m_device->EnableEmitter(1.0f);
		//std::thread t1([this] {this->startStreaming(RS400_STREAM_COLOR); });
		//std::thread t2([this] {this->startStreaming(RS400_STREAM_DEPTH); });

		//t1.detach();
		//t2.detach();

		m_device->selectSensorAndStreamProps(RS_400_STREAM_TYPE::RS400_STREAM_COLOR, RS_400_RESOLUTION::R1920_1080, RS_400_FORMAT::RGB8, RS_400_FPS::HZ30);




		while (m_isStreaming) {
			auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
			cv::waitKey(1);
			QImage color_image((uchar*)fColor.get_data(), m_color_width, m_color_height, QImage::Format_RGB888);
			QPixmap cbuf = QPixmap::fromImage(color_image);
			ui.rgbLabel->setPixmap(cbuf);
			ui.rgbLabel->setScaledContents(true);
			ui.rgbLabel->show();

		}

		//m_device->selectSensorAndStreamProps(RS400_STREAM_COLOR, R1920_1080, RGB8, HZ30);
		//m_streamingColor = true;
		//cv::namedWindow("namedWindow", CV_WINDOW_AUTOSIZE);
		//while (m_streamingColor) {
		//	m_frame_color = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);

		//	cv::Mat colorImage(cv::Size(m_color_width, m_color_height), CV_8UC3, (void*)m_frame_color.get_data(), cv::Mat::AUTO_STEP);
		//	cv::waitKey(1);
		//	//QImage color_img((uchar*)m_frame_color.get_data(), m_color_width, m_color_height, QImage::Format_RGB888);
		//	QImage color_img(colorImage.data, m_color_width, m_color_height, QImage::Format_RGB888);
		//	//QImage color_image(colorImage.data, m_color_width, m_color_width, QImage::Format_RGB888);
		//	QPixmap cbuf = QPixmap::fromImage(color_img);
		//	ui.rgbLabel->setPixmap(cbuf);
		//	ui.rgbLabel->setScaledContents(true);
		//	ui.rgbLabel->show();
		//	//imshow("original", colorImage);
		//	
		//}
	}
	else if (stream == RS400_STREAM_DEPTH && m_streamingDepth == false) {
		m_device->selectSensorAndStreamProps(RS400_STREAM_DEPTH, R1280_720, Z16, HZ30);;
		m_streamingDepth = false;
		while (m_streamingDepth) {

		}

	}

}


void DemoFirstPart::capture() {
	m_isStreaming = false;


}
void DemoFirstPart::slidertest() {
	cout << "slider value changed!" << endl;
}
inline QString DemoFirstPart::toQstr(std::string str) {
	return QString::fromUtf8(str.c_str());
}