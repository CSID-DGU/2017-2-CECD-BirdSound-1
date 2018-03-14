#pragma once
#include "ui_registrationmodule.h"
#include "Data.cpp"
/*
단하나의 객체만 만들도록 하기

*/
class RegistrationModule : public QWidget {
	Q_OBJECT

public:
	RegistrationModule(QWidget *parent = Q_NULLPTR);
	~RegistrationModule() {
		printf("reg_exited");
	}
	void setData(Data *data) {
		this->data = data;
	}
private slots:
	void SaveButtonClicked();
	void QuitButtonClicked();
private:
	Ui::RegistrationModule ui;
public:
	Data *data;
};