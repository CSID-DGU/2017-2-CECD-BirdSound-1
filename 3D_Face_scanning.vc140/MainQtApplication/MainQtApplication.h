#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainQtApplication.h"

class MainQtApplication : public QMainWindow
{
	Q_OBJECT

public:
	MainQtApplication(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainQtApplicationClass ui;
};
