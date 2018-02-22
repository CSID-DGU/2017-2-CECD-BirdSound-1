#include "ScanModule.hpp"
ScanModule::ScanModule(QWidget *parent) : QWidget(parent){
	ui.setupUi(this);
	
	connect(ui.NextButton, SIGNAL(clicked()), this, SLOT(on_NextButton_clicked()));
}
void ScanModule::on_NextButton_clicked() {
	printf("asd");
}