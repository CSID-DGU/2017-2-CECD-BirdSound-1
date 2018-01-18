#include "MainQtApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainQtApplication w;
	w.show();
	return a.exec();
}
