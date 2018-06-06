#include "MainModule.hpp"
#include "CalibrationModule.hpp"
#include "ScanModule.hpp"
#include "RegistrationModule.hpp"
#include "iomodule.h"
#include "ApplicationConfig.hpp"
#include <QDesktopWidget>

MainModule::MainModule(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	//버튼 초기화
	connect(ui.runCalibrationModule, &QPushButton::clicked, [this] {runCalibrationModule(); });
	connect(ui.runScanModule, &QPushButton::clicked, [this] {runScanModule(); });
	connect(ui.runViewerModule, &QPushButton::clicked, [this] {runViewerModule(); });
	connect(ui.runExpModule, &QPushButton::clicked, [this] {runExpModule(); }); 


	ui.RecentTable->setShowGrid(false);
	ui.RecentTable->setGeometry(QApplication::desktop()->screenGeometry());
	ui.RecentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.RecentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.RecentTable->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(ui.RecentTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(cellSelected(int, int)));
	//
	ui.RecentTable->insertRow(ui.RecentTable->rowCount()); 
	ui.RecentTable->setItem(0, 0, new QTableWidgetItem("정종현"));
	ui.RecentTable->setItem(0, 1, new QTableWidgetItem("950116"));
	ui.RecentTable->setItem(0, 2, new QTableWidgetItem("2MB"));
	ui.RecentTable->setItem(0, 3, new QTableWidgetItem("C://"));
	for (int i = 0; i < 20; i++) {
		ui.RecentTable->insertRow(ui.RecentTable->rowCount());
		ui.RecentTable->setItem(1+i, 0, new QTableWidgetItem("JungJongHyun"));
	}
}
void MainModule::cellSelected(int nRow, int nCol)
{
	QMessageBox::information(this, "",
		"Cell at row "+QString::number(nRow)+
		" column "+QString::number(nCol)+
		" was double clicked.");
	runViewerModule();
}

//void MainModule::loadDB() {
//	auto app_config = Config::get_instance();
//	ifstream file(app_config.person_db);
//	string line;
//	char pch;
//
//	
//	file.close;
//}

void MainModule::runScanModule() {
	Data * a = new Data();
	a->X = 1;
	a->Y = 1;
	a->Z = 1;

	ScanModule *scanner = new ScanModule();
	RegistrationModule *c = new RegistrationModule();
	scanner->setData(data);
	scanner->setRegistrationModule(c);
	scanner->show();
}
void MainModule::runCalibrationModule() {
	CalibrationModule* c = new CalibrationModule();
	c->show();
}

void MainModule::runViewerModule() {
	//ScanModule *sc = new ScanModule();
	//sc->show();
	IOModule *c = new IOModule();
	c->show();
	
}

void MainModule::runExpModule() {

}

