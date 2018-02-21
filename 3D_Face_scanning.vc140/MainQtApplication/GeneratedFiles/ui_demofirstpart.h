/********************************************************************************
** Form generated from reading UI file 'demofirstpart.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMOFIRSTPART_H
#define UI_DEMOFIRSTPART_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DemoFirstPart
{
public:
    QLabel *rgbLabel;
    QLabel *label_2;
    QLabel *depthLabel;
    QLabel *label_4;
    QPushButton *capture;
    QPushButton *startStreaming;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_2;
    QSlider *DepthUnit;
    QSlider *Exposure_;
    QSlider *Gain_2;
    QSlider *LaserPower;
    QCheckBox *AutoExposure_2;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_12;
    QLabel *label_15;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QGridLayout *gridLayout;
    QCheckBox *AutoExposure;
    QCheckBox *AutoWhiteBalance;
    QSlider *Exposure;
    QLabel *label_5;
    QSlider *Gain;
    QLabel *label_7;
    QSlider *Gamma;
    QSlider *Hue;
    QLabel *label_10;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_9;
    QSlider *Saturation;
    QLabel *label;
    QSlider *Sharpness;
    QSlider *Brightness;
    QLabel *label_3;
    QSlider *Contrast;
    QSlider *WhiteBalance;
    QLabel *label_11;
    QLabel *camName;
    QLabel *deviceFirmware;
    QLabel *deviceFirmware_2;
    QLabel *deviceName;
    QLabel *serialNum;
    QLabel *firmwareVer;

    void setupUi(QWidget *DemoFirstPart)
    {
        if (DemoFirstPart->objectName().isEmpty())
            DemoFirstPart->setObjectName(QStringLiteral("DemoFirstPart"));
        DemoFirstPart->resize(1102, 843);
        rgbLabel = new QLabel(DemoFirstPart);
        rgbLabel->setObjectName(QStringLiteral("rgbLabel"));
        rgbLabel->setGeometry(QRect(10, 50, 640, 360));
        rgbLabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        label_2 = new QLabel(DemoFirstPart);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 121, 21));
        label_2->setTextFormat(Qt::PlainText);
        depthLabel = new QLabel(DemoFirstPart);
        depthLabel->setObjectName(QStringLiteral("depthLabel"));
        depthLabel->setGeometry(QRect(10, 470, 640, 360));
        depthLabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        label_4 = new QLabel(DemoFirstPart);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 440, 121, 21));
        label_4->setTextFormat(Qt::PlainText);
        capture = new QPushButton(DemoFirstPart);
        capture->setObjectName(QStringLiteral("capture"));
        capture->setGeometry(QRect(960, 780, 121, 51));
        startStreaming = new QPushButton(DemoFirstPart);
        startStreaming->setObjectName(QStringLiteral("startStreaming"));
        startStreaming->setGeometry(QRect(830, 780, 121, 51));
        scrollArea_2 = new QScrollArea(DemoFirstPart);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(670, 470, 411, 301));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 409, 299));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        DepthUnit = new QSlider(scrollAreaWidgetContents_2);
        DepthUnit->setObjectName(QStringLiteral("DepthUnit"));
        DepthUnit->setMinimum(10);
        DepthUnit->setMaximum(1000);
        DepthUnit->setSingleStep(10);
        DepthUnit->setValue(100);
        DepthUnit->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(DepthUnit, 8, 0, 1, 1);

        Exposure_ = new QSlider(scrollAreaWidgetContents_2);
        Exposure_->setObjectName(QStringLiteral("Exposure_"));
        Exposure_->setMinimum(20);
        Exposure_->setMaximum(166000);
        Exposure_->setSingleStep(10);
        Exposure_->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Exposure_, 2, 0, 1, 1);

        Gain_2 = new QSlider(scrollAreaWidgetContents_2);
        Gain_2->setObjectName(QStringLiteral("Gain_2"));
        Gain_2->setMinimum(16);
        Gain_2->setMaximum(248);
        Gain_2->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Gain_2, 4, 0, 1, 1);

        LaserPower = new QSlider(scrollAreaWidgetContents_2);
        LaserPower->setObjectName(QStringLiteral("LaserPower"));
        LaserPower->setMaximum(360);
        LaserPower->setSingleStep(10);
        LaserPower->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(LaserPower, 6, 0, 1, 1);

        AutoExposure_2 = new QCheckBox(scrollAreaWidgetContents_2);
        AutoExposure_2->setObjectName(QStringLiteral("AutoExposure_2"));

        gridLayout_2->addWidget(AutoExposure_2, 0, 0, 1, 1);

        label_13 = new QLabel(scrollAreaWidgetContents_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 3, 0, 1, 1);

        label_14 = new QLabel(scrollAreaWidgetContents_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 5, 0, 1, 1);

        label_12 = new QLabel(scrollAreaWidgetContents_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 1, 0, 1, 1);

        label_15 = new QLabel(scrollAreaWidgetContents_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_2->addWidget(label_15, 7, 0, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        scrollArea_3 = new QScrollArea(DemoFirstPart);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setGeometry(QRect(670, 120, 411, 291));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 392, 470));
        gridLayout = new QGridLayout(scrollAreaWidgetContents_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        AutoExposure = new QCheckBox(scrollAreaWidgetContents_3);
        AutoExposure->setObjectName(QStringLiteral("AutoExposure"));

        gridLayout->addWidget(AutoExposure, 4, 0, 1, 1);

        AutoWhiteBalance = new QCheckBox(scrollAreaWidgetContents_3);
        AutoWhiteBalance->setObjectName(QStringLiteral("AutoWhiteBalance"));

        gridLayout->addWidget(AutoWhiteBalance, 17, 0, 1, 1);

        Exposure = new QSlider(scrollAreaWidgetContents_3);
        Exposure->setObjectName(QStringLiteral("Exposure"));
        Exposure->setMinimum(-8);
        Exposure->setMaximum(0);
        Exposure->setValue(-2);
        Exposure->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Exposure, 6, 0, 1, 1);

        label_5 = new QLabel(scrollAreaWidgetContents_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        Gain = new QSlider(scrollAreaWidgetContents_3);
        Gain->setObjectName(QStringLiteral("Gain"));
        Gain->setMaximum(128);
        Gain->setValue(35);
        Gain->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Gain, 8, 0, 1, 1);

        label_7 = new QLabel(scrollAreaWidgetContents_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 9, 0, 1, 1);

        Gamma = new QSlider(scrollAreaWidgetContents_3);
        Gamma->setObjectName(QStringLiteral("Gamma"));
        Gamma->setMinimum(100);
        Gamma->setMaximum(500);
        Gamma->setValue(234);
        Gamma->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Gamma, 10, 0, 1, 1);

        Hue = new QSlider(scrollAreaWidgetContents_3);
        Hue->setObjectName(QStringLiteral("Hue"));
        Hue->setMinimum(-180);
        Hue->setMaximum(180);
        Hue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Hue, 12, 0, 1, 1);

        label_10 = new QLabel(scrollAreaWidgetContents_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 15, 0, 1, 1);

        label_8 = new QLabel(scrollAreaWidgetContents_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 11, 0, 1, 1);

        label_6 = new QLabel(scrollAreaWidgetContents_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        label_9 = new QLabel(scrollAreaWidgetContents_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 13, 0, 1, 1);

        Saturation = new QSlider(scrollAreaWidgetContents_3);
        Saturation->setObjectName(QStringLiteral("Saturation"));
        Saturation->setMaximum(100);
        Saturation->setValue(22);
        Saturation->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Saturation, 14, 0, 1, 1);

        label = new QLabel(scrollAreaWidgetContents_3);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Sharpness = new QSlider(scrollAreaWidgetContents_3);
        Sharpness->setObjectName(QStringLiteral("Sharpness"));
        Sharpness->setMaximum(100);
        Sharpness->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Sharpness, 16, 0, 1, 1);

        Brightness = new QSlider(scrollAreaWidgetContents_3);
        Brightness->setObjectName(QStringLiteral("Brightness"));
        Brightness->setMinimum(-64);
        Brightness->setMaximum(64);
        Brightness->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Brightness, 1, 0, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        Contrast = new QSlider(scrollAreaWidgetContents_3);
        Contrast->setObjectName(QStringLiteral("Contrast"));
        Contrast->setMaximum(100);
        Contrast->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Contrast, 3, 0, 1, 1);

        WhiteBalance = new QSlider(scrollAreaWidgetContents_3);
        WhiteBalance->setObjectName(QStringLiteral("WhiteBalance"));
        WhiteBalance->setMinimum(2800);
        WhiteBalance->setMaximum(6500);
        WhiteBalance->setSingleStep(10);
        WhiteBalance->setPageStep(100);
        WhiteBalance->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(WhiteBalance, 19, 0, 1, 1);

        label_11 = new QLabel(scrollAreaWidgetContents_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 18, 0, 1, 1);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);
        camName = new QLabel(DemoFirstPart);
        camName->setObjectName(QStringLiteral("camName"));
        camName->setGeometry(QRect(770, 50, 211, 21));
        deviceFirmware = new QLabel(DemoFirstPart);
        deviceFirmware->setObjectName(QStringLiteral("deviceFirmware"));
        deviceFirmware->setGeometry(QRect(670, 90, 91, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(deviceFirmware->sizePolicy().hasHeightForWidth());
        deviceFirmware->setSizePolicy(sizePolicy);
        deviceFirmware->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        deviceFirmware_2 = new QLabel(DemoFirstPart);
        deviceFirmware_2->setObjectName(QStringLiteral("deviceFirmware_2"));
        deviceFirmware_2->setGeometry(QRect(670, 70, 91, 21));
        sizePolicy.setHeightForWidth(deviceFirmware_2->sizePolicy().hasHeightForWidth());
        deviceFirmware_2->setSizePolicy(sizePolicy);
        deviceFirmware_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        deviceName = new QLabel(DemoFirstPart);
        deviceName->setObjectName(QStringLiteral("deviceName"));
        deviceName->setGeometry(QRect(670, 50, 91, 21));
        sizePolicy.setHeightForWidth(deviceName->sizePolicy().hasHeightForWidth());
        deviceName->setSizePolicy(sizePolicy);
        deviceName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        serialNum = new QLabel(DemoFirstPart);
        serialNum->setObjectName(QStringLiteral("serialNum"));
        serialNum->setGeometry(QRect(770, 70, 211, 21));
        firmwareVer = new QLabel(DemoFirstPart);
        firmwareVer->setObjectName(QStringLiteral("firmwareVer"));
        firmwareVer->setGeometry(QRect(770, 90, 211, 21));
        rgbLabel->raise();
        label_2->raise();
        depthLabel->raise();
        label_4->raise();
        capture->raise();
        startStreaming->raise();
        scrollArea_3->raise();
        camName->raise();
        deviceFirmware->raise();
        deviceFirmware_2->raise();
        deviceName->raise();
        serialNum->raise();
        firmwareVer->raise();
        scrollArea_2->raise();

        retranslateUi(DemoFirstPart);

        QMetaObject::connectSlotsByName(DemoFirstPart);
    } // setupUi

    void retranslateUi(QWidget *DemoFirstPart)
    {
        DemoFirstPart->setWindowTitle(QApplication::translate("DemoFirstPart", "Form", Q_NULLPTR));
        rgbLabel->setText(QString());
        label_2->setText(QApplication::translate("DemoFirstPart", "Color Image", Q_NULLPTR));
        depthLabel->setText(QString());
        label_4->setText(QApplication::translate("DemoFirstPart", "Depth Image", Q_NULLPTR));
        capture->setText(QApplication::translate("DemoFirstPart", "CAPTURE", Q_NULLPTR));
        startStreaming->setText(QApplication::translate("DemoFirstPart", "START", Q_NULLPTR));
        AutoExposure_2->setText(QApplication::translate("DemoFirstPart", "Auto Exposure", Q_NULLPTR));
        label_13->setText(QApplication::translate("DemoFirstPart", "Gain : 16.000 ~ 248.000  ", Q_NULLPTR));
        label_14->setText(QApplication::translate("DemoFirstPart", "Laser Power : 0.000 ~ 360.000  ", Q_NULLPTR));
        label_12->setText(QApplication::translate("DemoFirstPart", "Exposure 20.000 ~ 166000.000  ", Q_NULLPTR));
        label_15->setText(QApplication::translate("DemoFirstPart", "Depth Unit : 0.0001 ~ 0.01", Q_NULLPTR));
        AutoExposure->setText(QApplication::translate("DemoFirstPart", "Auto Exposure", Q_NULLPTR));
        AutoWhiteBalance->setText(QApplication::translate("DemoFirstPart", "Enable Auto White Balance", Q_NULLPTR));
        label_5->setText(QApplication::translate("DemoFirstPart", "Exposure : -8.000 ~ 0.000 ", Q_NULLPTR));
        label_7->setText(QApplication::translate("DemoFirstPart", "Gamma : 100.000 ~ 500.000  ", Q_NULLPTR));
        label_10->setText(QApplication::translate("DemoFirstPart", "Sharpness : 0.000 ~ 100.000  ", Q_NULLPTR));
        label_8->setText(QApplication::translate("DemoFirstPart", "Hue : -180.000 ~ 180.000  ", Q_NULLPTR));
        label_6->setText(QApplication::translate("DemoFirstPart", "Gain : 0.000 ~ 128.000  ", Q_NULLPTR));
        label_9->setText(QApplication::translate("DemoFirstPart", "Saturation : 0.000 ~ 100.000   ", Q_NULLPTR));
        label->setText(QApplication::translate("DemoFirstPart", "Brightness : -64.000 ~ 64.000", Q_NULLPTR));
        label_3->setText(QApplication::translate("DemoFirstPart", "Contrast : 0.000 ~ 100.000 ", Q_NULLPTR));
        label_11->setText(QApplication::translate("DemoFirstPart", "White Balance : 2800.000 ~ 6500.000 ", Q_NULLPTR));
        camName->setText(QString());
        deviceFirmware->setText(QApplication::translate("DemoFirstPart", "\354\271\264\353\251\224\353\235\274 \355\216\214\354\233\250\354\226\264 : ", Q_NULLPTR));
        deviceFirmware_2->setText(QApplication::translate("DemoFirstPart", "\354\213\234\353\246\254\354\226\274 \353\204\230\353\262\204    : ", Q_NULLPTR));
        deviceName->setText(QApplication::translate("DemoFirstPart", "\354\227\260\352\262\260\353\220\234 \354\236\245\354\271\230    : ", Q_NULLPTR));
        serialNum->setText(QString());
        firmwareVer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DemoFirstPart: public Ui_DemoFirstPart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMOFIRSTPART_H
