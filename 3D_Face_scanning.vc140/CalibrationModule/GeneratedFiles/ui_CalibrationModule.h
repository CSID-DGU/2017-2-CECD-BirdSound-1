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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
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
    QComboBox *cameraList;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalibrationModuleClass)
    {
        if (CalibrationModuleClass->objectName().isEmpty())
            CalibrationModuleClass->setObjectName(QStringLiteral("CalibrationModuleClass"));
        CalibrationModuleClass->resize(773, 504);
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
        startStreaming->setGeometry(QRect(10, 130, 75, 23));
        captrueImage = new QPushButton(centralWidget);
        captrueImage->setObjectName(QStringLiteral("captrueImage"));
        captrueImage->setGeometry(QRect(10, 160, 75, 23));
        stopStreaming = new QPushButton(centralWidget);
        stopStreaming->setObjectName(QStringLiteral("stopStreaming"));
        stopStreaming->setGeometry(QRect(10, 190, 75, 23));
        cameraList = new QComboBox(centralWidget);
        cameraList->setObjectName(QStringLiteral("cameraList"));
        cameraList->setGeometry(QRect(10, 60, 76, 22));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(200, 10, 561, 441));
        CalibrationModuleClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CalibrationModuleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 773, 21));
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
    } // retranslateUi

};

namespace Ui {
    class CalibrationModuleClass: public Ui_CalibrationModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONMODULE_H
