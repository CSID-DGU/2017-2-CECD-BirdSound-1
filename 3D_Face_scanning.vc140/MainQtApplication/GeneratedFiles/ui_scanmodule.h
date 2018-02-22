/********************************************************************************
** Form generated from reading UI file 'scanmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANMODULE_H
#define UI_SCANMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanModule
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QFrame *frame_3;
    QPushButton *NextButton;

    void setupUi(QWidget *ScanModule)
    {
        if (ScanModule->objectName().isEmpty())
            ScanModule->setObjectName(QStringLiteral("ScanModule"));
        ScanModule->resize(1200, 700);
        ScanModule->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background: \"#F4F4F4\";\n"
"}\n"
"QFrame{\n"
"background:black;\n"
"}\n"
"QPushButton {\n"
"font: 12pt \"\353\247\221\354\235\200\352\263\240\353\224\225\";\n"
"background: \"#2896DC\";\n"
"border-radius: 5;\n"
"}\n"
"QPushButton:hover{\n"
"font: bold;\n"
"background: #2896DC;\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-color:\"black\";\n"
"}"));
        frame = new QFrame(ScanModule);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 30, 371, 481));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(ScanModule);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(410, 30, 371, 481));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(ScanModule);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(800, 30, 371, 481));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        NextButton = new QPushButton(ScanModule);
        NextButton->setObjectName(QStringLiteral("NextButton"));
        NextButton->setGeometry(QRect(970, 590, 151, 41));
        NextButton->setStyleSheet(QStringLiteral(""));

        retranslateUi(ScanModule);

        QMetaObject::connectSlotsByName(ScanModule);
    } // setupUi

    void retranslateUi(QWidget *ScanModule)
    {
        ScanModule->setWindowTitle(QApplication::translate("ScanModule", "Form", Q_NULLPTR));
        NextButton->setText(QApplication::translate("ScanModule", "Align", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScanModule: public Ui_ScanModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANMODULE_H
