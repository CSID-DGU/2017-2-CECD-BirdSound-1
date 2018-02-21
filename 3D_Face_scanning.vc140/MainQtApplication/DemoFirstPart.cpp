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
	
	//COLOR CAMERA PARAMETER
	connect(ui.Brightness, &QSlider::valueChanged, [this] {sliderHandle(ui.Brightness->objectName(), ui.Brightness->value()); });
	connect(ui.Contrast, &QSlider::valueChanged, [this] {sliderHandle(ui.Contrast->objectName(), ui.Contrast->value()); });
	connect(ui.Exposure, &QSlider::valueChanged, [this] {sliderHandle(ui.Exposure->objectName(), ui.Exposure->value()); });
	connect(ui.Gain, &QSlider::valueChanged, [this] {sliderHandle(ui.Gain->objectName(), ui.Gain->value()); });
	connect(ui.Gamma, &QSlider::valueChanged, [this] {sliderHandle(ui.Gamma->objectName(), ui.Gamma->value()); });
	connect(ui.Hue, &QSlider::valueChanged, [this] {sliderHandle(ui.Hue->objectName(), ui.Hue->value()); });
	connect(ui.Saturation, &QSlider::valueChanged, [this] {sliderHandle(ui.Saturation->objectName(), ui.Saturation->value()); });
	connect(ui.Sharpness, &QSlider::valueChanged, [this] {sliderHandle(ui.Sharpness->objectName(), ui.Sharpness->value()); });
	connect(ui.WhiteBalance, &QSlider::valueChanged, [this] {sliderHandle(ui.WhiteBalance->objectName(), ui.WhiteBalance->value()); });
	//checkbox
	connect(ui.AutoWhiteBalance, &QCheckBox::clicked, [this] {checkboxHandle(ui.AutoWhiteBalance->objectName(), ui.AutoWhiteBalance->checkState()); });
	connect(ui.AutoExposure, &QCheckBox::clicked, [this] {checkboxHandle(ui.AutoExposure->objectName(), ui.AutoExposure->checkState()); });


	//DEPTH PARAMETER
	connect(ui.Exposure_, &QSlider::valueChanged, [this] {sliderHandle(ui.Exposure_->objectName(), ui.Exposure_->value()); });
	connect(ui.Gain_2, &QSlider::valueChanged, [this] {sliderHandle(ui.Gain_2->objectName(), ui.Gain_2->value()); });
	connect(ui.LaserPower, &QSlider::valueChanged, [this] {sliderHandle(ui.LaserPower->objectName(), ui.LaserPower->value()); });

	connect(ui.MinDistance, &QSlider::valueChanged, [this] {sliderHandle(ui.MinDistance->objectName(), ui.MinDistance->value()); });
	connect(ui.MaxDistance, &QSlider::valueChanged, [this] {sliderHandle(ui.MaxDistance->objectName(), ui.MaxDistance->value()); });
	connect(ui.DecimationFilterMagnitude, &QSlider::valueChanged, [this] {sliderHandle(ui.DecimationFilterMagnitude->objectName(), ui.DecimationFilterMagnitude->value()); });
	connect(ui.SpatialFilterMagnitude, &QSlider::valueChanged, [this] {sliderHandle(ui.SpatialFilterMagnitude->objectName(), ui.SpatialFilterMagnitude->value()); });
	connect(ui.SpatialFilterSmoothAlpha, &QSlider::valueChanged, [this] {sliderHandle(ui.SpatialFilterSmoothAlpha->objectName(), ui.SpatialFilterSmoothAlpha->value()); });
	connect(ui.SpatialFilterSmoothDelta, &QSlider::valueChanged, [this] {sliderHandle(ui.SpatialFilterSmoothDelta->objectName(), ui.SpatialFilterSmoothDelta->value()); });
	connect(ui.TemporalFilterMagnitude, &QSlider::valueChanged, [this] {sliderHandle(ui.TemporalFilterMagnitude->objectName(), ui.TemporalFilterMagnitude->value()); });
	connect(ui.TemporalFilterSmoothAlpha, &QSlider::valueChanged, [this] {sliderHandle(ui.TemporalFilterSmoothAlpha->objectName(), ui.TemporalFilterSmoothAlpha->value()); });
	connect(ui.TemporalFilterSmoothDelta, &QSlider::valueChanged, [this] {sliderHandle(ui.TemporalFilterSmoothDelta->objectName(), ui.TemporalFilterSmoothDelta->value()); });
	//checkbox
	connect(ui.AutoExposure_2, &QCheckBox::clicked, [this] {checkboxHandle(ui.AutoExposure_2->objectName(), ui.AutoExposure_2->checkState()); });




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

