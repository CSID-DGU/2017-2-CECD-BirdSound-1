#ifndef SCANMODULEQT_H
#define SCANMODULEQT_H

#include <QtWidgets/QMainWindow>
#include "ui_scanmoduleqt.h"
#include"MeshPreview.h"
#include"ImagePreview.h"
//#include"RealSensePreviewer.h"
#include"Scan.h"
#include"MeshIO.h"
#include"AlignModule.h"
class ScanModule : public QMainWindow
{
	Q_OBJECT

public:
	ScanModule(QWidget *parent = 0);
	~ScanModule();


	MeshPreview*							m_MiniMeshPreviewer[3];//left, front, right¼ø¼­
	int										m_IsMiniMeshViewer[3];
	
	MeshPreview*							m_ScannedMeshViewer;
	int										m_IsScannedMeshViewer;

	//RealSensePreviewer*						m_ImagePreviewer;
	//int										m_IsImageViewer;

	void InitializeUi();
public slots:
	void slotCapBtn();
	void slotNextBtn();
	void slotLeftSaveBtn();
	void slotRightSaveBtn();
	void slotFrontSaveBtn();
	void slotStreamingBtn();
	void slotCapPicBtn();


	void InitializeVariables();
	void InitializeScene();
	int DestroyVariables();
private:
	int index=0;
	Ui::ScanModuleQTClass ui;

	realsense::Device *RealSenseD415;
	Scan *Scanner;
};

#endif // SCANMODULEQT_H
