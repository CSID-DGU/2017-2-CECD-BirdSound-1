#include "CalibrationModule.h"
#include <QtWidgets/QApplication>
//#undef foreach //Q_FOREACH
//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include "../DepthModule/device.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CalibrationModule w;
	w.show();
	return a.exec();
}
