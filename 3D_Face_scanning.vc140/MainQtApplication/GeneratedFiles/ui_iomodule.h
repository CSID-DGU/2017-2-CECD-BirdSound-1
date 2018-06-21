/********************************************************************************
** Form generated from reading UI file 'iomodule.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IOMODULE_H
#define UI_IOMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IOModuleClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *rsWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label;
    QTextBrowser *PathEdit_2d;
    QPushButton *LoadBtn_2d;
    QFrame *Viewer_2d;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *CapSaveBtn_2d;
    QPushButton *SaveBtn_2d;
    QWidget *widget_3;
    QFrame *Viewer_cad_1;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ViewVertex_1;
    QPushButton *ViewWireFrame_1;
    QPushButton *ViewFace_1;
    QPushButton *ViewEdgedFace_1;
    QLabel *label_3;
    QTextBrowser *PathEdit_cad_1;
    QPushButton *LoadBtn_cad_1;
    QSplitter *splitter_3;
    QSplitter *splitter_2;
    QSplitter *splitter_1;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IOModuleClass)
    {
        if (IOModuleClass->objectName().isEmpty())
            IOModuleClass->setObjectName(QStringLiteral("IOModuleClass"));
        IOModuleClass->resize(1387, 883);
        centralWidget = new QWidget(IOModuleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        rsWidget = new QTabWidget(centralWidget);
        rsWidget->setObjectName(QStringLiteral("rsWidget"));
        widget = new QWidget();
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);

        horizontalLayout_11->addWidget(label);

        PathEdit_2d = new QTextBrowser(widget);
        PathEdit_2d->setObjectName(QStringLiteral("PathEdit_2d"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PathEdit_2d->sizePolicy().hasHeightForWidth());
        PathEdit_2d->setSizePolicy(sizePolicy);
        PathEdit_2d->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_11->addWidget(PathEdit_2d);

        LoadBtn_2d = new QPushButton(widget);
        LoadBtn_2d->setObjectName(QStringLiteral("LoadBtn_2d"));
        sizePolicy.setHeightForWidth(LoadBtn_2d->sizePolicy().hasHeightForWidth());
        LoadBtn_2d->setSizePolicy(sizePolicy);

        horizontalLayout_11->addWidget(LoadBtn_2d);

        horizontalLayout_11->setStretch(1, 5);
        horizontalLayout_11->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_11);

        Viewer_2d = new QFrame(widget);
        Viewer_2d->setObjectName(QStringLiteral("Viewer_2d"));
        Viewer_2d->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_2d->setFrameShape(QFrame::StyledPanel);
        Viewer_2d->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(Viewer_2d);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer_6 = new QSpacerItem(368, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_6);

        CapSaveBtn_2d = new QPushButton(widget);
        CapSaveBtn_2d->setObjectName(QStringLiteral("CapSaveBtn_2d"));
        CapSaveBtn_2d->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(CapSaveBtn_2d->sizePolicy().hasHeightForWidth());
        CapSaveBtn_2d->setSizePolicy(sizePolicy1);

        horizontalLayout_12->addWidget(CapSaveBtn_2d);

        SaveBtn_2d = new QPushButton(widget);
        SaveBtn_2d->setObjectName(QStringLiteral("SaveBtn_2d"));
        SaveBtn_2d->setEnabled(false);
        sizePolicy.setHeightForWidth(SaveBtn_2d->sizePolicy().hasHeightForWidth());
        SaveBtn_2d->setSizePolicy(sizePolicy);

        horizontalLayout_12->addWidget(SaveBtn_2d);

        horizontalLayout_12->setStretch(0, 5);
        horizontalLayout_12->setStretch(1, 1);
        horizontalLayout_12->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_12);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 20);
        verticalLayout_2->setStretch(2, 1);
        rsWidget->addTab(widget, QString());
        widget_3 = new QWidget();
        widget_3->setObjectName(QStringLiteral("widget_3"));
        Viewer_cad_1 = new QFrame(widget_3);
        Viewer_cad_1->setObjectName(QStringLiteral("Viewer_cad_1"));
        Viewer_cad_1->setGeometry(QRect(10, 110, 1301, 571));
        Viewer_cad_1->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_1->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_1->setFrameShadow(QFrame::Raised);
        frame = new QFrame(widget_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 40, 531, 61));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ViewVertex_1 = new QPushButton(frame);
        ViewVertex_1->setObjectName(QStringLiteral("ViewVertex_1"));

        horizontalLayout_2->addWidget(ViewVertex_1);

        ViewWireFrame_1 = new QPushButton(frame);
        ViewWireFrame_1->setObjectName(QStringLiteral("ViewWireFrame_1"));

        horizontalLayout_2->addWidget(ViewWireFrame_1);

        ViewFace_1 = new QPushButton(frame);
        ViewFace_1->setObjectName(QStringLiteral("ViewFace_1"));

        horizontalLayout_2->addWidget(ViewFace_1);

        ViewEdgedFace_1 = new QPushButton(frame);
        ViewEdgedFace_1->setObjectName(QStringLiteral("ViewEdgedFace_1"));

        horizontalLayout_2->addWidget(ViewEdgedFace_1);

        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 40, 16));
        QFont font1;
        font1.setPointSize(10);
        label_3->setFont(font1);
        PathEdit_cad_1 = new QTextBrowser(widget_3);
        PathEdit_cad_1->setObjectName(QStringLiteral("PathEdit_cad_1"));
        PathEdit_cad_1->setGeometry(QRect(54, 2, 1161, 31));
        sizePolicy.setHeightForWidth(PathEdit_cad_1->sizePolicy().hasHeightForWidth());
        PathEdit_cad_1->setSizePolicy(sizePolicy);
        PathEdit_cad_1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        LoadBtn_cad_1 = new QPushButton(widget_3);
        LoadBtn_cad_1->setObjectName(QStringLiteral("LoadBtn_cad_1"));
        LoadBtn_cad_1->setGeometry(QRect(1220, 0, 91, 31));
        sizePolicy.setHeightForWidth(LoadBtn_cad_1->sizePolicy().hasHeightForWidth());
        LoadBtn_cad_1->setSizePolicy(sizePolicy);
        LoadBtn_cad_1->setMaximumSize(QSize(136, 16777215));
        splitter_3 = new QSplitter(widget_3);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setGeometry(QRect(980, 660, 431, 41));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter_2 = new QSplitter(widget_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(490, 660, 431, 41));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_1 = new QSplitter(widget_3);
        splitter_1->setObjectName(QStringLiteral("splitter_1"));
        splitter_1->setGeometry(QRect(10, 690, 431, 41));
        splitter_1->setOrientation(Qt::Horizontal);
        rsWidget->addTab(widget_3, QString());

        horizontalLayout->addWidget(rsWidget);

        IOModuleClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IOModuleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1387, 31));
        IOModuleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IOModuleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        IOModuleClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IOModuleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        IOModuleClass->setStatusBar(statusBar);
        QWidget::setTabOrder(LoadBtn_2d, CapSaveBtn_2d);
        QWidget::setTabOrder(CapSaveBtn_2d, SaveBtn_2d);
        QWidget::setTabOrder(SaveBtn_2d, PathEdit_cad_1);
        QWidget::setTabOrder(PathEdit_cad_1, LoadBtn_cad_1);
        QWidget::setTabOrder(LoadBtn_cad_1, ViewVertex_1);
        QWidget::setTabOrder(ViewVertex_1, ViewWireFrame_1);
        QWidget::setTabOrder(ViewWireFrame_1, ViewFace_1);
        QWidget::setTabOrder(ViewFace_1, ViewEdgedFace_1);
        QWidget::setTabOrder(ViewEdgedFace_1, PathEdit_2d);

        retranslateUi(IOModuleClass);

        rsWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(IOModuleClass);
    } // setupUi

    void retranslateUi(QMainWindow *IOModuleClass)
    {
        IOModuleClass->setWindowTitle(QApplication::translate("IOModuleClass", "IOModule", Q_NULLPTR));
        label->setText(QApplication::translate("IOModuleClass", "Path : ", Q_NULLPTR));
        LoadBtn_2d->setText(QApplication::translate("IOModuleClass", "Load", Q_NULLPTR));
        CapSaveBtn_2d->setText(QApplication::translate("IOModuleClass", "Save (Capture)", Q_NULLPTR));
        SaveBtn_2d->setText(QApplication::translate("IOModuleClass", "Save (Origin)", Q_NULLPTR));
        rsWidget->setTabText(rsWidget->indexOf(widget), QApplication::translate("IOModuleClass", "2D", Q_NULLPTR));
        ViewVertex_1->setText(QApplication::translate("IOModuleClass", "Vertex", Q_NULLPTR));
        ViewWireFrame_1->setText(QApplication::translate("IOModuleClass", "WireFrame", Q_NULLPTR));
        ViewFace_1->setText(QApplication::translate("IOModuleClass", "Face", Q_NULLPTR));
        ViewEdgedFace_1->setText(QApplication::translate("IOModuleClass", "EdgedFace", Q_NULLPTR));
        label_3->setText(QApplication::translate("IOModuleClass", "Path : ", Q_NULLPTR));
        LoadBtn_cad_1->setText(QApplication::translate("IOModuleClass", "Load", Q_NULLPTR));
        rsWidget->setTabText(rsWidget->indexOf(widget_3), QApplication::translate("IOModuleClass", "CAD", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IOModuleClass: public Ui_IOModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOMODULE_H
