#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CalibrationModule.h"

class CalibrationModule : public QMainWindow
{
	Q_OBJECT

public:
	CalibrationModule(QWidget *parent = Q_NULLPTR);

private:
	Ui::CalibrationModuleClass ui;
};
