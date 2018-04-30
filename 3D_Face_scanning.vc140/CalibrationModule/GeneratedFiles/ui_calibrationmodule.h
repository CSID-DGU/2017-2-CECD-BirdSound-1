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
    QLabel *irRightLabel;
    QLabel *serialNum;
    QPushButton *allStart;
    QPushButton *rgbStart;
    QLabel *label_2;
    QLabel *irLeftLabel;
    QPushButton *rgbCapture;
    QLabel *label_7;
    QPushButton *leftStart;
    QPushButton *allCapture;
    QLabel *deviceFirmware_2;
    QPushButton *startCalibrate;
    QPushButton *rgbStop;
    QLabel *ir1Status;
    QLabel *camName;
    QLabel *rgbStatus;
    QPushButton *allStop;
    QLabel *deviceName;
    QPushButton *leftStop;
    QLabel *rgbCount;
    QLabel *firmwareVer;
    QLabel *leftCount;
    QPushButton *leftCapture;
    QLabel *deviceFirmware;
    QLabel *rgbLabel;
    QLabel *rightCount;
    QListWidget *ir2CaptureList;
    QLabel *message;
    QLabel *label_5;
    QLabel *asdasd;
    QLabel *ir2Count;
    QLabel *label_9;

    void setupUi(QWidget *CalibrationModule)
    {
        if (CalibrationModule->objectName().isEmpty())
            CalibrationModule->setObjectName(QStringLiteral("CalibrationModule"));
        CalibrationModule->resize(1083, 743);
        irRightLabel = new QLabel(CalibrationModule);
        irRightLabel->setObjectName(QStringLiteral("irRightLabel"));
        irRightLabel->setGeometry(QRect(550, 400, 512, 288));
        irRightLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irRightLabel->setAlignment(Qt::AlignCenter);
        serialNum = new QLabel(CalibrationModule);
        serialNum->setObjectName(QStringLiteral("serialNum"));
        serialNum->setGeometry(QRect(660, 70, 141, 21));
        allStart = new QPushButton(CalibrationModule);
        allStart->setObjectName(QStringLiteral("allStart"));
        allStart->setGeometry(QRect(560, 120, 121, 31));
        rgbStart = new QPushButton(CalibrationModule);
        rgbStart->setObjectName(QStringLiteral("rgbStart"));
        rgbStart->setGeometry(QRect(270, 330, 101, 31));
        label_2 = new QLabel(CalibrationModule);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 690, 241, 31));
        label_2->setStyleSheet(QStringLiteral(""));
        irLeftLabel = new QLabel(CalibrationModule);
        irLeftLabel->setObjectName(QStringLiteral("irLeftLabel"));
        irLeftLabel->setGeometry(QRect(10, 400, 512, 288));
        irLeftLabel->setStyleSheet(QStringLiteral(" border-radius: 25px; background: white;"));
        irLeftLabel->setAlignment(Qt::AlignCenter);
        rgbCapture = new QPushButton(CalibrationModule);
        rgbCapture->setObjectName(QStringLiteral("rgbCapture"));
        rgbCapture->setGeometry(QRect(450, 330, 61, 31));
        label_7 = new QLabel(CalibrationModule);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(560, 300, 61, 21));
        leftStart = new QPushButton(CalibrationModule);
        leftStart->setObjectName(QStringLiteral("leftStart"));
        leftStart->setGeometry(QRect(270, 690, 101, 31));
        allCapture = new QPushButton(CalibrationModule);
        allCapture->setObjectName(QStringLiteral("allCapture"));
        allCapture->setGeometry(QRect(560, 160, 121, 31));
        deviceFirmware_2 = new QLabel(CalibrationModule);
        deviceFirmware_2->setObjectName(QStringLiteral("deviceFirmware_2"));
        deviceFirmware_2->setGeometry(QRect(560, 70, 91, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(deviceFirmware_2->sizePolicy().hasHeightForWidth());
        deviceFirmware_2->setSizePolicy(sizePolicy);
        deviceFirmware_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        startCalibrate = new QPushButton(CalibrationModule);
        startCalibrate->setObjectName(QStringLiteral("startCalibrate"));
        startCalibrate->setGeometry(QRect(690, 160, 121, 31));
        rgbStop = new QPushButton(CalibrationModule);
        rgbStop->setObjectName(QStringLiteral("rgbStop"));
        rgbStop->setGeometry(QRect(380, 330, 61, 31));
        ir1Status = new QLabel(CalibrationModule);
        ir1Status->setObjectName(QStringLiteral("ir1Status"));
        ir1Status->setGeometry(QRect(560, 690, 241, 31));
        ir1Status->setStyleSheet(QStringLiteral(""));
        camName = new QLabel(CalibrationModule);
        camName->setObjectName(QStringLiteral("camName"));
        camName->setGeometry(QRect(660, 50, 141, 21));
        rgbStatus = new QLabel(CalibrationModule);
        rgbStatus->setObjectName(QStringLiteral("rgbStatus"));
        rgbStatus->setGeometry(QRect(20, 330, 241, 31));
        rgbStatus->setStyleSheet(QStringLiteral(""));
        allStop = new QPushButton(CalibrationModule);
        allStop->setObjectName(QStringLiteral("allStop"));
        allStop->setGeometry(QRect(690, 120, 121, 31));
        deviceName = new QLabel(CalibrationModule);
        deviceName->setObjectName(QStringLiteral("deviceName"));
        deviceName->setGeometry(QRect(560, 50, 91, 21));
        sizePolicy.setHeightForWidth(deviceName->sizePolicy().hasHeightForWidth());
        deviceName->setSizePolicy(sizePolicy);
        deviceName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        leftStop = new QPushButton(CalibrationModule);
        leftStop->setObjectName(QStringLiteral("leftStop"));
        leftStop->setGeometry(QRect(380, 690, 61, 31));
        rgbCount = new QLabel(CalibrationModule);
        rgbCount->setObjectName(QStringLiteral("rgbCount"));
        rgbCount->setGeometry(QRect(470, 10, 51, 31));
        rgbCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        firmwareVer = new QLabel(CalibrationModule);
        firmwareVer->setObjectName(QStringLiteral("firmwareVer"));
        firmwareVer->setGeometry(QRect(660, 90, 141, 21));
        leftCount = new QLabel(CalibrationModule);
        leftCount->setObjectName(QStringLiteral("leftCount"));
        leftCount->setGeometry(QRect(470, 370, 51, 31));
        leftCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leftCapture = new QPushButton(CalibrationModule);
        leftCapture->setObjectName(QStringLiteral("leftCapture"));
        leftCapture->setGeometry(QRect(450, 690, 61, 31));
        deviceFirmware = new QLabel(CalibrationModule);
        deviceFirmware->setObjectName(QStringLiteral("deviceFirmware"));
        deviceFirmware->setGeometry(QRect(560, 90, 91, 21));
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
        rightCount->setGeometry(QRect(1010, 370, 51, 31));
        rightCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ir2CaptureList = new QListWidget(CalibrationModule);
        ir2CaptureList->setObjectName(QStringLiteral("ir2CaptureList"));
        ir2CaptureList->setGeometry(QRect(550, 40, 511, 291));
        message = new QLabel(CalibrationModule);
        message->setObjectName(QStringLiteral("message"));
        message->setGeometry(QRect(620, 300, 431, 21));
        label_5 = new QLabel(CalibrationModule);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 20, 511, 16));
        asdasd = new QLabel(CalibrationModule);
        asdasd->setObjectName(QStringLiteral("asdasd"));
        asdasd->setGeometry(QRect(10, 380, 101, 16));
        ir2Count = new QLabel(CalibrationModule);
        ir2Count->setObjectName(QStringLiteral("ir2Count"));
        ir2Count->setGeometry(QRect(550, 380, 511, 16));
        label_9 = new QLabel(CalibrationModule);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(550, 20, 511, 16));
        ir2CaptureList->raise();
        irRightLabel->raise();
        serialNum->raise();
        allStart->raise();
        rgbStart->raise();
        label_2->raise();
        irLeftLabel->raise();
        rgbCapture->raise();
        label_7->raise();
        leftStart->raise();
        allCapture->raise();
        deviceFirmware_2->raise();
        startCalibrate->raise();
        rgbStop->raise();
        ir1Status->raise();
        camName->raise();
        rgbStatus->raise();
        allStop->raise();
        deviceName->raise();
        leftStop->raise();
        rgbCount->raise();
        firmwareVer->raise();
        leftCount->raise();
        leftCapture->raise();
        deviceFirmware->raise();
        rgbLabel->raise();
        rightCount->raise();
        message->raise();
        label_5->raise();
        asdasd->raise();
        ir2Count->raise();
        label_9->raise();

        retranslateUi(CalibrationModule);

        QMetaObject::connectSlotsByName(CalibrationModule);
    } // setupUi

    void retranslateUi(QWidget *CalibrationModule)
    {
        CalibrationModule->setWindowTitle(QApplication::translate("CalibrationModule", "Form", Q_NULLPTR));
        irRightLabel->setText(QApplication::translate("CalibrationModule", "IR RIGHT", Q_NULLPTR));
        serialNum->setText(QString());
        allStart->setText(QApplication::translate("CalibrationModule", "All Start Detection", Q_NULLPTR));
        rgbStart->setText(QApplication::translate("CalibrationModule", "Start Detection", Q_NULLPTR));
        label_2->setText(QApplication::translate("CalibrationModule", "ir2Status", Q_NULLPTR));
        irLeftLabel->setText(QApplication::translate("CalibrationModule", "IR LEFT", Q_NULLPTR));
        rgbCapture->setText(QApplication::translate("CalibrationModule", "Capture", Q_NULLPTR));
        label_7->setText(QApplication::translate("CalibrationModule", "[System]", Q_NULLPTR));
        leftStart->setText(QApplication::translate("CalibrationModule", "Start Detection", Q_NULLPTR));
        allCapture->setText(QApplication::translate("CalibrationModule", "All Capture", Q_NULLPTR));
        deviceFirmware_2->setText(QApplication::translate("CalibrationModule", "\354\213\234\353\246\254\354\226\274 \353\204\230\353\262\204    : ", Q_NULLPTR));
        startCalibrate->setText(QApplication::translate("CalibrationModule", "Calibrate!!", Q_NULLPTR));
        rgbStop->setText(QApplication::translate("CalibrationModule", "Stop", Q_NULLPTR));
        ir1Status->setText(QApplication::translate("CalibrationModule", "status", Q_NULLPTR));
        camName->setText(QString());
        rgbStatus->setText(QApplication::translate("CalibrationModule", "status", Q_NULLPTR));
        allStop->setText(QApplication::translate("CalibrationModule", "All Stop", Q_NULLPTR));
        deviceName->setText(QApplication::translate("CalibrationModule", "\354\227\260\352\262\260\353\220\234 \354\236\245\354\271\230    : ", Q_NULLPTR));
        leftStop->setText(QApplication::translate("CalibrationModule", "Stop", Q_NULLPTR));
        rgbCount->setText(QApplication::translate("CalibrationModule", "0/20", Q_NULLPTR));
        firmwareVer->setText(QString());
        leftCount->setText(QApplication::translate("CalibrationModule", "0/20", Q_NULLPTR));
        leftCapture->setText(QApplication::translate("CalibrationModule", "Capture", Q_NULLPTR));
        deviceFirmware->setText(QApplication::translate("CalibrationModule", "\354\271\264\353\251\224\353\235\274 \355\216\214\354\233\250\354\226\264 : ", Q_NULLPTR));
        rgbLabel->setText(QApplication::translate("CalibrationModule", "RGB", Q_NULLPTR));
        rightCount->setText(QApplication::translate("CalibrationModule", "0/20", Q_NULLPTR));
        message->setText(QApplication::translate("CalibrationModule", "message!", Q_NULLPTR));
        label_5->setText(QApplication::translate("CalibrationModule", "RGB Camera", Q_NULLPTR));
        asdasd->setText(QApplication::translate("CalibrationModule", "IR Camera Left", Q_NULLPTR));
        ir2Count->setText(QApplication::translate("CalibrationModule", "IR Camera Right", Q_NULLPTR));
        label_9->setText(QApplication::translate("CalibrationModule", "Calibration Info", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalibrationModule: public Ui_CalibrationModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONMODULE_H
