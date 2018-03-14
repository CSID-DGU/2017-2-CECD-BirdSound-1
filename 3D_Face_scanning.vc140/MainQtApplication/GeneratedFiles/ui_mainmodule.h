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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainModule
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *RecentTable;
    QWidget *widget_1;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *runScanModule;
    QPushButton *runViewerModule;
    QPushButton *runCalibrationModule;
    QPushButton *runExpModule;
    QWidget *MainImg;

    void setupUi(QWidget *MainModule)
    {
        if (MainModule->objectName().isEmpty())
            MainModule->setObjectName(QStringLiteral("MainModule"));
        MainModule->resize(885, 530);
        MainModule->setStyleSheet(QString::fromUtf8("#MainImg{\n"
"background-image:url(\"GENORAY_small.jpg\");\n"
"background-repeat:no-repeat;\n"
"background-position:center;\n"
"}\n"
"QWidget{\n"
"background: \"#F4F4F4\";\n"
"}\n"
"QTableWidget{\n"
"background: \"white\";\n"
"}\n"
"QPushButton {\n"
"font: 12pt \"\353\247\221\354\235\200\352\263\240\353\224\225\";\n"
"background: \"#F4F4F4\";\n"
"border : 0px\n"
"}\n"
"QPushButton:hover{\n"
"color: \"#F00000\";\n"
"}"));
        layoutWidget = new QWidget(MainModule);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 881, 531));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        RecentTable = new QTableWidget(layoutWidget);
        if (RecentTable->columnCount() < 5)
            RecentTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        RecentTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        RecentTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        RecentTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        RecentTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        RecentTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        RecentTable->setObjectName(QStringLiteral("RecentTable"));
        RecentTable->setStyleSheet(QStringLiteral("background : white;"));

        horizontalLayout->addWidget(RecentTable);

        widget_1 = new QWidget(layoutWidget);
        widget_1->setObjectName(QStringLiteral("widget_1"));
        widget_1->setMinimumSize(QSize(350, 0));
        layoutWidget1 = new QWidget(widget_1);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 200, 331, 161));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        runScanModule = new QPushButton(layoutWidget1);
        runScanModule->setObjectName(QStringLiteral("runScanModule"));
        runScanModule->setAutoFillBackground(false);
        runScanModule->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(runScanModule);

        runViewerModule = new QPushButton(layoutWidget1);
        runViewerModule->setObjectName(QStringLiteral("runViewerModule"));

        verticalLayout->addWidget(runViewerModule);

        runCalibrationModule = new QPushButton(layoutWidget1);
        runCalibrationModule->setObjectName(QStringLiteral("runCalibrationModule"));

        verticalLayout->addWidget(runCalibrationModule);

        runExpModule = new QPushButton(layoutWidget1);
        runExpModule->setObjectName(QStringLiteral("runExpModule"));

        verticalLayout->addWidget(runExpModule);

        MainImg = new QWidget(widget_1);
        MainImg->setObjectName(QStringLiteral("MainImg"));
        MainImg->setGeometry(QRect(10, 10, 331, 161));

        horizontalLayout->addWidget(widget_1);


        retranslateUi(MainModule);

        QMetaObject::connectSlotsByName(MainModule);
    } // setupUi

    void retranslateUi(QWidget *MainModule)
    {
        MainModule->setWindowTitle(QApplication::translate("MainModule", "Form", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = RecentTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainModule", "\354\235\264\353\246\204", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = RecentTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainModule", "\354\264\254\354\230\201\353\202\240\354\247\234", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = RecentTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainModule", "\355\214\214\354\235\274\355\201\254\352\270\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = RecentTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainModule", "\355\214\214\354\235\274\354\234\204\354\271\230", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = RecentTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainModule", "\355\231\230\354\236\220 ID", Q_NULLPTR));
        runScanModule->setText(QApplication::translate("MainModule", "Start a new Face Scan", Q_NULLPTR));
        runViewerModule->setText(QApplication::translate("MainModule", "Open an existing Face Scan", Q_NULLPTR));
        runCalibrationModule->setText(QApplication::translate("MainModule", "Camera calibration", Q_NULLPTR));
        runExpModule->setText(QApplication::translate("MainModule", "Data Validation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainModule: public Ui_MainModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMODULE_H
