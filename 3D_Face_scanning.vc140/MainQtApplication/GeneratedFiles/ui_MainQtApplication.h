/********************************************************************************
** Form generated from reading UI file 'MainQtApplication.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINQTAPPLICATION_H
#define UI_MAINQTAPPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainQtApplicationClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainQtApplicationClass)
    {
        if (MainQtApplicationClass->objectName().isEmpty())
            MainQtApplicationClass->setObjectName(QStringLiteral("MainQtApplicationClass"));
        MainQtApplicationClass->resize(600, 400);
        menuBar = new QMenuBar(MainQtApplicationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MainQtApplicationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainQtApplicationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainQtApplicationClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MainQtApplicationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainQtApplicationClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainQtApplicationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainQtApplicationClass->setStatusBar(statusBar);

        retranslateUi(MainQtApplicationClass);

        QMetaObject::connectSlotsByName(MainQtApplicationClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainQtApplicationClass)
    {
        MainQtApplicationClass->setWindowTitle(QApplication::translate("MainQtApplicationClass", "MainQtApplication", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainQtApplicationClass: public Ui_MainQtApplicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINQTAPPLICATION_H
