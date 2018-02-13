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
#include <QtWidgets/QListWidget>
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
    QLabel *label;
    QLabel *rgbLabel;
    QLabel *irRightLabel;
    QLabel *irLeftLabel;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *depthLabel;
    QLabel *label_5;
    QPushButton *rgbStart;
    QPushButton *rgbStop;
    QPushButton *rgbCapture;
    QPushButton *leftStart;
    QPushButton *leftCapture;
    QPushButton *leftStop;
    QPushButton *rightStart;
    QPushButton *rightCapture;
    QPushButton *rightStop;
    QLabel *firmwareVer;
    QLabel *deviceFirmware;
    QLabel *label_6;
    QLabel *deviceName;
    QPushButton *captrueImage;
    QPushButton *startStreaming;
    QLabel *camName;
    QPushButton *stopStreaming;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *message;
    QLabel *label_7;
    QLabel *deviceFirmware_2;
    QLabel *serialNum;
    QLabel *rgbCount;
    QLabel *leftCount;
    QLabel *rightCount;
    QPushButton *startCalibration;
    QListWidget *rgbCaptureList;
    QListWidget *ir1CaptureList;
    QListWidget *ir2CaptureList;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalibrationModuleClass)
    {
        if (CalibrationModuleClass->objectName().isEmpty())
            CalibrationModuleClass->setObjectName(QStringLiteral("CalibrationModuleClass"));
        CalibrationModuleClass->resize(1313, 689);
        CalibrationModuleClass->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        centralWidget = new QWidget(CalibrationModuleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 290, 71, 16));
        label->setStyleSheet(QStringLiteral(""));
        rgbLabel = new QLabel(centralWidget);
        rgbLabel->setObjectName(QStringLiteral("rgbLabel"));
        rgbLabel->setGeometry(QRect(10, 0, 512, 288));
        rgbLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        rgbLabel->setTextFormat(Qt::AutoText);
        rgbLabel->setAlignment(Qt::AlignCenter);
        irRightLabel = new QLabel(centralWidget);
        irRightLabel->setObjectName(QStringLiteral("irRightLabel"));
        irRightLabel->setGeometry(QRect(530, 320, 512, 288));
        irRightLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irRightLabel->setAlignment(Qt::AlignCenter);
        irLeftLabel = new QLabel(centralWidget);
        irLeftLabel->setObjectName(QStringLiteral("irLeftLabel"));
        irLeftLabel->setGeometry(QRect(10, 320, 512, 288));
        irLeftLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irLeftLabel->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(540, 610, 111, 16));
        label_3->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 610, 111, 16));
        label_2->setStyleSheet(QStringLiteral(""));
        depthLabel = new QLabel(centralWidget);
        depthLabel->setObjectName(QStringLiteral("depthLabel"));
        depthLabel->setGeometry(QRect(530, 0, 512, 288));
        depthLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        depthLabel->setTextFormat(Qt::AutoText);
        depthLabel->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(540, 290, 81, 16));
        label_5->setStyleSheet(QStringLiteral(""));
        rgbStart = new QPushButton(centralWidget);
        rgbStart->setObjectName(QStringLiteral("rgbStart"));
        rgbStart->setGeometry(QRect(310, 290, 61, 21));
        rgbStop = new QPushButton(centralWidget);
        rgbStop->setObjectName(QStringLiteral("rgbStop"));
        rgbStop->setGeometry(QRect(380, 290, 61, 21));
        rgbCapture = new QPushButton(centralWidget);
        rgbCapture->setObjectName(QStringLiteral("rgbCapture"));
        rgbCapture->setGeometry(QRect(450, 290, 61, 21));
        leftStart = new QPushButton(centralWidget);
        leftStart->setObjectName(QStringLiteral("leftStart"));
        leftStart->setGeometry(QRect(310, 610, 61, 21));
        leftCapture = new QPushButton(centralWidget);
        leftCapture->setObjectName(QStringLiteral("leftCapture"));
        leftCapture->setGeometry(QRect(450, 610, 61, 21));
        leftStop = new QPushButton(centralWidget);
        leftStop->setObjectName(QStringLiteral("leftStop"));
        leftStop->setGeometry(QRect(380, 610, 61, 21));
        rightStart = new QPushButton(centralWidget);
        rightStart->setObjectName(QStringLiteral("rightStart"));
        rightStart->setGeometry(QRect(830, 610, 61, 21));
        rightCapture = new QPushButton(centralWidget);
        rightCapture->setObjectName(QStringLiteral("rightCapture"));
        rightCapture->setGeometry(QRect(970, 610, 61, 21));
        rightStop = new QPushButton(centralWidget);
        rightStop->setObjectName(QStringLiteral("rightStop"));
        rightStop->setGeometry(QRect(900, 610, 61, 21));
        firmwareVer = new QLabel(centralWidget);
        firmwareVer->setObjectName(QStringLiteral("firmwareVer"));
        firmwareVer->setGeometry(QRect(1160, 40, 141, 21));
        deviceFirmware = new QLabel(centralWidget);
        deviceFirmware->setObjectName(QStringLiteral("deviceFirmware"));
        deviceFirmware->setGeometry(QRect(1060, 40, 91, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(deviceFirmware->sizePolicy().hasHeightForWidth());
        deviceFirmware->setSizePolicy(sizePolicy);
        deviceFirmware->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(1070, 180, 81, 21));
        deviceName = new QLabel(centralWidget);
        deviceName->setObjectName(QStringLiteral("deviceName"));
        deviceName->setGeometry(QRect(1060, 0, 91, 21));
        sizePolicy.setHeightForWidth(deviceName->sizePolicy().hasHeightForWidth());
        deviceName->setSizePolicy(sizePolicy);
        deviceName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        captrueImage = new QPushButton(centralWidget);
        captrueImage->setObjectName(QStringLiteral("captrueImage"));
        captrueImage->setGeometry(QRect(1060, 100, 91, 23));
        startStreaming = new QPushButton(centralWidget);
        startStreaming->setObjectName(QStringLiteral("startStreaming"));
        startStreaming->setGeometry(QRect(1060, 70, 91, 23));
        camName = new QLabel(centralWidget);
        camName->setObjectName(QStringLiteral("camName"));
        camName->setGeometry(QRect(1160, 0, 141, 21));
        stopStreaming = new QPushButton(centralWidget);
        stopStreaming->setObjectName(QStringLiteral("stopStreaming"));
        stopStreaming->setGeometry(QRect(1160, 70, 91, 23));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1070, 480, 111, 16));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(1070, 330, 111, 16));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(1060, 170, 241, 461));
        label_9->setStyleSheet(QLatin1String("border-radius: 4px;\n"
"border: 2px solid gray;\n"
"background-image: url(:/myImage.png);\n"
""));
        message = new QLabel(centralWidget);
        message->setObjectName(QStringLiteral("message"));
        message->setGeometry(QRect(1120, 140, 161, 21));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(1060, 140, 61, 21));
        deviceFirmware_2 = new QLabel(centralWidget);
        deviceFirmware_2->setObjectName(QStringLiteral("deviceFirmware_2"));
        deviceFirmware_2->setGeometry(QRect(1060, 20, 91, 21));
        sizePolicy.setHeightForWidth(deviceFirmware_2->sizePolicy().hasHeightForWidth());
        deviceFirmware_2->setSizePolicy(sizePolicy);
        deviceFirmware_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        serialNum = new QLabel(centralWidget);
        serialNum->setObjectName(QStringLiteral("serialNum"));
        serialNum->setGeometry(QRect(1160, 20, 141, 21));
        rgbCount = new QLabel(centralWidget);
        rgbCount->setObjectName(QStringLiteral("rgbCount"));
        rgbCount->setGeometry(QRect(1210, 180, 81, 21));
        rgbCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leftCount = new QLabel(centralWidget);
        leftCount->setObjectName(QStringLiteral("leftCount"));
        leftCount->setGeometry(QRect(1210, 330, 81, 21));
        leftCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        rightCount = new QLabel(centralWidget);
        rightCount->setObjectName(QStringLiteral("rightCount"));
        rightCount->setGeometry(QRect(1210, 480, 81, 21));
        rightCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        startCalibration = new QPushButton(centralWidget);
        startCalibration->setObjectName(QStringLiteral("startCalibration"));
        startCalibration->setGeometry(QRect(1160, 100, 91, 23));
        rgbCaptureList = new QListWidget(centralWidget);
        rgbCaptureList->setObjectName(QStringLiteral("rgbCaptureList"));
        rgbCaptureList->setGeometry(QRect(1070, 200, 221, 121));
        ir1CaptureList = new QListWidget(centralWidget);
        ir1CaptureList->setObjectName(QStringLiteral("ir1CaptureList"));
        ir1CaptureList->setGeometry(QRect(1070, 350, 221, 121));
        ir2CaptureList = new QListWidget(centralWidget);
        ir2CaptureList->setObjectName(QStringLiteral("ir2CaptureList"));
        ir2CaptureList->setGeometry(QRect(1070, 500, 221, 121));
        CalibrationModuleClass->setCentralWidget(centralWidget);
        label_9->raise();
        label->raise();
        rgbLabel->raise();
        irRightLabel->raise();
        irLeftLabel->raise();
        label_3->raise();
        label_2->raise();
        depthLabel->raise();
        label_5->raise();
        rgbStart->raise();
        rgbStop->raise();
        rgbCapture->raise();
        leftStart->raise();
        leftCapture->raise();
        leftStop->raise();
        rightStart->raise();
        rightCapture->raise();
        rightStop->raise();
        firmwareVer->raise();
        deviceFirmware->raise();
        label_6->raise();
        deviceName->raise();
        captrueImage->raise();
        startStreaming->raise();
        camName->raise();
        stopStreaming->raise();
        label_4->raise();
        label_8->raise();
        message->raise();
        label_7->raise();
        deviceFirmware_2->raise();
        serialNum->raise();
        rgbCount->raise();
        leftCount->raise();
        rightCount->raise();
        startCalibration->raise();
        rgbCaptureList->raise();
        ir1CaptureList->raise();
        ir2CaptureList->raise();
        menuBar = new QMenuBar(CalibrationModuleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1313, 21));
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
        label->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221RGB CAM", Q_NULLPTR));
        rgbLabel->setText(QApplication::translate("CalibrationModuleClass", "RGB", Q_NULLPTR));
        irRightLabel->setText(QApplication::translate("CalibrationModuleClass", "IR RIGHT", Q_NULLPTR));
        irLeftLabel->setText(QApplication::translate("CalibrationModuleClass", "IR LEFT", Q_NULLPTR));
        label_3->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221IR CAM 2(RIGHT)", Q_NULLPTR));
        label_2->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221IR CAM 1(LEFT)", Q_NULLPTR));
        depthLabel->setText(QApplication::translate("CalibrationModuleClass", "DEPTH", Q_NULLPTR));
        label_5->setText(QApplication::translate("CalibrationModuleClass", "\342\206\221DEPRH MAP", Q_NULLPTR));
        rgbStart->setText(QApplication::translate("CalibrationModuleClass", "Start", Q_NULLPTR));
        rgbStop->setText(QApplication::translate("CalibrationModuleClass", "Stop", Q_NULLPTR));
        rgbCapture->setText(QApplication::translate("CalibrationModuleClass", "Capture", Q_NULLPTR));
        leftStart->setText(QApplication::translate("CalibrationModuleClass", "Start", Q_NULLPTR));
        leftCapture->setText(QApplication::translate("CalibrationModuleClass", "Capture", Q_NULLPTR));
        leftStop->setText(QApplication::translate("CalibrationModuleClass", "Stop", Q_NULLPTR));
        rightStart->setText(QApplication::translate("CalibrationModuleClass", "Start", Q_NULLPTR));
        rightCapture->setText(QApplication::translate("CalibrationModuleClass", "Capture", Q_NULLPTR));
        rightStop->setText(QApplication::translate("CalibrationModuleClass", "Stop", Q_NULLPTR));
        firmwareVer->setText(QString());
        deviceFirmware->setText(QApplication::translate("CalibrationModuleClass", "\354\271\264\353\251\224\353\235\274 \355\216\214\354\233\250\354\226\264 : ", Q_NULLPTR));
        label_6->setText(QApplication::translate("CalibrationModuleClass", "RGB CAM", Q_NULLPTR));
        deviceName->setText(QApplication::translate("CalibrationModuleClass", "\354\227\260\352\262\260\353\220\234 \354\236\245\354\271\230    : ", Q_NULLPTR));
        captrueImage->setText(QApplication::translate("CalibrationModuleClass", "All Capture", Q_NULLPTR));
        startStreaming->setText(QApplication::translate("CalibrationModuleClass", "All Start", Q_NULLPTR));
        camName->setText(QString());
        stopStreaming->setText(QApplication::translate("CalibrationModuleClass", "All Stop", Q_NULLPTR));
        label_4->setText(QApplication::translate("CalibrationModuleClass", "IR CAM 2 (RIGHT)", Q_NULLPTR));
        label_8->setText(QApplication::translate("CalibrationModuleClass", "IR CAM 1 (LEFT)", Q_NULLPTR));
        label_9->setText(QString());
        message->setText(QApplication::translate("CalibrationModuleClass", "message!", Q_NULLPTR));
        label_7->setText(QApplication::translate("CalibrationModuleClass", "[System]", Q_NULLPTR));
        deviceFirmware_2->setText(QApplication::translate("CalibrationModuleClass", "\354\213\234\353\246\254\354\226\274 \353\204\230\353\262\204    : ", Q_NULLPTR));
        serialNum->setText(QString());
        rgbCount->setText(QApplication::translate("CalibrationModuleClass", "0/20", Q_NULLPTR));
        leftCount->setText(QApplication::translate("CalibrationModuleClass", "0/20", Q_NULLPTR));
        rightCount->setText(QApplication::translate("CalibrationModuleClass", "0/20", Q_NULLPTR));
        startCalibration->setText(QApplication::translate("CalibrationModuleClass", "Calibrate!!", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrationModuleClass: public Ui_CalibrationModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONMODULE_H
