#include "CalibrationModule.hpp"
#include <QtWidgets/QApplication>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CalibrationModule w;
	w.show();
	return a.exec();
}
