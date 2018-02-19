#ifndef IOMODULE_H
#define IOMODULE_H
#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <LandMarkInteractorStyle.h>


#include "ui_iomodule.h"
#include "MeshPreview.h"
#include "ImagePreview.h"
#include"RealSensePreviewer.h"
#include"../DepthModule/device.h"

#include<string>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

#define IMG_TYPE_BMP	0
#define IMG_TYPE_JPG	1
#define IMG_TYPE_PNG	2
#define IMG_TYPE_TIF	3
#define IMG_TYPE_DCM	4

#define CAD_TYPE_STL	0
#define CAD_TYPE_PLY	1
#define CAD_TYPE_OBJ	2

class IOModule : public QMainWindow
{
	Q_OBJECT

public:
	IOModule(QWidget *parent = 0);
	~IOModule();

	MeshPreview*							m_MeshPreviewer[3];//left, front, right순서


	int										m_IsMeshViewer[3];
	LandMarkInteractorStyle*				m_MeshLandmarkStyle[3];//left, front, right순서


	ImagePreview*	m_ImagePreviewer;
	int				m_IsImageViewer;

	RealSensePreviewer*						m_RelalSensePreviewer;
	int										m_IsRelalSensePreviewer;
	void InitializeVariables();
	void InitializeScene();
	void InitializeUi();
	void DestroyVariables();

	//ADD-HHS
	void resizeEvent(QResizeEvent * event);
	//load
	void Load2DImg(int type, QString filePath);
	void LoadCADData(int type, int frameNum, QString filePath);
	//reference
	int GetImgType(QString filePath);
	int GetCADType(QString filePath);

public slots:
	//ADD-HHS
	void slotTabChanged(int idx);
	
	
	//2d slot
	void slotLoad2dBtnClicked();
	void slotSave2dBtnClicked();
	void slotCapSave2dBtnClicked();
	
	//3d slot
	void slotSaveCadBtn_1Clicked();
	void slotLoadcadBtn_1Clicked();
	void slotCapSaveCadBtn_1Clicked();


	void slotSaveCadBtn_2Clicked();
	void slotLoadcadBtn_2Clicked();
	void slotCapSaveCadBtn_2Clicked();

	void slotSaveCadBtn_3Clicked();
	void slotLoadcadBtn_3Clicked();
	void slotCapSaveCadBtn_3Clicked();

	//view opt
	void ViewVertex_1();
	void ViewWireFrame_1();
	void ViewFace_1();
	void ViewEdgedFace_1();

	void ViewVertex_2();
	void ViewWireFrame_2();
	void ViewFace_2();
	void ViewEdgedFace_2();

	void ViewVertex_3();
	void ViewWireFrame_3();
	void ViewFace_3();
	void ViewEdgedFace_3();

	//edit slot
	void slotDefaultBtn_1Clicked(); 
	void slotLandMarkBtn_1Clicked();
	void slotToOrignBtn_1Clicked();

	void slotDefaultBtn_2Clicked();
	void slotLandMarkBtn_2Clicked();
	void slotToOrignBtn_2Clicked();

	void slotDefaultBtn_3Clicked();
	void slotLandMarkBtn_3Clicked();
	void slotToOrignBtn_3Clicked();

	
	void slotAlignBtnClicked();


	//rs slot
	void slotCapColBtnClicked();
	void slotCapDepBtnClicked();
	void slotRecordBtnClicked();
	
private:
	void loadCadBtn(int frameNumber);
	void saveCadBtn(int frameNumber);
	void CapSavebtn(int frameNUmber);
	void DefaultBtn(int frameNumber);
	void LandMarkBtn(int frameNumber);
	void ToOringBtn(int frameNumber);
	Ui::IOModuleClass ui;
};

#endif // IOMODULE_H



