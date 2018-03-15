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
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationModule
{
public:
    QLabel *label_4;
    QLabel *irRightLabel;
    QLabel *serialNum;
    QPushButton *rightStart;
    QLabel *label_6;
    QPushButton *startStreaming;
    QPushButton *rgbStart;
    QLabel *label_2;
    QLabel *depthLabel;
    QListWidget *rgbCaptureList;
    QLabel *irLeftLabel;
    QPushButton *rgbCapture;
    QLabel *label_7;
    QPushButton *leftStart;
    QPushButton *captrueImage;
    QLabel *deviceFirmware_2;
    QPushButton *startCalibration;
    QPushButton *rgbStop;
    QLabel *label_8;
    QLabel *label_3;
    QLabel *camName;
    QLabel *label;
    QPushButton *stopStreaming;
    QLabel *deviceName;
    QLabel *label_5;
    QPushButton *leftStop;
    QLabel *rgbCount;
    QLabel *firmwareVer;
    QLabel *leftCount;
    QPushButton *leftCapture;
    QLabel *deviceFirmware;
    QLabel *rgbLabel;
    QLabel *rightCount;
    QLabel *label_9;
    QListWidget *ir1CaptureList;
    QPushButton *rightCapture;
    QListWidget *ir2CaptureList;
    QLabel *message;
    QPushButton *rightStop;

    void setupUi(QWidget *CalibrationModule)
    {
        if (CalibrationModule->objectName().isEmpty())
            CalibrationModule->setObjectName(QStringLiteral("CalibrationModule"));
        CalibrationModule->resize(1312, 687);
        label_4 = new QLabel(CalibrationModule);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1070, 520, 111, 16));
        irRightLabel = new QLabel(CalibrationModule);
        irRightLabel->setObjectName(QStringLiteral("irRightLabel"));
        irRightLabel->setGeometry(QRect(530, 360, 512, 288));
        irRightLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irRightLabel->setAlignment(Qt::AlignCenter);
        serialNum = new QLabel(CalibrationModule);
        serialNum->setObjectName(QStringLiteral("serialNum"));
        serialNum->setGeometry(QRect(1160, 60, 141, 21));
        rightStart = new QPushButton(CalibrationModule);
        rightStart->setObjectName(QStringLiteral("rightStart"));
        rightStart->setGeometry(QRect(830, 650, 61, 21));
        label_6 = new QLabel(CalibrationModule);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(1070, 220, 81, 21));
        startStreaming = new QPushButton(CalibrationModule);
        startStreaming->setObjectName(QStringLiteral("startStreaming"));
        startStreaming->setGeometry(QRect(1060, 110, 91, 23));
        rgbStart = new QPushButton(CalibrationModule);
        rgbStart->setObjectName(QStringLiteral("rgbStart"));
        rgbStart->setGeometry(QRect(310, 330, 61, 21));
        label_2 = new QLabel(CalibrationModule);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 650, 111, 16));
        label_2->setStyleSheet(QStringLiteral(""));
        depthLabel = new QLabel(CalibrationModule);
        depthLabel->setObjectName(QStringLiteral("depthLabel"));
        depthLabel->setGeometry(QRect(530, 40, 512, 288));
        depthLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        depthLabel->setTextFormat(Qt::AutoText);
        depthLabel->setAlignment(Qt::AlignCenter);
        rgbCaptureList = new QListWidget(CalibrationModule);
        rgbCaptureList->setObjectName(QStringLiteral("rgbCaptureList"));
        rgbCaptureList->setGeometry(QRect(1070, 240, 221, 121));
        irLeftLabel = new QLabel(CalibrationModule);
        irLeftLabel->setObjectName(QStringLiteral("irLeftLabel"));
        irLeftLabel->setGeometry(QRect(10, 360, 512, 288));
        irLeftLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irLeftLabel->setAlignment(Qt::AlignCenter);
        rgbCapture = new QPushButton(CalibrationModule);
        rgbCapture->setObjectName(QStringLiteral("rgbCapture"));
        rgbCapture->setGeometry(QRect(450, 330, 61, 21));
        label_7 = new QLabel(CalibrationModule);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(1060, 180, 61, 21));
        leftStart = new QPushButton(CalibrationModule);
        leftStart->setObjectName(QStringLiteral("leftStart"));
        leftStart->setGeometry(QRect(310, 650, 61, 21));
        captrueImage = new QPushButton(CalibrationModule);
        captrueImage->setObjectName(QStringLiteral("captrueImage"));
        captrueImage->setGeometry(QRect(1060, 140, 91, 23));
        deviceFirmware_2 = new QLabel(CalibrationModule);
        deviceFirmware_2->setObjectName(QStringLiteral("deviceFirmware_2"));
        deviceFirmware_2->setGeometry(QRect(1060, 60, 91, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(deviceFirmware_2->sizePolicy().hasHeightForWidth());
        deviceFirmware_2->setSizePolicy(sizePolicy);
        deviceFirmware_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        startCalibration = new QPushButton(CalibrationModule);
        startCalibration->setObjectName(QStringLiteral("startCalibration"));
        startCalibration->setGeometry(QRect(1160, 140, 91, 23));
        rgbStop = new QPushButton(CalibrationModule);
        rgbStop->setObjectName(QStringLiteral("rgbStop"));
        rgbStop->setGeometry(QRect(380, 330, 61, 21));
        label_8 = new QLabel(CalibrationModule);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(1070, 370, 111, 16));
        label_3 = new QLabel(CalibrationModule);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(540, 650, 111, 16));
        label_3->setStyleSheet(QStringLiteral(""));
        camName = new QLabel(CalibrationModule);
        camName->setObjectName(QStringLiteral("camName"));
        camName->setGeometry(QRect(1160, 40, 141, 21));
        label = new QLabel(CalibrationModule);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 330, 71, 16));
        label->setStyleSheet(QStringLiteral(""));
        stopStreaming = new QPushButton(CalibrationModule);
        stopStreaming->setObjectName(QStringLiteral("stopStreaming"));
        stopStreaming->setGeometry(QRect(1160, 110, 91, 23));
        deviceName = new QLabel(CalibrationModule);
        deviceName->setObjectName(QStringLiteral("deviceName"));
        deviceName->setGeometry(QRect(1060, 40, 91, 21));
        sizePolicy.setHeightForWidth(deviceName->sizePolicy().hasHeightForWidth());
        deviceName->setSizePolicy(sizePolicy);
        deviceName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(CalibrationModule);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(540, 330, 81, 16));
        label_5->setStyleSheet(QStringLiteral(""));
        leftStop = new QPushButton(CalibrationModule);
        leftStop->setObjectName(QStringLiteral("leftStop"));
        leftStop->setGeometry(QRect(380, 650, 61, 21));
        rgbCount = new QLabel(CalibrationModule);
        rgbCount->setObjectName(QStringLiteral("rgbCount"));
        rgbCount->setGeometry(QRect(1210, 220, 81, 21));
        rgbCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        firmwareVer = new QLabel(CalibrationModule);
        firmwareVer->setObjectName(QStringLiteral("firmwareVer"));
        firmwareVer->setGeometry(QRect(1160, 80, 141, 21));
        leftCount = new QLabel(CalibrationModule);
        leftCount->setObjectName(QStringLiteral("leftCount"));
        leftCount->setGeometry(QRect(1210, 370, 81, 21));
        leftCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leftCapture = new QPushButton(CalibrationModule);
        leftCapture->setObjectName(QStringLiteral("leftCapture"));
        leftCapture->setGeometry(QRect(450, 650, 61, 21));
        deviceFirmware = new QLabel(CalibrationModule);
        deviceFirmware->setObjectName(QStringLiteral("deviceFirmware"));
        deviceFirmware->setGeometry(QRect(1060, 80, 91, 21));
        sizePolicy.setHeightForWidth(deviceFirmware->sizePolicy().hasHeightForWidth());
        deviceFirmware->setSizePolicy(sizePolicy);
        deviceFirmware->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        rgbLabel = new QLabel(CalibrationModule);
        rgbLabel->setObjectName(QStringLiteral("rgbLabel"));
        rgbLabel->setGeometry(QRect(10, 40, 512, 288));
        rgbLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        rgbLabel->setTextFormat(Qt::AutoText);
        rgbLabel->setAlignment(Qt::AlignCenter);
        rightCount = new QLabel(CalibrationModule);
        rightCount->setObjectName(QStringLiteral("rightCount"));
        rightCount->setGeometry(QRect(1210, 520, 81, 21));
        rightCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_9 = new QLabel(CalibrationModule);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(1060, 210, 241, 461));
        label_9->setStyleSheet(QLatin1String("border-radius: 4px;\n"
"border: 2px solid gray;\n"
"background-image: url(:/myImage.png);\n"
""));
        ir1CaptureList = new QListWidget(CalibrationModule);
        ir1CaptureList->setObjectName(QStringLiteral("ir1CaptureList"));
        ir1CaptureList->setGeometry(QRect(1070, 390, 221, 121));
        rightCapture = new QPushButton(CalibrationModule);
        rightCapture->setObjectName(QStringLiteral("rightCapture"));
        rightCapture->setGeometry(QRect(970, 650, 61, 21));
        ir2CaptureList = new QListWidget(CalibrationModule);
        ir2CaptureList->setObjectName(QStringLiteral("ir2CaptureList"));
        ir2CaptureList->setGeometry(QRect(1070, 540, 221, 121));
        message = new QLabel(CalibrationModule);
        message->setObjectName(QStringLiteral("message"));
        message->setGeometry(QRect(1120, 180, 161, 21));
        rightStop = new QPushButton(CalibrationModule);
        rightStop->setObjectName(QStringLiteral("rightStop"));
        rightStop->setGeometry(QRect(900, 650, 61, 21));

        retranslateUi(CalibrationModule);

        QMetaObject::connectSlotsByName(CalibrationModule);
    } // setupUi

    void retranslateUi(QWidget *CalibrationModule)
    {
        CalibrationModule->setWindowTitle(QApplication::translate("CalibrationModule", "Form", Q_NULLPTR));
        label_4->setText(QApplication::translate("CalibrationModule", "IR CAM 2 (RIGHT)", Q_NULLPTR));
        irRightLabel->setText(QApplication::translate("CalibrationModule", "IR RIGHT", Q_NULLPTR));
        serialNum->setText(QString());
        rightStart->setText(QApplication::translate("CalibrationModule", "Start", Q_NULLPTR));
        label_6->setText(QApplication::translate("CalibrationModule", "RGB CAM", Q_NULLPTR));
        startStreaming->setText(QApplication::translate("CalibrationModule", "All Start", Q_NULLPTR));
        rgbStart->setText(QApplication::translate("CalibrationModule", "Start", Q_NULLPTR));
        label_2->setText(QApplication::translate("CalibrationModule", "\342\206\221IR CAM 1(LEFT)", Q_NULLPTR));
        depthLabel->setText(QApplication::translate("CalibrationModule", "DEPTH", Q_NULLPTR));
        irLeftLabel->setText(QApplication::translate("CalibrationModule", "IR LEFT", Q_NULLPTR));
        rgbCapture->setText(QApplication::translate("CalibrationModule", "Capture", Q_NULLPTR));
        label_7->setText(QApplication::translate("CalibrationModule", "[System]", Q_NULLPTR));
        leftStart->setText(QApplication::translate("CalibrationModule", "Start", Q_NULLPTR));
        captrueImage->setText(QApplication::translate("CalibrationModule", "All Capture", Q_NULLPTR));
        deviceFirmware_2->setText(QApplication::translate("CalibrationModule", "\354\213\234\353\246\254\354\226\274 \353\204\230\353\262\204    : ", Q_NULLPTR));
        startCalibration->setText(QApplication::translate("CalibrationModule", "Calibrate!!", Q_NULLPTR));
        rgbStop->setText(QApplication::translate("CalibrationModule", "Stop", Q_NULLPTR));
        label_8->setText(QApplication::translate("CalibrationModule", "IR CAM 1 (LEFT)", Q_NULLPTR));
        label_3->setText(QApplication::translate("CalibrationModule", "\342\206\221IR CAM 2(RIGHT)", Q_NULLPTR));
        camName->setText(QString());
        label->setText(QApplication::translate("CalibrationModule", "\342\206\221RGB CAM", Q_NULLPTR));
        stopStreaming->setText(QApplication::translate("CalibrationModule", "All Stop", Q_NULLPTR));
        deviceName->setText(QApplication::translate("CalibrationModule", "\354\227\260\352\262\260\353\220\234 \354\236\245\354\271\230    : ", Q_NULLPTR));
        label_5->setText(QApplication::translate("CalibrationModule", "\342\206\221DEPRH MAP", Q_NULLPTR));
        leftStop->setText(QApplication::translate("CalibrationModule", "Stop", Q_NULLPTR));
        rgbCount->setText(QApplication::translate("CalibrationModule", "0/20", Q_NULLPTR));
        firmwareVer->setText(QString());
        leftCount->setText(QApplication::translate("CalibrationModule", "0/20", Q_NULLPTR));
        leftCapture->setText(QApplication::translate("CalibrationModule", "Capture", Q_NULLPTR));
        deviceFirmware->setText(QApplication::translate("CalibrationModule", "\354\271\264\353\251\224\353\235\274 \355\216\214\354\233\250\354\226\264 : ", Q_NULLPTR));
        rgbLabel->setText(QApplication::translate("CalibrationModule", "RGB", Q_NULLPTR));
        rightCount->setText(QApplication::translate("CalibrationModule", "0/20", Q_NULLPTR));
        label_9->setText(QString());
        rightCapture->setText(QApplication::translate("CalibrationModule", "Capture", Q_NULLPTR));
        message->setText(QApplication::translate("CalibrationModule", "message!", Q_NULLPTR));
        rightStop->setText(QApplication::translate("CalibrationModule", "Stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrationModule: public Ui_CalibrationModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONMODULE_H
