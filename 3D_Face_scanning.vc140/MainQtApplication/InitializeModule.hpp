#pragma once
#include "ui_initializemodule.h"
#include <qtimer>

class InitializeModule : public QWidget { //QWidget ���..
	Q_OBJECT

public :
	InitializeModule(QWidget* parent = Q_NULLPTR);
	bool Init();
private : 

	Ui::InitializeModule ui;
};