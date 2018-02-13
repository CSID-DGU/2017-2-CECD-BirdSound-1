/********************************************************************************
** Form generated from reading UI file 'calibrationmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONMODULE_H
#define UI_CALIBRATIONMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationModule
{
public:

    void setupUi(QWidget *CalibrationModule)
    {
        if (CalibrationModule->objectName().isEmpty())
            CalibrationModule->setObjectName(QStringLiteral("CalibrationModule"));
        CalibrationModule->resize(400, 300);

        retranslateUi(CalibrationModule);

        QMetaObject::connectSlotsByName(CalibrationModule);
    } // setupUi

    void retranslateUi(QWidget *CalibrationModule)
    {
        CalibrationModule->setWindowTitle(QApplication::translate("CalibrationModule", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrationModule: public Ui_CalibrationModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONMODULE_H
