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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanModule
{
public:

    void setupUi(QWidget *ScanModule)
    {
        if (ScanModule->objectName().isEmpty())
            ScanModule->setObjectName(QStringLiteral("ScanModule"));
        ScanModule->resize(400, 300);

        retranslateUi(ScanModule);

        QMetaObject::connectSlotsByName(ScanModule);
    } // setupUi

    void retranslateUi(QWidget *ScanModule)
    {
        ScanModule->setWindowTitle(QApplication::translate("ScanModule", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScanModule: public Ui_ScanModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANMODULE_H
