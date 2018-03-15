#ifndef IOMODULE_H
#define IOMODULE_H
#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
//#include <LandMarkInteractorStyle.h>


#include "ui_iomodule.h"
#include "MeshPreview.h"
#include "ImagePreview.h"
//#include"RealSensePreviewer.h"
#include"../DepthModule/device.h"

#include<string>

#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
//VTK_MODULE_INIT(vtkInteractionStyle);


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

	MeshPreview*						m_MeshPreviewer;//left, front, right¼ø¼­
	int									m_IsMeshViewer;

	ImagePreview*						m_ImagePreviewer;
	int									m_IsImageViewer;

	void InitializeVariables();
	void InitializeScene();
	void InitializeUi();
	void DestroyVariables();

	//ADD-HHS
	void resizeEvent(QResizeEvent * event);
	//load
	void Load2DImg(int type, QString filePath);
	void LoadCADData(int type,QString filePath);
	//reference
	int GetImgType(QString filePath);
	int GetCADType(QString filePath);

public slots:
	//ADD-HHS
	void slotTabChanged(int idx);

	//view opt
	void ViewVertex_1();
	void ViewWireFrame_1();
	void ViewFace_1();
	void ViewEdgedFace_1();

	void slotCapSave2dBtnClicked();
	void slotSave2dBtnClicked();
	void slotLoad2dBtnClicked();
	void loadCadBtn();

private:

	void saveCadBtn();
	void CapSavebtn();
	Ui::IOModuleClass ui;
};

#endif // IOMODULE_H



