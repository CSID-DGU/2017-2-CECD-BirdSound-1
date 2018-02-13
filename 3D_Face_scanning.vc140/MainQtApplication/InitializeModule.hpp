#pragma once
#include "ui_initializemodule.h"

class InitializeModule : public QWidget { //QWidget »ó¼Ó..
	Q_OBJECT

public :
	InitializeModule(QWidget* parent = Q_NULLPTR);
private : 
	Ui::InitializeModule ui;
};