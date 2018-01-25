/********************************************************************************
** Form generated from reading UI file 'CalibrationModule.ui'
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationModuleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalibrationModuleClass)
    {
        if (CalibrationModuleClass->objectName().isEmpty())
            CalibrationModuleClass->setObjectName(QStringLiteral("CalibrationModuleClass"));
        CalibrationModuleClass->resize(600, 400);
        menuBar = new QMenuBar(CalibrationModuleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CalibrationModuleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CalibrationModuleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CalibrationModuleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CalibrationModuleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CalibrationModuleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CalibrationModuleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CalibrationModuleClass->setStatusBar(statusBar);

        retranslateUi(CalibrationModuleClass);

        QMetaObject::connectSlotsByName(CalibrationModuleClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalibrationModuleClass)
    {
        CalibrationModuleClass->setWindowTitle(QApplication::translate("CalibrationModuleClass", "CalibrationModule", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrationModuleClass: public Ui_CalibrationModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONMODULE_H
