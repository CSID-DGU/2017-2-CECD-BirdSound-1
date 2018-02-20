#include "DemoFirstPart.hpp"
#include "../DepthModule/device.h"

using namespace realsense;

DemoFirstPart::DemoFirstPart(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	//string devSerialNumber = getFirstSerial();
	//m_device = new Device(devSerialNumber);
	//ui.camName->setText(toQstr(m_device->info.name));
	//ui.serialNum->setText(toQstr(m_device->info.serial));
	//ui.firmwareVer->setText(toQstr(m_device->info.fw_ver));

	//connect(ui.startStreaming, &QPushButton::clicked, [this] {startStreaming(streamType::color); });
	//connect(ui.rgbStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_COLOR); });
	//connect(ui.leftStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED1); });
	//connect(ui.rightStart, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED2); });

	//connect(ui.captrueImage, &QPushButton::clicked, [this] {capture(); });
	//connect(ui.rgbCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_COLOR); });
	//connect(ui.leftCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED1); });
	//connect(ui.rightCapture, &QPushButton::clicked, [this] {capture(RS400_STREAM_INFRARED2); });

	//connect(ui.stopStreaming, &QPushButton::clicked, [this] {stopStreaming(); });


	//connect(ui.startCalibration, &QPushButton::clicked, [this] {calibration(); });
}
