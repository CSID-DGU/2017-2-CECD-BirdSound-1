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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
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
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
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
        DemoFirstPart->resize(1102, 846);
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
        scrollArea_2->setGeometry(QRect(670, 450, 411, 321));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 409, 319));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        scrollArea_3 = new QScrollArea(DemoFirstPart);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setGeometry(QRect(670, 120, 411, 321));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 409, 319));
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
