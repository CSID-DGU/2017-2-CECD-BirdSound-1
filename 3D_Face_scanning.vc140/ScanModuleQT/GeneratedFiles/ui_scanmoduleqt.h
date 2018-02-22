/********************************************************************************
** Form generated from reading UI file 'scanmoduleqt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANMODULEQT_H
#define UI_SCANMODULEQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanModuleQTClass
{
public:
    QWidget *centralWidget;
    QPushButton *CapBtn;
    QFrame *Viewer_cad_3D;
    QFrame *Viewer_cad_2D;
    QPushButton *NextBtn;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QSlider *Median3D_slid;
    QLabel *ParameterTitle;
    QLabel *label_27;
    QLabel *label_29;
    QSlider *GausianStd_slid;
    QSlider *GausianRad_slid;
    QPushButton *MeshSmoothBtn;
    QPushButton *MedianBtn;
    QPushButton *GausianStdBtn;
    QPushButton *GausianRadBtn;
    QPushButton *ResetBtn;
    QPushButton *FilterApplyBtn;
    QPushButton *NextBtn2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QPushButton *MultiCatpBtn;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ScanModuleQTClass)
    {
        if (ScanModuleQTClass->objectName().isEmpty())
            ScanModuleQTClass->setObjectName(QStringLiteral("ScanModuleQTClass"));
        ScanModuleQTClass->resize(1334, 915);
        centralWidget = new QWidget(ScanModuleQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CapBtn = new QPushButton(centralWidget);
        CapBtn->setObjectName(QStringLiteral("CapBtn"));
        CapBtn->setGeometry(QRect(1040, 700, 111, 41));
        Viewer_cad_3D = new QFrame(centralWidget);
        Viewer_cad_3D->setObjectName(QStringLiteral("Viewer_cad_3D"));
        Viewer_cad_3D->setGeometry(QRect(20, 10, 891, 421));
        Viewer_cad_3D->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_3D->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_3D->setFrameShadow(QFrame::Raised);
        Viewer_cad_2D = new QFrame(centralWidget);
        Viewer_cad_2D->setObjectName(QStringLiteral("Viewer_cad_2D"));
        Viewer_cad_2D->setGeometry(QRect(20, 450, 891, 431));
        Viewer_cad_2D->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_2D->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_2D->setFrameShadow(QFrame::Raised);
        NextBtn = new QPushButton(centralWidget);
        NextBtn->setObjectName(QStringLiteral("NextBtn"));
        NextBtn->setGeometry(QRect(1040, 750, 111, 51));
        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(1030, 10, 261, 671));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 259, 669));
        Median3D_slid = new QSlider(scrollAreaWidgetContents_2);
        Median3D_slid->setObjectName(QStringLiteral("Median3D_slid"));
        Median3D_slid->setGeometry(QRect(10, 70, 160, 22));
        Median3D_slid->setMinimum(1);
        Median3D_slid->setMaximum(5);
        Median3D_slid->setOrientation(Qt::Horizontal);
        ParameterTitle = new QLabel(scrollAreaWidgetContents_2);
        ParameterTitle->setObjectName(QStringLiteral("ParameterTitle"));
        ParameterTitle->setGeometry(QRect(10, 10, 151, 16));
        label_27 = new QLabel(scrollAreaWidgetContents_2);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(10, 50, 241, 16));
        label_29 = new QLabel(scrollAreaWidgetContents_2);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(10, 180, 171, 16));
        GausianStd_slid = new QSlider(scrollAreaWidgetContents_2);
        GausianStd_slid->setObjectName(QStringLiteral("GausianStd_slid"));
        GausianStd_slid->setGeometry(QRect(10, 200, 160, 22));
        GausianStd_slid->setMinimum(1);
        GausianStd_slid->setMaximum(100);
        GausianStd_slid->setSingleStep(5);
        GausianStd_slid->setOrientation(Qt::Horizontal);
        GausianRad_slid = new QSlider(scrollAreaWidgetContents_2);
        GausianRad_slid->setObjectName(QStringLiteral("GausianRad_slid"));
        GausianRad_slid->setGeometry(QRect(10, 230, 160, 22));
        GausianRad_slid->setMinimum(1);
        GausianRad_slid->setMaximum(100);
        GausianRad_slid->setSingleStep(5);
        GausianRad_slid->setOrientation(Qt::Horizontal);
        MeshSmoothBtn = new QPushButton(scrollAreaWidgetContents_2);
        MeshSmoothBtn->setObjectName(QStringLiteral("MeshSmoothBtn"));
        MeshSmoothBtn->setGeometry(QRect(10, 280, 141, 31));
        MedianBtn = new QPushButton(scrollAreaWidgetContents_2);
        MedianBtn->setObjectName(QStringLiteral("MedianBtn"));
        MedianBtn->setGeometry(QRect(170, 70, 75, 23));
        GausianStdBtn = new QPushButton(scrollAreaWidgetContents_2);
        GausianStdBtn->setObjectName(QStringLiteral("GausianStdBtn"));
        GausianStdBtn->setGeometry(QRect(170, 200, 75, 23));
        GausianRadBtn = new QPushButton(scrollAreaWidgetContents_2);
        GausianRadBtn->setObjectName(QStringLiteral("GausianRadBtn"));
        GausianRadBtn->setGeometry(QRect(170, 230, 75, 23));
        ResetBtn = new QPushButton(scrollAreaWidgetContents_2);
        ResetBtn->setObjectName(QStringLiteral("ResetBtn"));
        ResetBtn->setGeometry(QRect(20, 620, 75, 23));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        FilterApplyBtn = new QPushButton(centralWidget);
        FilterApplyBtn->setObjectName(QStringLiteral("FilterApplyBtn"));
        FilterApplyBtn->setGeometry(QRect(1180, 750, 101, 41));
        NextBtn2 = new QPushButton(centralWidget);
        NextBtn2->setObjectName(QStringLiteral("NextBtn2"));
        NextBtn2->setGeometry(QRect(1180, 800, 101, 41));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(1030, 690, 131, 171));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 129, 169));
        scrollArea->setWidget(scrollAreaWidgetContents);
        scrollArea_3 = new QScrollArea(centralWidget);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setGeometry(QRect(1170, 690, 121, 171));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 119, 169));
        MultiCatpBtn = new QPushButton(scrollAreaWidgetContents_3);
        MultiCatpBtn->setObjectName(QStringLiteral("MultiCatpBtn"));
        MultiCatpBtn->setGeometry(QRect(10, 10, 101, 41));
        scrollArea_3->setWidget(scrollAreaWidgetContents_3);
        ScanModuleQTClass->setCentralWidget(centralWidget);
        scrollArea_3->raise();
        scrollArea->raise();
        CapBtn->raise();
        Viewer_cad_3D->raise();
        Viewer_cad_2D->raise();
        NextBtn->raise();
        scrollArea_2->raise();
        FilterApplyBtn->raise();
        NextBtn2->raise();
        menuBar = new QMenuBar(ScanModuleQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1334, 21));
        ScanModuleQTClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(ScanModuleQTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ScanModuleQTClass->setStatusBar(statusBar);

        retranslateUi(ScanModuleQTClass);

        QMetaObject::connectSlotsByName(ScanModuleQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *ScanModuleQTClass)
    {
        ScanModuleQTClass->setWindowTitle(QApplication::translate("ScanModuleQTClass", "ScanModuleQT", Q_NULLPTR));
        CapBtn->setText(QApplication::translate("ScanModuleQTClass", "CAPTURE", Q_NULLPTR));
        NextBtn->setText(QApplication::translate("ScanModuleQTClass", "NEXT", Q_NULLPTR));
        ParameterTitle->setText(QApplication::translate("ScanModuleQTClass", "Camera Parameter", Q_NULLPTR));
        label_27->setText(QApplication::translate("ScanModuleQTClass", "Median 3D(Kernal Size) 1~5", Q_NULLPTR));
        label_29->setText(QApplication::translate("ScanModuleQTClass", "Gausian smooth(Std/Rad)", Q_NULLPTR));
        MeshSmoothBtn->setText(QApplication::translate("ScanModuleQTClass", "Mesh Smoothing", Q_NULLPTR));
        MedianBtn->setText(QApplication::translate("ScanModuleQTClass", "Complete", Q_NULLPTR));
        GausianStdBtn->setText(QApplication::translate("ScanModuleQTClass", "Complete", Q_NULLPTR));
        GausianRadBtn->setText(QApplication::translate("ScanModuleQTClass", "Complete", Q_NULLPTR));
        ResetBtn->setText(QApplication::translate("ScanModuleQTClass", "Reset", Q_NULLPTR));
        FilterApplyBtn->setText(QApplication::translate("ScanModuleQTClass", "Apply Filter", Q_NULLPTR));
        NextBtn2->setText(QApplication::translate("ScanModuleQTClass", "Next", Q_NULLPTR));
        MultiCatpBtn->setText(QApplication::translate("ScanModuleQTClass", "MultiCAPTURE", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScanModuleQTClass: public Ui_ScanModuleQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANMODULEQT_H
