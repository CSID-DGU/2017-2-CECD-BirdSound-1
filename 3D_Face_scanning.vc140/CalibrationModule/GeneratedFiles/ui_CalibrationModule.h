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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationModuleClass
{
public:
    QWidget *centralWidget;
    QLabel *deviceName;
    QLabel *deviceFirmware;
    QPushButton *startStreaming;
    QPushButton *captrueImage;
    QPushButton *stopStreaming;
    QLabel *label;
    QLabel *rgbLabel;
    QLabel *irRightLabel;
    QLabel *irLeftLabel;
    QLabel *label_3;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalibrationModuleClass)
    {
        if (CalibrationModuleClass->objectName().isEmpty())
            CalibrationModuleClass->setObjectName(QStringLiteral("CalibrationModuleClass"));
        CalibrationModuleClass->resize(1308, 756);
        CalibrationModuleClass->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        centralWidget = new QWidget(CalibrationModuleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        deviceName = new QLabel(centralWidget);
        deviceName->setObjectName(QStringLiteral("deviceName"));
        deviceName->setGeometry(QRect(10, 10, 81, 21));
        deviceFirmware = new QLabel(centralWidget);
        deviceFirmware->setObjectName(QStringLiteral("deviceFirmware"));
        deviceFirmware->setGeometry(QRect(10, 30, 81, 21));
        startStreaming = new QPushButton(centralWidget);
        startStreaming->setObjectName(QStringLiteral("startStreaming"));
        startStreaming->setGeometry(QRect(10, 60, 75, 23));
        captrueImage = new QPushButton(centralWidget);
        captrueImage->setObjectName(QStringLiteral("captrueImage"));
        captrueImage->setGeometry(QRect(10, 90, 75, 23));
        stopStreaming = new QPushButton(centralWidget);
        stopStreaming->setObjectName(QStringLiteral("stopStreaming"));
        stopStreaming->setGeometry(QRect(10, 120, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 300, 71, 16));
        label->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        rgbLabel = new QLabel(centralWidget);
        rgbLabel->setObjectName(QStringLiteral("rgbLabel"));
        rgbLabel->setGeometry(QRect(220, 10, 512, 288));
        rgbLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irRightLabel = new QLabel(centralWidget);
        irRightLabel->setObjectName(QStringLiteral("irRightLabel"));
        irRightLabel->setGeometry(QRect(740, 320, 512, 288));
        irRightLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irLeftLabel = new QLabel(centralWidget);
        irLeftLabel->setObjectName(QStringLiteral("irLeftLabel"));
        irLeftLabel->setGeometry(QRect(220, 320, 512, 288));
        irLeftLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(750, 610, 111, 16));
        label_3->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 610, 111, 16));
        label_2->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        CalibrationModuleClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CalibrationModuleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1308, 21));
        CalibrationModuleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CalibrationModuleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CalibrationModuleClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CalibrationModuleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CalibrationModuleClass->setStatusBar(statusBar);

        retranslateUi(CalibrationModuleClass);

        QMetaObject::connectSlotsByName(CalibrationModuleClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalibrationModuleClass)
    {
        CalibrationModuleClass->setWindowTitle(QApplication::translate("CalibrationModuleClass", "CalibrationModule", Q_NULLPTR));
        deviceName->setText(QApplication::translate("CalibrationModuleClass", "\354\227\260\352\262\260\353\220\234 \354\236\245\354\271\230", Q_NULLPTR));
        deviceFirmware->setText(QApplication::translate("CalibrationModuleClass", "\354\271\264\353\251\224\353\235\274 \355\216\214\354\233\250\354\226\264", Q_NULLPTR));
        startStreaming->setText(QApplication::translate("CalibrationModuleClass", "Start", Q_NULLPTR));
        captrueImage->setText(QApplication::translate("CalibrationModuleClass", "Capture", Q_NULLPTR));
        stopStreaming->setText(QApplication::translate("CalibrationModuleClass", "Stop", Q_NULLPTR));
        label->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221RGB CAM", Q_NULLPTR));
        rgbLabel->setText(QApplication::translate("CalibrationModuleClass", "RGB Image", Q_NULLPTR));
        irRightLabel->setText(QApplication::translate("CalibrationModuleClass", "IR2", Q_NULLPTR));
        irLeftLabel->setText(QApplication::translate("CalibrationModuleClass", "IR1", Q_NULLPTR));
        label_3->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221IR CAM 2(RIGHT)", Q_NULLPTR));
        label_2->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221IR CAM 1(LEFT)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrationModuleClass: public Ui_CalibrationModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONMODULE_H
