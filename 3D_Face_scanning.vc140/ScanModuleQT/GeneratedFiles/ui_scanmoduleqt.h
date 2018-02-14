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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanModuleQTClass
{
public:
    QWidget *centralWidget;
    QTextBrowser *OutPutText;
    QFrame *Viewer_cad_RIGHT;
    QFrame *Viewer_cad_FRONT;
    QPushButton *CapBtn;
    QPushButton *FrontSaveBtn;
    QFrame *Viewer_cad_3D;
    QPushButton *LeftSaveBtn;
    QFrame *Viewer_cad_LEFT;
    QLabel *TitleFront;
    QLabel *Title3D;
    QLabel *TitleLeft;
    QFrame *Viewer_cad_2D;
    QPushButton *NextBtn;
    QLabel *TitleRight;
    QLabel *Title2D;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QSlider *horizontalSlider_11;
    QSlider *horizontalSlider_12;
    QLabel *ParameterTitle;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QSlider *horizontalSlider_13;
    QLabel *label_30;
    QSlider *horizontalSlider_14;
    QSlider *horizontalSlider_15;
    QLabel *label_31;
    QSlider *horizontalSlider_16;
    QLabel *label_32;
    QSlider *horizontalSlider_17;
    QLabel *label_33;
    QSlider *horizontalSlider_18;
    QLabel *label_34;
    QSlider *horizontalSlider_19;
    QLabel *label_35;
    QSlider *horizontalSlider_20;
    QLabel *label_36;
    QPushButton *RightSaveBtn;
    QPushButton *StreamingBtn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ScanModuleQTClass)
    {
        if (ScanModuleQTClass->objectName().isEmpty())
            ScanModuleQTClass->setObjectName(QStringLiteral("ScanModuleQTClass"));
        ScanModuleQTClass->resize(1372, 839);
        centralWidget = new QWidget(ScanModuleQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        OutPutText = new QTextBrowser(centralWidget);
        OutPutText->setObjectName(QStringLiteral("OutPutText"));
        OutPutText->setGeometry(QRect(20, 680, 911, 91));
        Viewer_cad_RIGHT = new QFrame(centralWidget);
        Viewer_cad_RIGHT->setObjectName(QStringLiteral("Viewer_cad_RIGHT"));
        Viewer_cad_RIGHT->setGeometry(QRect(950, 480, 150, 200));
        Viewer_cad_RIGHT->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_RIGHT->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_RIGHT->setFrameShadow(QFrame::Raised);
        Viewer_cad_FRONT = new QFrame(centralWidget);
        Viewer_cad_FRONT->setObjectName(QStringLiteral("Viewer_cad_FRONT"));
        Viewer_cad_FRONT->setGeometry(QRect(950, 240, 150, 200));
        Viewer_cad_FRONT->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_FRONT->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_FRONT->setFrameShadow(QFrame::Raised);
        CapBtn = new QPushButton(centralWidget);
        CapBtn->setObjectName(QStringLiteral("CapBtn"));
        CapBtn->setGeometry(QRect(1150, 720, 101, 51));
        FrontSaveBtn = new QPushButton(centralWidget);
        FrontSaveBtn->setObjectName(QStringLiteral("FrontSaveBtn"));
        FrontSaveBtn->setGeometry(QRect(1030, 450, 71, 20));
        Viewer_cad_3D = new QFrame(centralWidget);
        Viewer_cad_3D->setObjectName(QStringLiteral("Viewer_cad_3D"));
        Viewer_cad_3D->setGeometry(QRect(20, 10, 450, 600));
        Viewer_cad_3D->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_3D->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_3D->setFrameShadow(QFrame::Raised);
        LeftSaveBtn = new QPushButton(centralWidget);
        LeftSaveBtn->setObjectName(QStringLiteral("LeftSaveBtn"));
        LeftSaveBtn->setGeometry(QRect(1030, 210, 71, 20));
        Viewer_cad_LEFT = new QFrame(centralWidget);
        Viewer_cad_LEFT->setObjectName(QStringLiteral("Viewer_cad_LEFT"));
        Viewer_cad_LEFT->setGeometry(QRect(950, 10, 150, 200));
        Viewer_cad_LEFT->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"border: 6px solid ;\n"
"border-color: rgb(255, 0, 0);"));
        Viewer_cad_LEFT->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_LEFT->setFrameShadow(QFrame::Raised);
        TitleFront = new QLabel(centralWidget);
        TitleFront->setObjectName(QStringLiteral("TitleFront"));
        TitleFront->setGeometry(QRect(960, 450, 61, 16));
        Title3D = new QLabel(centralWidget);
        Title3D->setObjectName(QStringLiteral("Title3D"));
        Title3D->setGeometry(QRect(30, 620, 431, 41));
        TitleLeft = new QLabel(centralWidget);
        TitleLeft->setObjectName(QStringLiteral("TitleLeft"));
        TitleLeft->setGeometry(QRect(960, 210, 61, 16));
        Viewer_cad_2D = new QFrame(centralWidget);
        Viewer_cad_2D->setObjectName(QStringLiteral("Viewer_cad_2D"));
        Viewer_cad_2D->setGeometry(QRect(480, 10, 450, 600));
        Viewer_cad_2D->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_2D->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_2D->setFrameShadow(QFrame::Raised);
        NextBtn = new QPushButton(centralWidget);
        NextBtn->setObjectName(QStringLiteral("NextBtn"));
        NextBtn->setGeometry(QRect(1260, 720, 101, 51));
        TitleRight = new QLabel(centralWidget);
        TitleRight->setObjectName(QStringLiteral("TitleRight"));
        TitleRight->setGeometry(QRect(960, 690, 61, 16));
        Title2D = new QLabel(centralWidget);
        Title2D->setObjectName(QStringLiteral("Title2D"));
        Title2D->setGeometry(QRect(480, 620, 441, 41));
        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(1140, 10, 221, 671));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 219, 669));
        horizontalSlider_11 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_11->setObjectName(QStringLiteral("horizontalSlider_11"));
        horizontalSlider_11->setGeometry(QRect(10, 70, 160, 22));
        horizontalSlider_11->setOrientation(Qt::Horizontal);
        horizontalSlider_12 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_12->setObjectName(QStringLiteral("horizontalSlider_12"));
        horizontalSlider_12->setGeometry(QRect(10, 130, 160, 22));
        horizontalSlider_12->setOrientation(Qt::Horizontal);
        ParameterTitle = new QLabel(scrollAreaWidgetContents_2);
        ParameterTitle->setObjectName(QStringLiteral("ParameterTitle"));
        ParameterTitle->setGeometry(QRect(10, 10, 151, 16));
        label_27 = new QLabel(scrollAreaWidgetContents_2);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(10, 50, 151, 16));
        label_28 = new QLabel(scrollAreaWidgetContents_2);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(10, 110, 151, 16));
        label_29 = new QLabel(scrollAreaWidgetContents_2);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(10, 180, 151, 16));
        horizontalSlider_13 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_13->setObjectName(QStringLiteral("horizontalSlider_13"));
        horizontalSlider_13->setGeometry(QRect(10, 200, 160, 22));
        horizontalSlider_13->setOrientation(Qt::Horizontal);
        label_30 = new QLabel(scrollAreaWidgetContents_2);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(10, 240, 151, 16));
        horizontalSlider_14 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_14->setObjectName(QStringLiteral("horizontalSlider_14"));
        horizontalSlider_14->setGeometry(QRect(10, 260, 160, 22));
        horizontalSlider_14->setOrientation(Qt::Horizontal);
        horizontalSlider_15 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_15->setObjectName(QStringLiteral("horizontalSlider_15"));
        horizontalSlider_15->setGeometry(QRect(10, 320, 160, 22));
        horizontalSlider_15->setOrientation(Qt::Horizontal);
        label_31 = new QLabel(scrollAreaWidgetContents_2);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(10, 300, 151, 16));
        horizontalSlider_16 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_16->setObjectName(QStringLiteral("horizontalSlider_16"));
        horizontalSlider_16->setGeometry(QRect(10, 380, 160, 22));
        horizontalSlider_16->setOrientation(Qt::Horizontal);
        label_32 = new QLabel(scrollAreaWidgetContents_2);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(10, 360, 151, 16));
        horizontalSlider_17 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_17->setObjectName(QStringLiteral("horizontalSlider_17"));
        horizontalSlider_17->setGeometry(QRect(10, 440, 160, 22));
        horizontalSlider_17->setOrientation(Qt::Horizontal);
        label_33 = new QLabel(scrollAreaWidgetContents_2);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(10, 420, 151, 16));
        horizontalSlider_18 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_18->setObjectName(QStringLiteral("horizontalSlider_18"));
        horizontalSlider_18->setGeometry(QRect(10, 490, 160, 22));
        horizontalSlider_18->setOrientation(Qt::Horizontal);
        label_34 = new QLabel(scrollAreaWidgetContents_2);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(10, 470, 151, 16));
        horizontalSlider_19 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_19->setObjectName(QStringLiteral("horizontalSlider_19"));
        horizontalSlider_19->setGeometry(QRect(10, 550, 160, 22));
        horizontalSlider_19->setOrientation(Qt::Horizontal);
        label_35 = new QLabel(scrollAreaWidgetContents_2);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(10, 530, 151, 16));
        horizontalSlider_20 = new QSlider(scrollAreaWidgetContents_2);
        horizontalSlider_20->setObjectName(QStringLiteral("horizontalSlider_20"));
        horizontalSlider_20->setGeometry(QRect(10, 610, 160, 22));
        horizontalSlider_20->setOrientation(Qt::Horizontal);
        label_36 = new QLabel(scrollAreaWidgetContents_2);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(10, 590, 151, 16));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        RightSaveBtn = new QPushButton(centralWidget);
        RightSaveBtn->setObjectName(QStringLiteral("RightSaveBtn"));
        RightSaveBtn->setGeometry(QRect(1030, 690, 71, 20));
        StreamingBtn = new QPushButton(centralWidget);
        StreamingBtn->setObjectName(QStringLiteral("StreamingBtn"));
        StreamingBtn->setGeometry(QRect(1040, 720, 101, 51));
        ScanModuleQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ScanModuleQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1372, 21));
        ScanModuleQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ScanModuleQTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ScanModuleQTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ScanModuleQTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ScanModuleQTClass->setStatusBar(statusBar);

        retranslateUi(ScanModuleQTClass);

        QMetaObject::connectSlotsByName(ScanModuleQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *ScanModuleQTClass)
    {
        ScanModuleQTClass->setWindowTitle(QApplication::translate("ScanModuleQTClass", "ScanModuleQT", Q_NULLPTR));
        OutPutText->setHtml(QApplication::translate("ScanModuleQTClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">librealsense \353\262\204\354\240\204 : 2.9.0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">VTK \353\262\204\354\240\204 : 8.1.0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Start straming...</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">parameter changed : 00000 -&gt; 00000<br />... (focus on tail)<br />saving LEFT CAPT"
                        "URE DATA ....<br />saved $PATH !</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        CapBtn->setText(QApplication::translate("ScanModuleQTClass", "CAPTURE", Q_NULLPTR));
        FrontSaveBtn->setText(QApplication::translate("ScanModuleQTClass", "SAVE", Q_NULLPTR));
        LeftSaveBtn->setText(QApplication::translate("ScanModuleQTClass", "SAVE", Q_NULLPTR));
        TitleFront->setText(QApplication::translate("ScanModuleQTClass", "FRONT", Q_NULLPTR));
        Title3D->setText(QApplication::translate("ScanModuleQTClass", "3D View", Q_NULLPTR));
        TitleLeft->setText(QApplication::translate("ScanModuleQTClass", "LEFT", Q_NULLPTR));
        NextBtn->setText(QApplication::translate("ScanModuleQTClass", "NEXT", Q_NULLPTR));
        TitleRight->setText(QApplication::translate("ScanModuleQTClass", "RIGHT", Q_NULLPTR));
        Title2D->setText(QApplication::translate("ScanModuleQTClass", "2D View <1920x1080 / RGB8 / 30FPS>", Q_NULLPTR));
        ParameterTitle->setText(QApplication::translate("ScanModuleQTClass", "Camera Parameter", Q_NULLPTR));
        label_27->setText(QApplication::translate("ScanModuleQTClass", "Parameter1", Q_NULLPTR));
        label_28->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        label_29->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        label_30->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        label_31->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        label_32->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        label_33->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        label_34->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        label_35->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        label_36->setText(QApplication::translate("ScanModuleQTClass", "Parameter2", Q_NULLPTR));
        RightSaveBtn->setText(QApplication::translate("ScanModuleQTClass", "SAVE", Q_NULLPTR));
        StreamingBtn->setText(QApplication::translate("ScanModuleQTClass", "Streaming", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScanModuleQTClass: public Ui_ScanModuleQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANMODULEQT_H
