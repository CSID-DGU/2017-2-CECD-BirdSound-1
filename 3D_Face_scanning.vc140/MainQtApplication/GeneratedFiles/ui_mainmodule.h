/********************************************************************************
** Form generated from reading UI file 'mainmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMODULE_H
#define UI_MAINMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainModule
{
public:
    QTableWidget *tableWidget;
    QPushButton *runScanModule;
    QPushButton *runViewerModule;
    QPushButton *runCalibrationModule;
    QPushButton *runExpModule;
    QLabel *label;

    void setupUi(QWidget *MainModule)
    {
        if (MainModule->objectName().isEmpty())
            MainModule->setObjectName(QStringLiteral("MainModule"));
        MainModule->resize(901, 777);
        tableWidget = new QTableWidget(MainModule);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 90, 721, 661));
        runScanModule = new QPushButton(MainModule);
        runScanModule->setObjectName(QStringLiteral("runScanModule"));
        runScanModule->setGeometry(QRect(750, 90, 141, 101));
        runViewerModule = new QPushButton(MainModule);
        runViewerModule->setObjectName(QStringLiteral("runViewerModule"));
        runViewerModule->setGeometry(QRect(750, 200, 141, 101));
        runCalibrationModule = new QPushButton(MainModule);
        runCalibrationModule->setObjectName(QStringLiteral("runCalibrationModule"));
        runCalibrationModule->setGeometry(QRect(750, 310, 141, 101));
        runExpModule = new QPushButton(MainModule);
        runExpModule->setObjectName(QStringLiteral("runExpModule"));
        runExpModule->setGeometry(QRect(750, 420, 141, 101));
        label = new QLabel(MainModule);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 62, 721, 20));

        retranslateUi(MainModule);

        QMetaObject::connectSlotsByName(MainModule);
    } // setupUi

    void retranslateUi(QWidget *MainModule)
    {
        MainModule->setWindowTitle(QApplication::translate("MainModule", "Form", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainModule", "\354\235\264\353\246\204", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainModule", "\354\264\254\354\230\201\353\202\240\354\247\234", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainModule", "\355\214\214\354\235\274\355\201\254\352\270\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainModule", "\355\214\214\354\235\274\354\234\204\354\271\230", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainModule", "\355\231\230\354\236\220 ID", Q_NULLPTR));
        runScanModule->setText(QApplication::translate("MainModule", "\354\203\210\353\241\234 \354\212\244\354\272\224\355\225\230\352\270\260", Q_NULLPTR));
        runViewerModule->setText(QApplication::translate("MainModule", "\354\235\264\354\240\204\354\212\244\354\272\224 \353\266\210\353\237\254\354\230\244\352\270\260", Q_NULLPTR));
        runCalibrationModule->setText(QApplication::translate("MainModule", "\354\271\264\353\251\224\353\235\274 \354\272\230\353\246\254\353\270\214\353\240\210\354\235\264\354\205\230", Q_NULLPTR));
        runExpModule->setText(QApplication::translate("MainModule", "\353\215\260\354\235\264\355\204\260 \352\262\200\354\246\235\354\213\244\355\227\230", Q_NULLPTR));
        label->setText(QApplication::translate("MainModule", "\354\235\264\354\240\204 \354\212\244\354\272\224 \353\252\251\353\241\235", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainModule: public Ui_MainModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMODULE_H
