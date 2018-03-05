#include "InitializeModule.hpp"
#include <qprogressbar.h>

InitializeModule::InitializeModule(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

}
void InitializeModule::Init() {
	int max = 100;
	int div = 10;
	ui.progressBar->setRange(0, max);
	ui.progressBar->setValue(0);
	ui.progressBar->show();
	for (int i = 1; i <= div; i++) {
		//프로세스 처리 
		QEventLoop loop;
		QTimer::singleShot(100, &loop, SLOT(quit()));
		loop.exec();
		qApp->processEvents();
		ui.progressBar->setValue(i*div);
	}
}