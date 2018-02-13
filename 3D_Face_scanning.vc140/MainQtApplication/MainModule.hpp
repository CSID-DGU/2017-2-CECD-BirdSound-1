#include "ui_mainmodule.h"

class MainModule : public QWidget { //QWidget »ó¼Ó..
	Q_OBJECT

public:
	MainModule(QWidget* parent = Q_NULLPTR);
	void runCalibrationModule();
	void runScanModule();
	void runViewerModule();
	void runExpModule();

private:
	Ui::MainModule ui;
};