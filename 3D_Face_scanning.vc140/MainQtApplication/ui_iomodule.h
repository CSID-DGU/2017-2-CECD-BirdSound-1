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
    QTabWidget *tabWidget;
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
    QFrame *Viewer_cad_2;
    QFrame *Viewer_cad_3;
    QPushButton *LoadBtn_cad_2;
    QTextBrowser *PathEdit_cad_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *ViewVertex_2;
    QPushButton *ViewWireFrame_2;
    QPushButton *ViewFace_2;
    QPushButton *ViewEdgedFace_2;
    QLabel *label_4;
    QPushButton *LoadBtn_cad_3;
    QTextBrowser *PathEdit_cad_3;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *ViewVertex_3;
    QPushButton *ViewWireFrame_3;
    QPushButton *ViewFace_3;
    QPushButton *ViewEdgedFace_3;
    QLabel *label_5;
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
    QPushButton *DefaultBtn_3;
    QPushButton *LandMarkBtn_3;
    QPushButton *ToOrignBtn_3;
    QPushButton *CapSaveBtn_cad_3;
    QPushButton *SaveBtn_cad_3;
    QSplitter *splitter_2;
    QPushButton *DefaultBtn_2;
    QPushButton *LandMarkBtn_2;
    QPushButton *ToOrignBtn_2;
    QPushButton *CapSaveBtn_cad_2;
    QPushButton *SaveBtn_cad_2;
    QSplitter *splitter_1;
    QPushButton *DefaultBtn_1;
    QPushButton *LandMarkBtn_1;
    QPushButton *ToOrignBtn_1;
    QPushButton *CapSaveBtn_cad_1;
    QPushButton *SaveBtn_cad_1;
    QPushButton *AlignBtn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IOModuleClass)
    {
        if (IOModuleClass->objectName().isEmpty())
            IOModuleClass->setObjectName(QStringLiteral("IOModuleClass"));
        IOModuleClass->resize(1448, 843);
        centralWidget = new QWidget(IOModuleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
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
        tabWidget->addTab(widget, QString());
        widget_3 = new QWidget();
        widget_3->setObjectName(QStringLiteral("widget_3"));
        Viewer_cad_1 = new QFrame(widget_3);
        Viewer_cad_1->setObjectName(QStringLiteral("Viewer_cad_1"));
        Viewer_cad_1->setGeometry(QRect(10, 80, 431, 571));
        Viewer_cad_1->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_1->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_1->setFrameShadow(QFrame::Raised);
        Viewer_cad_2 = new QFrame(widget_3);
        Viewer_cad_2->setObjectName(QStringLiteral("Viewer_cad_2"));
        Viewer_cad_2->setGeometry(QRect(490, 80, 431, 571));
        Viewer_cad_2->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_2->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_2->setFrameShadow(QFrame::Raised);
        Viewer_cad_3 = new QFrame(widget_3);
        Viewer_cad_3->setObjectName(QStringLiteral("Viewer_cad_3"));
        Viewer_cad_3->setGeometry(QRect(980, 80, 431, 571));
        Viewer_cad_3->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        Viewer_cad_3->setFrameShape(QFrame::StyledPanel);
        Viewer_cad_3->setFrameShadow(QFrame::Raised);
        LoadBtn_cad_2 = new QPushButton(widget_3);
        LoadBtn_cad_2->setObjectName(QStringLiteral("LoadBtn_cad_2"));
        LoadBtn_cad_2->setGeometry(QRect(858, 8, 61, 31));
        sizePolicy.setHeightForWidth(LoadBtn_cad_2->sizePolicy().hasHeightForWidth());
        LoadBtn_cad_2->setSizePolicy(sizePolicy);
        LoadBtn_cad_2->setMaximumSize(QSize(136, 16777215));
        PathEdit_cad_2 = new QTextBrowser(widget_3);
        PathEdit_cad_2->setObjectName(QStringLiteral("PathEdit_cad_2"));
        PathEdit_cad_2->setGeometry(QRect(532, 10, 321, 21));
        sizePolicy.setHeightForWidth(PathEdit_cad_2->sizePolicy().hasHeightForWidth());
        PathEdit_cad_2->setSizePolicy(sizePolicy);
        PathEdit_cad_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        frame_2 = new QFrame(widget_3);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(488, 38, 431, 41));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Plain);
        horizontalLayout_7 = new QHBoxLayout(frame_2);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        ViewVertex_2 = new QPushButton(frame_2);
        ViewVertex_2->setObjectName(QStringLiteral("ViewVertex_2"));

        horizontalLayout_7->addWidget(ViewVertex_2);

        ViewWireFrame_2 = new QPushButton(frame_2);
        ViewWireFrame_2->setObjectName(QStringLiteral("ViewWireFrame_2"));

        horizontalLayout_7->addWidget(ViewWireFrame_2);

        ViewFace_2 = new QPushButton(frame_2);
        ViewFace_2->setObjectName(QStringLiteral("ViewFace_2"));

        horizontalLayout_7->addWidget(ViewFace_2);

        ViewEdgedFace_2 = new QPushButton(frame_2);
        ViewEdgedFace_2->setObjectName(QStringLiteral("ViewEdgedFace_2"));

        horizontalLayout_7->addWidget(ViewEdgedFace_2);

        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(490, 10, 40, 16));
        QFont font1;
        font1.setPointSize(10);
        label_4->setFont(font1);
        LoadBtn_cad_3 = new QPushButton(widget_3);
        LoadBtn_cad_3->setObjectName(QStringLiteral("LoadBtn_cad_3"));
        LoadBtn_cad_3->setGeometry(QRect(1348, 8, 61, 31));
        sizePolicy.setHeightForWidth(LoadBtn_cad_3->sizePolicy().hasHeightForWidth());
        LoadBtn_cad_3->setSizePolicy(sizePolicy);
        LoadBtn_cad_3->setMaximumSize(QSize(136, 16777215));
        PathEdit_cad_3 = new QTextBrowser(widget_3);
        PathEdit_cad_3->setObjectName(QStringLiteral("PathEdit_cad_3"));
        PathEdit_cad_3->setGeometry(QRect(1022, 10, 321, 21));
        sizePolicy.setHeightForWidth(PathEdit_cad_3->sizePolicy().hasHeightForWidth());
        PathEdit_cad_3->setSizePolicy(sizePolicy);
        PathEdit_cad_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        frame_3 = new QFrame(widget_3);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(978, 38, 431, 41));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Plain);
        horizontalLayout_8 = new QHBoxLayout(frame_3);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        ViewVertex_3 = new QPushButton(frame_3);
        ViewVertex_3->setObjectName(QStringLiteral("ViewVertex_3"));

        horizontalLayout_8->addWidget(ViewVertex_3);

        ViewWireFrame_3 = new QPushButton(frame_3);
        ViewWireFrame_3->setObjectName(QStringLiteral("ViewWireFrame_3"));

        horizontalLayout_8->addWidget(ViewWireFrame_3);

        ViewFace_3 = new QPushButton(frame_3);
        ViewFace_3->setObjectName(QStringLiteral("ViewFace_3"));

        horizontalLayout_8->addWidget(ViewFace_3);

        ViewEdgedFace_3 = new QPushButton(frame_3);
        ViewEdgedFace_3->setObjectName(QStringLiteral("ViewEdgedFace_3"));

        horizontalLayout_8->addWidget(ViewEdgedFace_3);

        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(980, 10, 40, 16));
        label_5->setFont(font1);
        frame = new QFrame(widget_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 30, 431, 41));
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
        label_3->setGeometry(QRect(12, 2, 40, 16));
        label_3->setFont(font1);
        PathEdit_cad_1 = new QTextBrowser(widget_3);
        PathEdit_cad_1->setObjectName(QStringLiteral("PathEdit_cad_1"));
        PathEdit_cad_1->setGeometry(QRect(54, 2, 321, 21));
        sizePolicy.setHeightForWidth(PathEdit_cad_1->sizePolicy().hasHeightForWidth());
        PathEdit_cad_1->setSizePolicy(sizePolicy);
        PathEdit_cad_1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        LoadBtn_cad_1 = new QPushButton(widget_3);
        LoadBtn_cad_1->setObjectName(QStringLiteral("LoadBtn_cad_1"));
        LoadBtn_cad_1->setGeometry(QRect(380, 0, 61, 31));
        sizePolicy.setHeightForWidth(LoadBtn_cad_1->sizePolicy().hasHeightForWidth());
        LoadBtn_cad_1->setSizePolicy(sizePolicy);
        LoadBtn_cad_1->setMaximumSize(QSize(136, 16777215));
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
        CapSaveBtn_cad_3 = new QPushButton(splitter_3);
        CapSaveBtn_cad_3->setObjectName(QStringLiteral("CapSaveBtn_cad_3"));
        CapSaveBtn_cad_3->setEnabled(false);
        sizePolicy1.setHeightForWidth(CapSaveBtn_cad_3->sizePolicy().hasHeightForWidth());
        CapSaveBtn_cad_3->setSizePolicy(sizePolicy1);
        splitter_3->addWidget(CapSaveBtn_cad_3);
        SaveBtn_cad_3 = new QPushButton(splitter_3);
        SaveBtn_cad_3->setObjectName(QStringLiteral("SaveBtn_cad_3"));
        SaveBtn_cad_3->setEnabled(false);
        sizePolicy.setHeightForWidth(SaveBtn_cad_3->sizePolicy().hasHeightForWidth());
        SaveBtn_cad_3->setSizePolicy(sizePolicy);
        splitter_3->addWidget(SaveBtn_cad_3);
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
        CapSaveBtn_cad_2 = new QPushButton(splitter_2);
        CapSaveBtn_cad_2->setObjectName(QStringLiteral("CapSaveBtn_cad_2"));
        CapSaveBtn_cad_2->setEnabled(false);
        sizePolicy1.setHeightForWidth(CapSaveBtn_cad_2->sizePolicy().hasHeightForWidth());
        CapSaveBtn_cad_2->setSizePolicy(sizePolicy1);
        splitter_2->addWidget(CapSaveBtn_cad_2);
        SaveBtn_cad_2 = new QPushButton(splitter_2);
        SaveBtn_cad_2->setObjectName(QStringLiteral("SaveBtn_cad_2"));
        SaveBtn_cad_2->setEnabled(false);
        sizePolicy.setHeightForWidth(SaveBtn_cad_2->sizePolicy().hasHeightForWidth());
        SaveBtn_cad_2->setSizePolicy(sizePolicy);
        splitter_2->addWidget(SaveBtn_cad_2);
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
        CapSaveBtn_cad_1 = new QPushButton(splitter_1);
        CapSaveBtn_cad_1->setObjectName(QStringLiteral("CapSaveBtn_cad_1"));
        CapSaveBtn_cad_1->setEnabled(false);
        sizePolicy1.setHeightForWidth(CapSaveBtn_cad_1->sizePolicy().hasHeightForWidth());
        CapSaveBtn_cad_1->setSizePolicy(sizePolicy1);
        splitter_1->addWidget(CapSaveBtn_cad_1);
        SaveBtn_cad_1 = new QPushButton(splitter_1);
        SaveBtn_cad_1->setObjectName(QStringLiteral("SaveBtn_cad_1"));
        SaveBtn_cad_1->setEnabled(false);
        sizePolicy.setHeightForWidth(SaveBtn_cad_1->sizePolicy().hasHeightForWidth());
        SaveBtn_cad_1->setSizePolicy(sizePolicy);
        splitter_1->addWidget(SaveBtn_cad_1);
        AlignBtn = new QPushButton(widget_3);
        AlignBtn->setObjectName(QStringLiteral("AlignBtn"));
        AlignBtn->setGeometry(QRect(490, 710, 101, 31));
        tabWidget->addTab(widget_3, QString());

        horizontalLayout->addWidget(tabWidget);

        IOModuleClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IOModuleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1448, 21));
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
        QWidget::setTabOrder(ViewEdgedFace_1, CapSaveBtn_cad_1);
        QWidget::setTabOrder(CapSaveBtn_cad_1, SaveBtn_cad_1);
        QWidget::setTabOrder(SaveBtn_cad_1, PathEdit_2d);

        retranslateUi(IOModuleClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(IOModuleClass);
    } // setupUi

    void retranslateUi(QMainWindow *IOModuleClass)
    {
        IOModuleClass->setWindowTitle(QApplication::translate("IOModuleClass", "IOModule", Q_NULLPTR));
        label->setText(QApplication::translate("IOModuleClass", "Path : ", Q_NULLPTR));
        LoadBtn_2d->setText(QApplication::translate("IOModuleClass", "Load", Q_NULLPTR));
        CapSaveBtn_2d->setText(QApplication::translate("IOModuleClass", "Save (Capture)", Q_NULLPTR));
        SaveBtn_2d->setText(QApplication::translate("IOModuleClass", "Save (Origin)", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("IOModuleClass", "2D", Q_NULLPTR));
        LoadBtn_cad_2->setText(QApplication::translate("IOModuleClass", "Load", Q_NULLPTR));
        ViewVertex_2->setText(QApplication::translate("IOModuleClass", "Vertex", Q_NULLPTR));
        ViewWireFrame_2->setText(QApplication::translate("IOModuleClass", "WireFrame", Q_NULLPTR));
        ViewFace_2->setText(QApplication::translate("IOModuleClass", "Face", Q_NULLPTR));
        ViewEdgedFace_2->setText(QApplication::translate("IOModuleClass", "EdgedFace", Q_NULLPTR));
        label_4->setText(QApplication::translate("IOModuleClass", "Path : ", Q_NULLPTR));
        LoadBtn_cad_3->setText(QApplication::translate("IOModuleClass", "Load", Q_NULLPTR));
        ViewVertex_3->setText(QApplication::translate("IOModuleClass", "Vertex", Q_NULLPTR));
        ViewWireFrame_3->setText(QApplication::translate("IOModuleClass", "WireFrame", Q_NULLPTR));
        ViewFace_3->setText(QApplication::translate("IOModuleClass", "Face", Q_NULLPTR));
        ViewEdgedFace_3->setText(QApplication::translate("IOModuleClass", "EdgedFace", Q_NULLPTR));
        label_5->setText(QApplication::translate("IOModuleClass", "Path : ", Q_NULLPTR));
        ViewVertex_1->setText(QApplication::translate("IOModuleClass", "Vertex", Q_NULLPTR));
        ViewWireFrame_1->setText(QApplication::translate("IOModuleClass", "WireFrame", Q_NULLPTR));
        ViewFace_1->setText(QApplication::translate("IOModuleClass", "Face", Q_NULLPTR));
        ViewEdgedFace_1->setText(QApplication::translate("IOModuleClass", "EdgedFace", Q_NULLPTR));
        label_3->setText(QApplication::translate("IOModuleClass", "Path : ", Q_NULLPTR));
        LoadBtn_cad_1->setText(QApplication::translate("IOModuleClass", "Load", Q_NULLPTR));
        DefaultBtn_3->setText(QApplication::translate("IOModuleClass", "Default", Q_NULLPTR));
        LandMarkBtn_3->setText(QApplication::translate("IOModuleClass", "LandMark", Q_NULLPTR));
        ToOrignBtn_3->setText(QApplication::translate("IOModuleClass", "\354\262\230\354\235\214\354\234\274\353\241\234...", Q_NULLPTR));
        CapSaveBtn_cad_3->setText(QApplication::translate("IOModuleClass", "Save (Capture)", Q_NULLPTR));
        SaveBtn_cad_3->setText(QApplication::translate("IOModuleClass", "Save (Origin)", Q_NULLPTR));
        DefaultBtn_2->setText(QApplication::translate("IOModuleClass", "Default", Q_NULLPTR));
        LandMarkBtn_2->setText(QApplication::translate("IOModuleClass", "LandMark", Q_NULLPTR));
        ToOrignBtn_2->setText(QApplication::translate("IOModuleClass", "\354\262\230\354\235\214\354\234\274\353\241\234...", Q_NULLPTR));
        CapSaveBtn_cad_2->setText(QApplication::translate("IOModuleClass", "Save (Capture)", Q_NULLPTR));
        SaveBtn_cad_2->setText(QApplication::translate("IOModuleClass", "Save (Origin)", Q_NULLPTR));
        DefaultBtn_1->setText(QApplication::translate("IOModuleClass", "Default", Q_NULLPTR));
        LandMarkBtn_1->setText(QApplication::translate("IOModuleClass", "LandMark", Q_NULLPTR));
        ToOrignBtn_1->setText(QApplication::translate("IOModuleClass", "\354\262\230\354\235\214\354\234\274\353\241\234...", Q_NULLPTR));
        CapSaveBtn_cad_1->setText(QApplication::translate("IOModuleClass", "Save (Capture)", Q_NULLPTR));
        SaveBtn_cad_1->setText(QApplication::translate("IOModuleClass", "Save (Origin)", Q_NULLPTR));
        AlignBtn->setText(QApplication::translate("IOModuleClass", "Align", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(widget_3), QApplication::translate("IOModuleClass", "CAD", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IOModuleClass: public Ui_IOModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOMODULE_H
