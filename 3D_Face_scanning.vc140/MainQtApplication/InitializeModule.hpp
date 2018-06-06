#pragma once
#include "ui_initializemodule.h"
#include <qtimer>

class InitializeModule : public QWidget { //QWidget »ó¼Ó..
	Q_OBJECT

public :
	InitializeModule(QWidget* parent = Q_NULLPTR);
	bool Init();
private : 

	Ui::InitializeModule ui;
};