#include "ScanModule.hpp"
ScanModule::ScanModule(QWidget *parent) : QWidget(parent){
	ui.setupUi(this);
	
	connect(ui.NextButton, SIGNAL(clicked()), this, SLOT(on_NextButton_clicked()));
}
void ScanModule::on_NextButton_clicked() {
	//data가지고 ALign 처리 


	//제일 마지막
	reg->setData(data);
	this->close();
	reg->show();
}