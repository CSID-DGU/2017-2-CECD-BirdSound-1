#include "CalibrationModule.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CalibrationModule w;
	w.show();
	return a.exec();
}
