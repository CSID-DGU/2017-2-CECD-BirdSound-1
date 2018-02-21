#include "DemoFirstPart.hpp"
#include "../DepthModule/device.h"
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
	//connect(ui.rgbStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_COLOR); });
	//connect(ui.leftStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED1); });
	//connect(ui.rightStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED2); });

	//connect(ui.captrueImage, &QPushButton::clicked, [this] {capture(); });
	connect(ui.capture, &QPushButton::clicked, [this] {capture(); });
	//connect(ui.leftCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED1); });
	//connect(ui.rightCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED2); });

	//connect(ui.stopStreaming, &QPushButton::clicked, [this] {stopStreaming(); });


	//connect(ui.startCalibration, &QPushButton::clicked, [this] {calibration(); });
}

void DemoFirstPart::startStreaming() {

	m_isStreaming = true;
	m_device->EnableEmitter(1.0f);
	std::thread t1([this] {this->startStreaming(RS400_STREAM_COLOR); });
	std::thread t2([this] {this->startStreaming(RS400_STREAM_DEPTH); });

	t1.detach();
	t2.detach();
	/*m_device->selectSensorAndStreamProps(RS400_STREAM_COLOR,R1920_1080,RGB8,HZ30);
	m_device->selectSensorAndStreamProps(RS400_STREAM_DEPTH, R1280_720, Z16, HZ30);


	while (m_isStreaming) {
		auto m_frame_color = m_device->capture(RS400_STREAM_COLOR);
		auto m_frame_depth = m_device->capture(RS400_STREAM_DEPTH);

		QImage color_img((uchar*)m_frame_color.get_data(), m_color_width, m_color_height, QImage::Format_RGB888);
		QPixmap cbuf = QPixmap::fromImage(color_img);
		ui.rgbLabel->setPixmap(cbuf);
		ui.rgbLabel->setScaledContents(true);
		ui.rgbLabel->show(); 
	
	}*/
	
	
 }

void DemoFirstPart::startStreaming(RS_400_STREAM_TYPE stream) {
	//m.lock();
	if (stream == RS400_STREAM_COLOR && m_streamingColor == false) {

		m_device->selectSensorAndStreamProps(RS400_STREAM_COLOR, R1920_1080, RGB8, HZ30);
		m_streamingColor = true;
		
		while (m_streamingColor) {
			m_frame_color = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);

			QImage color_img((uchar*)m_frame_color.get_data(), m_color_width, m_color_height, QImage::Format_RGB888);
			QPixmap cbuf = QPixmap::fromImage(color_img);
			ui.rgbLabel->setPixmap(cbuf);
			ui.rgbLabel->setScaledContents(true);
			ui.rgbLabel->show();
		}
	}
	else if (stream == RS400_STREAM_DEPTH && m_streamingDepth == false) {
		m_device->selectSensorAndStreamProps(RS400_STREAM_DEPTH, R1280_720, Z16, HZ30);;
		m_streamingDepth = false;
		while (m_streamingDepth) {

		}

	}

}


void DemoFirstPart::capture() {
	


}

inline QString DemoFirstPart::toQstr(std::string str) {
	return QString::fromUtf8(str.c_str());
}