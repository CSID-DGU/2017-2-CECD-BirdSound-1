#include "ScanModule.hpp"
ScanModule::ScanModule(QWidget *parent) : QWidget(parent){
	ui.setupUi(this);
	
	connect(ui.NextButton, SIGNAL(clicked()), this, SLOT(on_NextButton_clicked()));
	connect(ui.ScanButton, SIGNAL(clicked()), this, SLOT(on_ScanButton_clicked()));
}
void ScanModule::on_NextButton_clicked() {
	//data가지고 ALign 처리 


	//제일 마지막
	reg->setData(data);
	this->close();
	reg->show();
}
void ScanModule::on_ScanButton_clicked() {
	//data가지고 ALign 처리 
	ui.ScanButton->setEnabled(false);
	ui.NextButton->setEnabled(false);

	//프로세스 처리 
	QEventLoop loop;
	QTimer::singleShot(1500, &loop, SLOT(quit()));
	loop.exec();
	qApp->processEvents();

	ui.ScanButton->setEnabled(true);
	ui.NextButton->setEnabled(true);

}