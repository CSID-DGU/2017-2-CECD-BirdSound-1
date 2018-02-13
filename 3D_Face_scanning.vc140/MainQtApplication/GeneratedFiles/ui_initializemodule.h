/********************************************************************************
** Form generated from reading UI file 'initializemodule.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALIZEMODULE_H
#define UI_INITIALIZEMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitializeModule
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *InitializeModule)
    {
        if (InitializeModule->objectName().isEmpty())
            InitializeModule->setObjectName(QStringLiteral("InitializeModule"));
        InitializeModule->setWindowModality(Qt::NonModal);
        InitializeModule->resize(584, 182);
        InitializeModule->setCursor(QCursor(Qt::WaitCursor));
        layoutWidget = new QWidget(InitializeModule);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 130, 561, 40));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(InitializeModule);

        QMetaObject::connectSlotsByName(InitializeModule);
    } // setupUi

    void retranslateUi(QWidget *InitializeModule)
    {
        InitializeModule->setWindowTitle(QApplication::translate("InitializeModule", "BirdSound - 3D Face Scanning", Q_NULLPTR));
        label->setText(QApplication::translate("InitializeModule", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InitializeModule: public Ui_InitializeModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALIZEMODULE_H
