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
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;

    void setupUi(QWidget *DemoFirstPart)
    {
        if (DemoFirstPart->objectName().isEmpty())
            DemoFirstPart->setObjectName(QStringLiteral("DemoFirstPart"));
        DemoFirstPart->resize(1102, 846);
        label = new QLabel(DemoFirstPart);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 640, 360));
        label->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        label_2 = new QLabel(DemoFirstPart);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 121, 21));
        label_2->setTextFormat(Qt::PlainText);
        label_3 = new QLabel(DemoFirstPart);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 470, 640, 360));
        label_3->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        label_4 = new QLabel(DemoFirstPart);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 440, 121, 21));
        label_4->setTextFormat(Qt::PlainText);
        scrollArea = new QScrollArea(DemoFirstPart);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(670, 20, 411, 421));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 409, 419));
        scrollArea->setWidget(scrollAreaWidgetContents);
        pushButton = new QPushButton(DemoFirstPart);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(960, 780, 121, 51));
        pushButton_2 = new QPushButton(DemoFirstPart);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(830, 780, 121, 51));
        scrollArea_2 = new QScrollArea(DemoFirstPart);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(670, 450, 411, 321));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 409, 319));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        retranslateUi(DemoFirstPart);

        QMetaObject::connectSlotsByName(DemoFirstPart);
    } // setupUi

    void retranslateUi(QWidget *DemoFirstPart)
    {
        DemoFirstPart->setWindowTitle(QApplication::translate("DemoFirstPart", "Form", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("DemoFirstPart", "Color Image", Q_NULLPTR));
        label_3->setText(QString());
        label_4->setText(QApplication::translate("DemoFirstPart", "Depth Image", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DemoFirstPart", "CAPTURE", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("DemoFirstPart", "START", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DemoFirstPart: public Ui_DemoFirstPart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMOFIRSTPART_H
