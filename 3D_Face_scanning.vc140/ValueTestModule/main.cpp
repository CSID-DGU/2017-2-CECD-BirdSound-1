#include "ValueTestModule.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ValueTestModule w;
	w.show();
	return a.exec();
}
