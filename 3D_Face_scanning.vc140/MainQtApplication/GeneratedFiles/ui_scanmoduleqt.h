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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
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
    QPushButton *RightSaveBtn;
    QPushButton *StreamingBtn;
    QPushButton *MultiCapBtn;
    QMenuBar *menuBar;
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
        CapBtn->setGeometry(QRect(1150, 690, 91, 31));
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
        NextBtn->setGeometry(QRect(1260, 690, 91, 31));
        TitleRight = new QLabel(centralWidget);
        TitleRight->setObjectName(QStringLiteral("TitleRight"));
        TitleRight->setGeometry(QRect(960, 690, 61, 16));
        Title2D = new QLabel(centralWidget);
        Title2D->setObjectName(QStringLiteral("Title2D"));
        Title2D->setGeometry(QRect(480, 620, 441, 41));
        RightSaveBtn = new QPushButton(centralWidget);
        RightSaveBtn->setObjectName(QStringLiteral("RightSaveBtn"));
        RightSaveBtn->setGeometry(QRect(1030, 690, 71, 20));
        StreamingBtn = new QPushButton(centralWidget);
        StreamingBtn->setObjectName(QStringLiteral("StreamingBtn"));
        StreamingBtn->setGeometry(QRect(1040, 720, 101, 51));
        MultiCapBtn = new QPushButton(centralWidget);
        MultiCapBtn->setObjectName(QStringLiteral("MultiCapBtn"));
        MultiCapBtn->setGeometry(QRect(1150, 730, 91, 31));
        ScanModuleQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ScanModuleQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1372, 31));
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
        RightSaveBtn->setText(QApplication::translate("ScanModuleQTClass", "SAVE", Q_NULLPTR));
        StreamingBtn->setText(QApplication::translate("ScanModuleQTClass", "Streaming", Q_NULLPTR));
        MultiCapBtn->setText(QApplication::translate("ScanModuleQTClass", "SavePic", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScanModuleQTClass: public Ui_ScanModuleQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANMODULEQT_H
