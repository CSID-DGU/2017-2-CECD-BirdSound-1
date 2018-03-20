/********************************************************************************
** Form generated from reading UI file 'Align.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALIGN_H
#define UI_ALIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlignModuleClass
{
public:
    QTabWidget *rsWidget;
    QWidget *widget_3;
    QFrame *cadLeft;
    QFrame *cadFront;
    QFrame *cadRight;
    QSplitter *splitter_3;
    QPushButton *DefaultBtn_3;
    QPushButton *LandMarkBtn_3;
    QPushButton *ToOrignBtn_3;
    QSplitter *splitter_2;
    QPushButton *DefaultBtn_2;
    QPushButton *LandMarkBtn_2;
    QPushButton *ToOrignBtn_2;
    QSplitter *splitter_1;
    QPushButton *DefaultBtn_1;
    QPushButton *LandMarkBtn_1;
    QPushButton *ToOrignBtn_1;
    QPushButton *AlignBtn;

    void setupUi(QWidget *AlignModuleClass)
    {
        if (AlignModuleClass->objectName().isEmpty())
            AlignModuleClass->setObjectName(QStringLiteral("AlignModuleClass"));
        AlignModuleClass->resize(1450, 779);
        rsWidget = new QTabWidget(AlignModuleClass);
        rsWidget->setObjectName(QStringLiteral("rsWidget"));
        rsWidget->setEnabled(true);
        rsWidget->setGeometry(QRect(13, 13, 1422, 740));
        rsWidget->setMinimumSize(QSize(1422, 0));
        rsWidget->setMaximumSize(QSize(16777215, 16777215));
        rsWidget->setUsesScrollButtons(true);
        rsWidget->setMovable(false);
        widget_3 = new QWidget();
        widget_3->setObjectName(QStringLiteral("widget_3"));
        cadLeft = new QFrame(widget_3);
        cadLeft->setObjectName(QStringLiteral("cadLeft"));
        cadLeft->setGeometry(QRect(10, 80, 431, 571));
        cadLeft->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        cadLeft->setFrameShape(QFrame::StyledPanel);
        cadLeft->setFrameShadow(QFrame::Raised);
        cadFront = new QFrame(widget_3);
        cadFront->setObjectName(QStringLiteral("cadFront"));
        cadFront->setGeometry(QRect(490, 80, 431, 571));
        cadFront->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        cadFront->setFrameShape(QFrame::StyledPanel);
        cadFront->setFrameShadow(QFrame::Raised);
        cadRight = new QFrame(widget_3);
        cadRight->setObjectName(QStringLiteral("cadRight"));
        cadRight->setGeometry(QRect(980, 80, 431, 571));
        cadRight->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        cadRight->setFrameShape(QFrame::StyledPanel);
        cadRight->setFrameShadow(QFrame::Raised);
        splitter_3 = new QSplitter(widget_3);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setGeometry(QRect(980, 660, 431, 41));
        splitter_3->setOrientation(Qt::Horizontal);
        DefaultBtn_3 = new QPushButton(splitter_3);
        DefaultBtn_3->setObjectName(QStringLiteral("DefaultBtn_3"));
        splitter_3->addWidget(DefaultBtn_3);
        LandMarkBtn_3 = new QPushButton(splitter_3);
        LandMarkBtn_3->setObjectName(QStringLiteral("LandMarkBtn_3"));
        splitter_3->addWidget(LandMarkBtn_3);
        ToOrignBtn_3 = new QPushButton(splitter_3);
        ToOrignBtn_3->setObjectName(QStringLiteral("ToOrignBtn_3"));
        splitter_3->addWidget(ToOrignBtn_3);
        splitter_2 = new QSplitter(widget_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(490, 660, 431, 41));
        splitter_2->setOrientation(Qt::Horizontal);
        DefaultBtn_2 = new QPushButton(splitter_2);
        DefaultBtn_2->setObjectName(QStringLiteral("DefaultBtn_2"));
        splitter_2->addWidget(DefaultBtn_2);
        LandMarkBtn_2 = new QPushButton(splitter_2);
        LandMarkBtn_2->setObjectName(QStringLiteral("LandMarkBtn_2"));
        splitter_2->addWidget(LandMarkBtn_2);
        ToOrignBtn_2 = new QPushButton(splitter_2);
        ToOrignBtn_2->setObjectName(QStringLiteral("ToOrignBtn_2"));
        splitter_2->addWidget(ToOrignBtn_2);
        splitter_1 = new QSplitter(widget_3);
        splitter_1->setObjectName(QStringLiteral("splitter_1"));
        splitter_1->setGeometry(QRect(10, 660, 431, 41));
        splitter_1->setOrientation(Qt::Horizontal);
        DefaultBtn_1 = new QPushButton(splitter_1);
        DefaultBtn_1->setObjectName(QStringLiteral("DefaultBtn_1"));
        splitter_1->addWidget(DefaultBtn_1);
        LandMarkBtn_1 = new QPushButton(splitter_1);
        LandMarkBtn_1->setObjectName(QStringLiteral("LandMarkBtn_1"));
        splitter_1->addWidget(LandMarkBtn_1);
        ToOrignBtn_1 = new QPushButton(splitter_1);
        ToOrignBtn_1->setObjectName(QStringLiteral("ToOrignBtn_1"));
        splitter_1->addWidget(ToOrignBtn_1);
        AlignBtn = new QPushButton(widget_3);
        AlignBtn->setObjectName(QStringLiteral("AlignBtn"));
        AlignBtn->setGeometry(QRect(280, 10, 112, 34));
        rsWidget->addTab(widget_3, QString());

        retranslateUi(AlignModuleClass);

        rsWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AlignModuleClass);
    } // setupUi

    void retranslateUi(QWidget *AlignModuleClass)
    {
        AlignModuleClass->setWindowTitle(QApplication::translate("AlignModuleClass", "Form", Q_NULLPTR));
        DefaultBtn_3->setText(QApplication::translate("AlignModuleClass", "Default", Q_NULLPTR));
        LandMarkBtn_3->setText(QApplication::translate("AlignModuleClass", "LandMark", Q_NULLPTR));
        ToOrignBtn_3->setText(QApplication::translate("AlignModuleClass", "\354\262\230\354\235\214\354\234\274\353\241\234...", Q_NULLPTR));
        DefaultBtn_2->setText(QApplication::translate("AlignModuleClass", "Default", Q_NULLPTR));
        LandMarkBtn_2->setText(QApplication::translate("AlignModuleClass", "LandMark", Q_NULLPTR));
        ToOrignBtn_2->setText(QApplication::translate("AlignModuleClass", "\354\262\230\354\235\214\354\234\274\353\241\234...", Q_NULLPTR));
        DefaultBtn_1->setText(QApplication::translate("AlignModuleClass", "Default", Q_NULLPTR));
        LandMarkBtn_1->setText(QApplication::translate("AlignModuleClass", "LandMark", Q_NULLPTR));
        ToOrignBtn_1->setText(QApplication::translate("AlignModuleClass", "\354\262\230\354\235\214\354\234\274\353\241\234...", Q_NULLPTR));
        AlignBtn->setText(QApplication::translate("AlignModuleClass", "Align", Q_NULLPTR));
        rsWidget->setTabText(rsWidget->indexOf(widget_3), QApplication::translate("AlignModuleClass", "CAD", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AlignModuleClass: public Ui_AlignModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALIGN_H
