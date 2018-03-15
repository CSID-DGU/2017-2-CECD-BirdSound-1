#pragma once
#include "ui_scanmodule.h"
#include "Data.cpp"
#include "RegistrationModule.hpp"
#include <qtimer>
/*
- 단하나의 객체만 만들도록 하기(더블 클릭 방지)
- Scan 기능 모듈 구현은 Scan될때 생성자와 다음 모듈로 넘어가는 onNext에 구현

*/
class ScanModule : public QWidget{
	Q_OBJECT

public:
	ScanModule(QWidget *parent = Q_NULLPTR);
	void setData(Data *data) {
		this->data = data;
	}
	void setRegistrationModule(RegistrationModule *reg) {
		this->reg = reg;
	}
private slots:
	void on_NextButton_clicked();
	void on_ScanButton_clicked();
private:
	Ui::ScanModule ui;
public:
	Data *data;
	RegistrationModule *reg;
};