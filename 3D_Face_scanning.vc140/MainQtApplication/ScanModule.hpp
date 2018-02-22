#pragma once
#include "ui_scanmodule.h"
/*
단하나의 객체만 만들도록 하기

*/
class ScanModule : public QWidget{
	Q_OBJECT

public:
	ScanModule(QWidget *parent = Q_NULLPTR);

private slots:
	void on_NextButton_clicked();
private:
	Ui::ScanModule ui;
};