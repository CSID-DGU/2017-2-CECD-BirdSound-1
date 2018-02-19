/********************************************************************************
** Form generated from reading UI file 'valuetestmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VALUETESTMODULE_H
#define UI_VALUETESTMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ValueTestModuleClass
{
public:
    QFrame *Viewer_cad_RS;
    QTextBrowser *textBrowser;
    QPushButton *CapDepBtn;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QSlider *horizontalSlider_3;
    QLabel *label_15;
    QSlider *horizontalSlider_4;
    QSlider *horizontalSlider_5;
    QLabel *label_16;
    QSlider *horizontalSlider_6;
    QLabel *label_17;
    QSlider *horizontalSlider_7;
    QLabel *label_18;
    QSlider *horizontalSlider_8;
    QLabel *label_19;
    QSlider *horizontalSlider_9;
    QLabel *label_20;
    QSlider *horizontalSlider_10;
    QLabel *label_21;
    QScrollBar *verticalScrollBar;
    QLabel *label_8;
    QTextBrowser *textBrowser_2;
    QLabel *label_9;
    QScrollBar *verticalScrollBar_2;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QTextBrowser *textBrowser_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QTextBrowser *textBrowser_4;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QTextBrowser *textBrowser_5;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QTextBrowser *textBrowser_6;

    void setupUi(QWidget *ValueTestModuleClass)
    {
        if (ValueTestModuleClass->objectName().isEmpty())
            ValueTestModuleClass->setObjectName(QStringLiteral("ValueTestModuleClass"));
        ValueTestModuleClass->resize(1392, 691);
        Viewer_cad_RS = new QFrame(ValueTestModuleClass);
        Viewer_cad_RS->setObjectName(QStringLiteral("Viewer_cad_RS"));
        Viewer_cad_RS->setGeometry(QRect(10, 10, 641, 461));
        Viewer_cad_RS->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_RS->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_RS->setFrameShadow(QFrame::Raised);
        textBrowser = new QTextBrowser(ValueTestModuleClass);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 540, 1111, 141));
        CapDepBtn = new QPushButton(ValueTestModuleClass);
        CapDepBtn->setObjectName(QStringLiteral("CapDepBtn"));
        CapDepBtn->setGeometry(QRect(550, 480, 101, 51));
        scrollArea = new QScrollArea(ValueTestModuleClass);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(1130, 10, 251, 671));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 249, 669));
        horizontalSlider = new QSlider(scrollAreaWidgetContents);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 70, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(10, 130, 160, 22));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label_11 = new QLabel(scrollAreaWidgetContents);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 10, 151, 16));
        label_12 = new QLabel(scrollAreaWidgetContents);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 50, 151, 16));
        label_13 = new QLabel(scrollAreaWidgetContents);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 110, 151, 16));
        label_14 = new QLabel(scrollAreaWidgetContents);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 180, 151, 16));
        horizontalSlider_3 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(10, 200, 160, 22));
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        label_15 = new QLabel(scrollAreaWidgetContents);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 240, 151, 16));
        horizontalSlider_4 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setGeometry(QRect(10, 260, 160, 22));
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        horizontalSlider_5 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setGeometry(QRect(10, 320, 160, 22));
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        label_16 = new QLabel(scrollAreaWidgetContents);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 300, 151, 16));
        horizontalSlider_6 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setGeometry(QRect(10, 380, 160, 22));
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        label_17 = new QLabel(scrollAreaWidgetContents);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 360, 151, 16));
        horizontalSlider_7 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_7->setObjectName(QStringLiteral("horizontalSlider_7"));
        horizontalSlider_7->setGeometry(QRect(10, 440, 160, 22));
        horizontalSlider_7->setOrientation(Qt::Horizontal);
        label_18 = new QLabel(scrollAreaWidgetContents);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 420, 151, 16));
        horizontalSlider_8 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_8->setObjectName(QStringLiteral("horizontalSlider_8"));
        horizontalSlider_8->setGeometry(QRect(10, 490, 160, 22));
        horizontalSlider_8->setOrientation(Qt::Horizontal);
        label_19 = new QLabel(scrollAreaWidgetContents);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 470, 151, 16));
        horizontalSlider_9 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_9->setObjectName(QStringLiteral("horizontalSlider_9"));
        horizontalSlider_9->setGeometry(QRect(10, 550, 160, 22));
        horizontalSlider_9->setOrientation(Qt::Horizontal);
        label_20 = new QLabel(scrollAreaWidgetContents);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 530, 151, 16));
        horizontalSlider_10 = new QSlider(scrollAreaWidgetContents);
        horizontalSlider_10->setObjectName(QStringLiteral("horizontalSlider_10"));
        horizontalSlider_10->setGeometry(QRect(10, 610, 160, 22));
        horizontalSlider_10->setOrientation(Qt::Horizontal);
        label_21 = new QLabel(scrollAreaWidgetContents);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 590, 151, 16));
        verticalScrollBar = new QScrollBar(scrollAreaWidgetContents);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(230, 0, 16, 671));
        verticalScrollBar->setOrientation(Qt::Vertical);
        scrollArea->setWidget(scrollAreaWidgetContents);
        label_8 = new QLabel(ValueTestModuleClass);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 470, 61, 41));
        textBrowser_2 = new QTextBrowser(ValueTestModuleClass);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(670, 20, 301, 61));
        label_9 = new QLabel(ValueTestModuleClass);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(660, 10, 461, 521));
        label_9->setStyleSheet(QLatin1String("border-radius: 4px;\n"
"border: 2px solid gray;\n"
"background-image: url(:/myImage.png);\n"
""));
        verticalScrollBar_2 = new QScrollBar(ValueTestModuleClass);
        verticalScrollBar_2->setObjectName(QStringLiteral("verticalScrollBar_2"));
        verticalScrollBar_2->setGeometry(QRect(1100, 20, 16, 501));
        verticalScrollBar_2->setOrientation(Qt::Vertical);
        textEdit = new QTextEdit(ValueTestModuleClass);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(430, 480, 104, 51));
        pushButton = new QPushButton(ValueTestModuleClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(984, 20, 101, 23));
        pushButton_2 = new QPushButton(ValueTestModuleClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(984, 50, 101, 23));
        pushButton_3 = new QPushButton(ValueTestModuleClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(984, 90, 101, 23));
        pushButton_4 = new QPushButton(ValueTestModuleClass);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(984, 120, 101, 23));
        textBrowser_3 = new QTextBrowser(ValueTestModuleClass);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(670, 90, 301, 61));
        pushButton_5 = new QPushButton(ValueTestModuleClass);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(984, 160, 101, 23));
        pushButton_6 = new QPushButton(ValueTestModuleClass);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(984, 190, 101, 23));
        textBrowser_4 = new QTextBrowser(ValueTestModuleClass);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(670, 160, 301, 61));
        pushButton_7 = new QPushButton(ValueTestModuleClass);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(984, 230, 101, 23));
        pushButton_8 = new QPushButton(ValueTestModuleClass);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(984, 260, 101, 23));
        textBrowser_5 = new QTextBrowser(ValueTestModuleClass);
        textBrowser_5->setObjectName(QStringLiteral("textBrowser_5"));
        textBrowser_5->setGeometry(QRect(670, 230, 301, 61));
        pushButton_9 = new QPushButton(ValueTestModuleClass);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(984, 300, 101, 23));
        pushButton_10 = new QPushButton(ValueTestModuleClass);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(984, 330, 101, 23));
        textBrowser_6 = new QTextBrowser(ValueTestModuleClass);
        textBrowser_6->setObjectName(QStringLiteral("textBrowser_6"));
        textBrowser_6->setGeometry(QRect(670, 300, 301, 61));
        label_9->raise();
        Viewer_cad_RS->raise();
        textBrowser->raise();
        CapDepBtn->raise();
        scrollArea->raise();
        label_8->raise();
        textBrowser_2->raise();
        verticalScrollBar_2->raise();
        textEdit->raise();
        pushButton->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        pushButton_4->raise();
        textBrowser_3->raise();
        pushButton_5->raise();
        pushButton_6->raise();
        textBrowser_4->raise();
        pushButton_7->raise();
        pushButton_8->raise();
        textBrowser_5->raise();
        pushButton_9->raise();
        pushButton_10->raise();
        textBrowser_6->raise();

        retranslateUi(ValueTestModuleClass);

        QMetaObject::connectSlotsByName(ValueTestModuleClass);
    } // setupUi

    void retranslateUi(QWidget *ValueTestModuleClass)
    {
        ValueTestModuleClass->setWindowTitle(QApplication::translate("ValueTestModuleClass", "ValueTestModule", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("ValueTestModuleClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">librealsense \353\262\204\354\240\204 : 2.9.0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">VTK \353\262\204\354\240\204 : 8.1.0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Start straming...</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">parameter changed : 00000 -&gt; 00000</p>\n"
"<p style=\" margin-top:0px; margin-bot"
                        "tom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\353\266\204\354\204\235\354\231\204\353\243\214!<br />... (focus on tail)<br /></p></body></html>", Q_NULLPTR));
        CapDepBtn->setText(QApplication::translate("ValueTestModuleClass", "START", Q_NULLPTR));
        label_11->setText(QApplication::translate("ValueTestModuleClass", "Camera Parameter", Q_NULLPTR));
        label_12->setText(QApplication::translate("ValueTestModuleClass", "Parameter1", Q_NULLPTR));
        label_13->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_14->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_15->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_16->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_17->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_18->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_19->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_20->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_21->setText(QApplication::translate("ValueTestModuleClass", "Parameter2", Q_NULLPTR));
        label_8->setText(QApplication::translate("ValueTestModuleClass", "3D View", Q_NULLPTR));
        textBrowser_2->setHtml(QApplication::translate("ValueTestModuleClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[\354\264\254\354\230\201\352\261\260\353\246\254 00cm]</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">RMS \354\230\244\354\260\250 :  000<br />000 \354\230\244\354\260\250 : 000 </p></body></html>", Q_NULLPTR));
        label_9->setText(QString());
        textEdit->setHtml(QApplication::translate("ValueTestModuleClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\354\264\254\354\230\201 \352\261\260\353\246\254 \354\236\205\353\240\245</p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ValueTestModuleClass", "View Param", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ValueTestModuleClass", "Capture view", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ValueTestModuleClass", "View Param", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("ValueTestModuleClass", "Capture view", Q_NULLPTR));
        textBrowser_3->setHtml(QApplication::translate("ValueTestModuleClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[\354\264\254\354\230\201\352\261\260\353\246\254 00cm]</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">RMS \354\230\244\354\260\250 :  000<br />000 \354\230\244\354\260\250 : 000 </p></body></html>", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("ValueTestModuleClass", "View Param", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("ValueTestModuleClass", "Capture view", Q_NULLPTR));
        textBrowser_4->setHtml(QApplication::translate("ValueTestModuleClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[\354\264\254\354\230\201\352\261\260\353\246\254 00cm]</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">RMS \354\230\244\354\260\250 :  000<br />000 \354\230\244\354\260\250 : 000 </p></body></html>", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("ValueTestModuleClass", "View Param", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("ValueTestModuleClass", "Capture view", Q_NULLPTR));
        textBrowser_5->setHtml(QApplication::translate("ValueTestModuleClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[\354\264\254\354\230\201\352\261\260\353\246\254 00cm]</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">RMS \354\230\244\354\260\250 :  000<br />000 \354\230\244\354\260\250 : 000 </p></body></html>", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("ValueTestModuleClass", "View Param", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("ValueTestModuleClass", "Capture view", Q_NULLPTR));
        textBrowser_6->setHtml(QApplication::translate("ValueTestModuleClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[\354\264\254\354\230\201\352\261\260\353\246\254 00cm]</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">RMS \354\230\244\354\260\250 :  000<br />000 \354\230\244\354\260\250 : 000 </p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ValueTestModuleClass: public Ui_ValueTestModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VALUETESTMODULE_H