void DemoFirstPart::checkboxHandle(QString sn, Qt::CheckState cs) {
	if (cs == 2) { cout << toStdStr(sn) << " is Checked!" << endl; } else if (cs == 0) { cout << toStdStr(sn) << " is Unchecked!" << endl; }
	
	if (sn == toQstr("AutoExposure")) {
		if (cs == 2) { 
			m_device->setOption(RGB_CAMERA, RS2_OPTION_ENABLE_AUTO_EXPOSURE, 1);
			cout << toStdStr(sn) << " is Checked!" << endl; }
		else if (cs == 0) { 
			m_device->setOption(RGB_CAMERA, RS2_OPTION_ENABLE_AUTO_EXPOSURE, 0);
			cout << toStdStr(sn) << " is Unchecked!" << endl; }
	}
	else if (sn == toQstr("AutoWhiteBalance")) {
		if (cs == 2) {
			m_device->setOption(RGB_CAMERA, RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE, 1);
			cout << toStdStr(sn) << " is Checked!" << endl;
		}
		else if (cs == 0) {
			m_device->setOption(RGB_CAMERA, RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE, 0);
			cout << toStdStr(sn) << " is Unchecked!" << endl;
		}
	}
	else if (sn == toQstr("AutoExposure_2")) {
		if (cs == 2) {
			m_device->setOption(STEREO_MODULE, RS2_OPTION_ENABLE_AUTO_EXPOSURE, 1);
			cout << toStdStr(sn) << " is Checked!" << endl;
		}
		else if (cs == 0) {
			m_device->setOption(STEREO_MODULE, RS2_OPTION_ENABLE_AUTO_EXPOSURE, 0);
			cout << toStdStr(sn) << " is Unchecked!" << endl;
		}
	}
}
void DemoFirstPart::sliderHandle(QString sn, int val) {
	
	//Color parameter(9)
	if (sn == toQstr("Brightness")) {
		m_device->setOption(RGB_CAMERA, RS2_OPTION_BRIGHTNESS, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("Contrast")) {
		m_device->setOption(RGB_CAMERA, RS2_OPTION_CONTRAST, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("Exposure")) {
		m_device->setOption(RGB_CAMERA, RS2_OPTION_EXPOSURE, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("Gain")) {
		m_device->setOption(RGB_CAMERA, RS2_OPTION_GAIN, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("Gamma")) {
		m_device->setOption(RGB_CAMERA, RS2_OPTION_GAMMA, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("Hue")) {
		m_device->setOption(RGB_CAMERA, RS2_OPTION_HUE, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("Saturation")) {
		m_device->setOption(RGB_CAMERA, RS2_OPTION_SATURATION, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("Sharpness")) {
		m_device->setOption(RGB_CAMERA, RS2_OPTION_SHARPNESS, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("WhiteBalance")) {
		int tmpval = val / 10;
		tmpval *= 10;
		m_device->setOption(RGB_CAMERA, RS2_OPTION_WHITE_BALANCE, tmpval);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	//Depth Parameter(12)
	else if (sn == toQstr("Exposure_")) {
		m_device->setOption(STEREO_MODULE, RS2_OPTION_EXPOSURE, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("Gain_2")) {
		m_device->setOption(STEREO_MODULE, RS2_OPTION_GAIN, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("LaserPower")) {
		m_device->setOption(STEREO_MODULE, RS2_OPTION_LASER_POWER, val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	/*else if (sn == toQstr("MinDistance")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("MaxDistance")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("DecimationFilterMagnitude")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("SpatialFilterMagnitude")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("SpatialFilterSmoothAlpha")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("SpatialFilterSmoothDelta")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("TemporalFilterMagnitude")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("TemporalFilterSmoothAlpha")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}
	else if (sn == toQstr("TemporalFilterSmoothDelta")) {
		m_device->setOption(STEREO_MODULE, , val);
		cout << "slider value changed! : " << toStdStr(sn) << "  value : " << val << endl;
	}*/


}

inline QString DemoFirstPart::toQstr(std::string str) {
	return QString::fromStdString(str);
}

inline std::string DemoFirstPart::toStdStr(QString str) {
	return str.toUtf8().constData();
}