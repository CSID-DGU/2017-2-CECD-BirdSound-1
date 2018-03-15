#pragma once

#include <QtWidgets/QWidget>
#include "ui_valuetestmodule.h"

class ValueTestModule : public QWidget
{
	Q_OBJECT

public:
	ValueTestModule(QWidget *parent = Q_NULLPTR);

private:
	Ui::ValueTestModuleClass ui;
};
