#include "CalibrationModule.h"
#include "opencv2/opencv.hpp"
#undef foreach //Q_FOREACH
#include "librealsense2\rs.hpp"
#include "../DepthModule/device.h"
#include <fstream>


CalibrationModule::CalibrationModule(QWidget *parent): QMainWindow(parent)
{
	
	ui.setupUi(this);
	//connect(ui.startStreaming, SIGNAL(clicked()), this, SLOT());
	connect(ui.startStreaming, &QPushButton::clicked, [this] {startStreaming(streamType::color); });

}

void CalibrationModule::startStreaming(streamType st) {

	rs2::context ctx;
	rs2::device_list devices = ctx.query_devices();
	std::string serialNum = devices[0].get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);

	RS400Device* device = new RS400Device;

	auto camera_info = device->InitializeCamera(serialNum);
	device->EnableEmitter(0.0f);
	device->EnableAutoExposure(1.0f);
	device->SetMediaMode(1920, 1080, 15, 1920, 1080, camera_info.isRGB);
	device->StartCapture();
	int height = 1080;
	int width = 1920;

	ofstream colorhex, lefthex, righthex;
	colorhex.open("colorhex.txt");
	lefthex.open("lefthex.txt");
	righthex.open("righthex.txt");

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//colorhex << std::hex << device->colorImage[i*width + j] << endl;
			lefthex << "0x" << std::hex << static_cast<int>(device->leftImage[i*width + j]);
			righthex << "0x" << std::hex << static_cast<int>(device->rightImage[i*width + j]);
		}
		lefthex << endl;
		righthex << endl;
	}
	


	//Realsense realsense;
	//realsense.init();
	//realsense.info(0);
	//realsense.startStreaming(0, RS2_FORMAT_BGR8, 0);
	//rs2::frame frame = realsense.capture(0, 0);
	///*vtkPoints *points = realsense.frameToVtkPoints(frame);

	//realsense.stopStreaming(0, 0);
	//realsense.MeshConstruct(points);
	//rs2::colorizer color_map;
	//rs2::pipeline pipe;
	//pipe.start();
	//rs2::frameset data = pipe.wait_for_frames();
	//rs2::frame color = data.get_color_frame();*/
	//cv::Mat color_mat = RS400::frameToMat(frame);
	//

	//const int w = 1920;
	//const int h = 1080;
	////cv::Mat cv::image(Size(w, h), CV_8UC3, (void*)depth.get_data(), Mat::AUTO_STEP);
	////cv::Mat image(cv::Size(w, h), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP);
	//cv::imshow("WINdow", color_mat);
	//
	//std::cout << "A";
	////auto image2 = new QImage(image.data, w, h, QImage::Format_RGB888);
	
	
	//QPixmap buf = QPixmap::fromImage(*image2);
	//ui.irCam1->setIma
	//ui.label->setPixmap(buf);
}



