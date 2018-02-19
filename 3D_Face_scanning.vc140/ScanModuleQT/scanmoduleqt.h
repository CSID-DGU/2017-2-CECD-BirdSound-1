#ifndef SCANMODULEQT_H
#define SCANMODULEQT_H

#include <QtWidgets/QMainWindow>
#include "ui_scanmoduleqt.h"
#include"MeshPreview.h"
#include"ImagePreview.h"
#include"RealSensePreviewer.h"
#include"Scan.h"
class ScanModuleQT : public QMainWindow
{
	Q_OBJECT

public:
	ScanModuleQT(QWidget *parent = 0);
	~ScanModuleQT();


	MeshPreview*							m_MiniMeshPreviewer[3];//left, front, right¼ø¼­
	int										m_IsMiniMeshViewer[3];
	
	
	int										m_ScannedMeshViewer;

	RealSensePreviewer*						m_ImagePreviewer;
	int										m_IsImageViewer;

	void InitializeUi();
public slots:
	void slotCapBtn();
	void slotNextBtn();
	void slotLeftSaveBtn();
	void slotRightSaveBtn();
	void slotFrontSaveBtn();
	void slotStreamingBtn();



	void InitializeVariables();
	void InitializeScene();
	int DestroyVariables();
private:
	Ui::ScanModuleQTClass ui;

	realsense::Device *RealSenseD415;
	Scan *Scanner;
};

#endif // SCANMODULEQT_H
