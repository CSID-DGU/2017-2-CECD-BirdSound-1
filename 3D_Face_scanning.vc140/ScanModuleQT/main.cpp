#include "scanmoduleqt.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ScanModuleQT w;
	w.show();
	return a.exec();
}
