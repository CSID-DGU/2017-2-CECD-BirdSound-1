#include "MainModule.hpp"
#include "../../CalibrationModule/CalibrationModule.hpp"


MainModule::MainModule(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	//버튼 초기화
	connect(ui.runCalibrationModule, &QPushButton::clicked, [this] {runCalibrationModule(); });
	connect(ui.runScanModule, &QPushButton::clicked, [this] {runScanModule(); });
	connect(ui.runViewerModule, &QPushButton::clicked, [this] {runViewerModule(); });
	connect(ui.runExpModule, &QPushButton::clicked, [this] {runExpModule(); }); 
}

void MainModule::runCalibrationModule() {
	CalibrationModule* c = new CalibrationModule();
	c->show();
}

void MainModule::runScanModule() {

}

void MainModule::runViewerModule() {
	
}

void MainModule::runExpModule() {

}