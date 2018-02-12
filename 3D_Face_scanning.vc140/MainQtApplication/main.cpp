#pragma warning (disable : 4996)

#include "iomodule.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IOModule w;
	w.show();
	return a.exec();
}