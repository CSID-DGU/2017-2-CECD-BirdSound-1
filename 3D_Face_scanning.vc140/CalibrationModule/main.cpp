#include "CalibrationModule.h"
#include <QtWidgets/QApplication>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
int main(int argc, char *argv[])
{
	VideoCapture cap;
	
	while (1) {
		CvMat test;
		Mat frame;
		cap >> frame;
		if (frame.empty()) break;
		imshow("ok", frame);
		if (waitKey(10) == 27) break;
	}

	QApplication a(argc, argv);
	CalibrationModule w;
	w.show();
	return a.exec();
}
