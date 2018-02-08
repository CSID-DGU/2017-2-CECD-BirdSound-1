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
    QLabel *label_4;
    QLabel *depthLabel;
    QLabel *label_5;
    QLabel *camName;
    QLabel *firmwareVer;
    QLabel *label_6;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalibrationModuleClass)
    {
        if (CalibrationModuleClass->objectName().isEmpty())
            CalibrationModuleClass->setObjectName(QStringLiteral("CalibrationModuleClass"));
        CalibrationModuleClass->resize(1291, 712);
        CalibrationModuleClass->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        centralWidget = new QWidget(CalibrationModuleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        deviceName = new QLabel(centralWidget);
        deviceName->setObjectName(QStringLiteral("deviceName"));
        deviceName->setGeometry(QRect(10, 10, 91, 21));
        deviceName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        deviceFirmware = new QLabel(centralWidget);
        deviceFirmware->setObjectName(QStringLiteral("deviceFirmware"));
        deviceFirmware->setGeometry(QRect(10, 30, 91, 21));
        deviceFirmware->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        startStreaming = new QPushButton(centralWidget);
        startStreaming->setObjectName(QStringLiteral("startStreaming"));
        startStreaming->setGeometry(QRect(10, 80, 91, 23));
        captrueImage = new QPushButton(centralWidget);
        captrueImage->setObjectName(QStringLiteral("captrueImage"));
        captrueImage->setGeometry(QRect(10, 110, 91, 23));
        stopStreaming = new QPushButton(centralWidget);
        stopStreaming->setObjectName(QStringLiteral("stopStreaming"));
        stopStreaming->setGeometry(QRect(10, 140, 91, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(260, 300, 71, 16));
        label->setStyleSheet(QStringLiteral(""));
        rgbLabel = new QLabel(centralWidget);
        rgbLabel->setObjectName(QStringLiteral("rgbLabel"));
        rgbLabel->setGeometry(QRect(250, 10, 512, 288));
        rgbLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        rgbLabel->setTextFormat(Qt::AutoText);
        rgbLabel->setAlignment(Qt::AlignCenter);
        irRightLabel = new QLabel(centralWidget);
        irRightLabel->setObjectName(QStringLiteral("irRightLabel"));
        irRightLabel->setGeometry(QRect(770, 320, 512, 288));
        irRightLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irRightLabel->setAlignment(Qt::AlignCenter);
        irLeftLabel = new QLabel(centralWidget);
        irLeftLabel->setObjectName(QStringLiteral("irLeftLabel"));
        irLeftLabel->setGeometry(QRect(250, 320, 512, 288));
        irLeftLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irLeftLabel->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(780, 610, 111, 16));
        label_3->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 610, 111, 16));
        label_2->setStyleSheet(QStringLiteral(""));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 180, 221, 431));
        label_4->setStyleSheet(QLatin1String("background: white; border-color: coral;\n"
"    border-width: 7px;"));
        depthLabel = new QLabel(centralWidget);
        depthLabel->setObjectName(QStringLiteral("depthLabel"));
        depthLabel->setGeometry(QRect(770, 10, 512, 288));
        depthLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        depthLabel->setTextFormat(Qt::AutoText);
        depthLabel->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(780, 300, 81, 16));
        label_5->setStyleSheet(QStringLiteral(""));
        camName = new QLabel(centralWidget);
        camName->setObjectName(QStringLiteral("camName"));
        camName->setGeometry(QRect(100, 10, 141, 21));
        firmwareVer = new QLabel(centralWidget);
        firmwareVer->setObjectName(QStringLiteral("firmwareVer"));
        firmwareVer->setGeometry(QRect(100, 30, 141, 21));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 615, 81, 21));
        CalibrationModuleClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CalibrationModuleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1291, 21));
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
        deviceName->setText(QApplication::translate("CalibrationModuleClass", "\354\227\260\352\262\260\353\220\234 \354\236\245\354\271\230 : ", Q_NULLPTR));
        deviceFirmware->setText(QApplication::translate("CalibrationModuleClass", "\354\271\264\353\251\224\353\235\274 \355\216\214\354\233\250\354\226\264 : ", Q_NULLPTR));
        startStreaming->setText(QApplication::translate("CalibrationModuleClass", "Start", Q_NULLPTR));
        captrueImage->setText(QApplication::translate("CalibrationModuleClass", "Capture", Q_NULLPTR));
        stopStreaming->setText(QApplication::translate("CalibrationModuleClass", "Stop", Q_NULLPTR));
        label->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221RGB CAM", Q_NULLPTR));
        rgbLabel->setText(QApplication::translate("CalibrationModuleClass", "RGB", Q_NULLPTR));
        irRightLabel->setText(QApplication::translate("CalibrationModuleClass", "IR RIGHT", Q_NULLPTR));
        irLeftLabel->setText(QApplication::translate("CalibrationModuleClass", "IR LEFT", Q_NULLPTR));
        label_3->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221IR CAM 2(RIGHT)", Q_NULLPTR));
        label_2->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221IR CAM 1(LEFT)", Q_NULLPTR));
        label_4->setText(QString());
        depthLabel->setText(QApplication::translate("CalibrationModuleClass", "DEPTH", Q_NULLPTR));
        label_5->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221DEPRH MAP", Q_NULLPTR));
        camName->setText(QString());
        firmwareVer->setText(QString());
        label_6->setText(QApplication::translate("CalibrationModuleClass", "Saved file", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrationModuleClass: public Ui_CalibrationModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONMODULE_H
