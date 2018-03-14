/********************************************************************************
** Form generated from reading UI file 'registrationmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONMODULE_H
#define UI_REGISTRATIONMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrationModule
{
public:
    QFrame *frame;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *SaveButton;
    QPushButton *QuitButton;

    void setupUi(QWidget *RegistrationModule)
    {
        if (RegistrationModule->objectName().isEmpty())
            RegistrationModule->setObjectName(QStringLiteral("RegistrationModule"));
        RegistrationModule->resize(1200, 800);
        RegistrationModule->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background: \"#F4F4F4\";\n"
"}\n"
"QFrame{\n"
"background:black;\n"
"}\n"
"QPushButton {\n"
"font: 12pt \"\353\247\221\354\235\200\352\263\240\353\224\225\";\n"
"background: \"#2896DC\";\n"
"padding:12px;\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-color:\"black\";\n"
"border-radius: 5;\n"
"}\n"
"#QuitButton{\n"
"background: \"#F4F4F4\";\n"
"}\n"
"QPushButton:hover{\n"
"font: bold;\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-color:\"black\";\n"
"}"));
        frame = new QFrame(RegistrationModule);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 971, 781));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(RegistrationModule);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(1010, 130, 161, 131));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        SaveButton = new QPushButton(layoutWidget);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));

        verticalLayout->addWidget(SaveButton);

        QuitButton = new QPushButton(layoutWidget);
        QuitButton->setObjectName(QStringLiteral("QuitButton"));

        verticalLayout->addWidget(QuitButton);


        retranslateUi(RegistrationModule);

        QMetaObject::connectSlotsByName(RegistrationModule);
    } // setupUi

    void retranslateUi(QWidget *RegistrationModule)
    {
        RegistrationModule->setWindowTitle(QApplication::translate("RegistrationModule", "Form", Q_NULLPTR));
        SaveButton->setText(QApplication::translate("RegistrationModule", "Save", Q_NULLPTR));
        QuitButton->setText(QApplication::translate("RegistrationModule", "Quit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegistrationModule: public Ui_RegistrationModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONMODULE_H
