#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_CalibrationModule.h"



class CalibrationModule : public QMainWindow
{
	Q_OBJECT
	enum class streamType {infrared_left, infrared_right, color };
public:
	CalibrationModule(QWidget *parent = Q_NULLPTR);
	void startStreaming(streamType);
	void captureFrame();
private:
	Ui::CalibrationModuleClass ui;
};
