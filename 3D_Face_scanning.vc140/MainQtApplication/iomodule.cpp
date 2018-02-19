#include "iomodule.h"


IOModule::IOModule(QWidget *parent)
	: QMainWindow(parent)
{
	InitializeVariables();

	InitializeScene();
	InitializeUi();
}

IOModule::~IOModule()
{
	DestroyVariables();
}


void IOModule::InitializeVariables()
{
	
	for (int i = 0; i < 3; i++)
	{
		m_MeshPreviewer[i] = NULL;
		m_IsMeshViewer[i] = 0;
	}
	

	m_IsImageViewer = 0;
	m_ImagePreviewer = NULL;
	for (int i = 0; i < 3; i++)
		m_MeshLandmarkStyle[i] = LandMarkInteractorStyle::New();

	m_IsRelalSensePreviewer = 0;
	m_RelalSensePreviewer = NULL;
}

void IOModule::InitializeScene()
{
	for (int i = 0; i < 3; i++)
	{
		m_MeshPreviewer[i] = new MeshPreview;
		m_MeshPreviewer[i]->Create3DScene();
		m_IsMeshViewer[i] = 1;
	}

	m_RelalSensePreviewer = new RelalSensePreviewer();
	//m_RelalSensePreviewer->Create2DScene();
	m_IsRelalSensePreviewer = 1;

	m_ImagePreviewer = new ImagePreview;
	m_ImagePreviewer->Create2DScene();

	m_IsImageViewer = 1;
}

void IOModule::InitializeUi()
{
	ui.setupUi(this);

	//ADD-HHS
	connect(ui.LoadBtn_2d, SIGNAL(clicked()), this, SLOT(slotLoad2dBtnClicked()));
	connect(ui.LoadBtn_cad_1, SIGNAL(clicked()), this, SLOT(slotLoadcadBtn_1Clicked()));
	connect(ui.LoadBtn_cad_2, SIGNAL(clicked()), this, SLOT(slotLoadcadBtn_2Clicked()));
	connect(ui.LoadBtn_cad_3, SIGNAL(clicked()), this, SLOT(slotLoadcadBtn_3Clicked()));

	connect(ui.SaveBtn_2d, SIGNAL(clicked()), this, SLOT(slotSave2dBtnClicked()));
	connect(ui.CapSaveBtn_2d, SIGNAL(clicked()), this, SLOT(slotCapSave2dBtnClicked()));

	connect(ui.SaveBtn_cad_1, SIGNAL(clicked()), this, SLOT(slotSaveCadBtn_1Clicked()));
	connect(ui.CapSaveBtn_cad_1, SIGNAL(clicked()), this, SLOT(slotCapSaveCadBtn_1Clicked()));

	connect(ui.SaveBtn_cad_2, SIGNAL(clicked()), this, SLOT(slotSaveCadBtn_2Clicked()));
	connect(ui.CapSaveBtn_cad_2, SIGNAL(clicked()), this, SLOT(slotCapSaveCadBtn_2Clicked())); 

	connect(ui.SaveBtn_cad_3, SIGNAL(clicked()), this, SLOT(slotSaveCadBtn_3Clicked()));
	connect(ui.CapSaveBtn_cad_3, SIGNAL(clicked()), this, SLOT(slotCapSaveCadBtn_3Clicked()));
	
	connect(ui.DefaultBtn_1, SIGNAL(clicked()), this, SLOT(slotDefaultBtn_1Clicked()));//to default Interaction
	connect(ui.LandMarkBtn_1, SIGNAL(clicked()), this, SLOT(slotLandMarkBtn_1Clicked()));//land mark select mode
	connect(ui.ToOrignBtn_1, SIGNAL(clicked()), this, SLOT(slotToOrignBtn_1Clicked()));//to Oring mesh

	connect(ui.DefaultBtn_2, SIGNAL(clicked()), this, SLOT(slotDefaultBtn_2Clicked()));//to default Interaction
	connect(ui.LandMarkBtn_2, SIGNAL(clicked()), this, SLOT(slotLandMarkBtn_2Clicked()));//land mark select mode
	connect(ui.ToOrignBtn_2, SIGNAL(clicked()), this, SLOT(slotToOrignBtn_2Clicked()));//to Oring mesh

	connect(ui.DefaultBtn_3, SIGNAL(clicked()), this, SLOT(slotDefaultBtn_3Clicked()));//to default Interaction
	connect(ui.LandMarkBtn_3, SIGNAL(clicked()), this, SLOT(slotLandMarkBtn_3Clicked()));//land mark select mode
	connect(ui.ToOrignBtn_3, SIGNAL(clicked()), this, SLOT(slotToOrignBtn_3Clicked()));//to Oring mesh
	
	//connect(ui.tab, SIGNAL(currentChanged(int)), this, SLOT(slotTabChanged(int)));

	connect(ui.AlignBtn, SIGNAL(clicked()), this, SLOT(slotAlignBtnClicked()));

	connect(ui.ViewVertex_1, SIGNAL(clicked()), this, SLOT(ViewVertex_1()));
	connect(ui.ViewWireFrame_1, SIGNAL(clicked()), this, SLOT(ViewWireFrame_1()));
	connect(ui.ViewFace_1, SIGNAL(clicked()), this, SLOT(ViewFace_1()));
	connect(ui.ViewEdgedFace_1, SIGNAL(clicked()), this, SLOT(ViewEdgedFace_1()));

	connect(ui.ViewVertex_2, SIGNAL(clicked()), this, SLOT(ViewVertex_2()));
	connect(ui.ViewWireFrame_2, SIGNAL(clicked()), this, SLOT(ViewWireFrame_2()));
	connect(ui.ViewFace_2, SIGNAL(clicked()), this, SLOT(ViewFace_2()));
	connect(ui.ViewEdgedFace_2, SIGNAL(clicked()), this, SLOT(ViewEdgedFace_2()));

	connect(ui.ViewVertex_3, SIGNAL(clicked()), this, SLOT(ViewVertex_3()));
	connect(ui.ViewWireFrame_3, SIGNAL(clicked()), this, SLOT(ViewWireFrame_3()));
	connect(ui.ViewFace_3, SIGNAL(clicked()), this, SLOT(ViewFace_3()));
	connect(ui.ViewEdgedFace_3, SIGNAL(clicked()), this, SLOT(ViewEdgedFace_3()));

	
	//connect(ui.CapColBtn, SIGNAL(clicked()), this, SLOT(slotCapColBtnClicked()));
	connect(ui.CapDepBtn, SIGNAL(clicked()), this, SLOT(slotCapDepBtnClicked()));
	//connect(ui.RecordBtn, SIGNAL(clicked()), this, SLOT(slotRecordBtnClicked()));

	int sizeX = 0;	int sizeY = 0;
	sizeX = this->ui.Viewer_cad_1->width();	sizeY = this->ui.Viewer_cad_1->height();
	m_MeshPreviewer[0]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_1->winId()), sizeX, sizeY);
	m_MeshPreviewer[1]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_2->winId()), sizeX, sizeY);
	m_MeshPreviewer[2]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_3->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_2d->width();	sizeY = this->ui.Viewer_2d->height();
	m_ImagePreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_2d->winId()), sizeX, sizeY);
	
	
	sizeX = this->ui.Viewer_cad_RS->width();	sizeY = this->ui.Viewer_cad_RS->height();
	//m_RelalSensePreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_RS->winId()), sizeX, sizeY);
}

void IOModule::resizeEvent(QResizeEvent * event)
{
	m_MeshPreviewer[0]->GetRenderWindow()->SetSize(ui.Viewer_cad_1->width(), ui.Viewer_cad_1->height());
	m_MeshPreviewer[1]->GetRenderWindow()->SetSize(ui.Viewer_cad_2->width(), ui.Viewer_cad_2->height());
	m_MeshPreviewer[2]->GetRenderWindow()->SetSize(ui.Viewer_cad_3->width(), ui.Viewer_cad_3->height());
	m_ImagePreviewer->GetRenderWindow()->SetSize(ui.Viewer_2d->width(), ui.Viewer_2d->height());
}



void IOModule::DestroyVariables()
{
	if (m_IsMeshViewer)
	{
		for (int i = 0; i < 3; i++)
		{
			delete m_MeshPreviewer[0];
			m_MeshPreviewer[0] = NULL;
		}
	}
	if (m_IsImageViewer)
	{
		delete m_ImagePreviewer;
		m_ImagePreviewer = NULL;
	}

	/*
	land mark style 삭제하는 코드도 추가할 것.
	*/
}


void IOModule::slotTabChanged(int idx)
{
	if (idx == 1)//////check here
		m_MeshPreviewer[0]->GetRenderWindow()->SetSize(ui.Viewer_cad_1->width(), ui.Viewer_cad_1->height());
	else//idx == 0)
		m_ImagePreviewer->GetRenderWindow()->SetSize(ui.Viewer_2d->width(), ui.Viewer_2d->height());
}

void IOModule::slotLoad2dBtnClicked()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image (*.png *.jpg *.tif *.bmp)"),
		NULL, QFileDialog::DontUseNativeDialog);

	if (filename.isEmpty())	return;

	int ImgType = this->GetImgType(filename);

	if (ImgType != -1)
		this->Load2DImg(ImgType, filename);
}

/*************************load 3d button*************************/
void IOModule::loadCadBtn(int frameNumber)
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open CAD Data"), "", tr("CAD data(*.stl *.obj *.ply)"),
		NULL, QFileDialog::DontUseNativeDialog);

	if (filename.isEmpty())	return;

	int DataType = this->GetCADType(filename);

	m_MeshLandmarkStyle[frameNumber - 1]->Reset();//
	

	if (DataType != -1)this->LoadCADData(DataType, frameNumber, filename);


	m_MeshLandmarkStyle[frameNumber - 1]->SetDefaultRenderer(m_MeshPreviewer[frameNumber - 1]->GetRenderer());
	m_MeshLandmarkStyle[frameNumber - 1]->setRadis(m_MeshPreviewer[frameNumber - 1]->GetActor());
}

void IOModule::LoadCADData(int type, int frameNum, QString filePath)
{
	if (m_IsMeshViewer[frameNum - 1])
	{
		m_MeshPreviewer[frameNum - 1]->ReleaseModel();
	}
	
	m_MeshPreviewer[frameNum-1]->GetRenderWindow()->SetSize(ui.Viewer_cad_1->width(), ui.Viewer_cad_1->height());
	if (type == CAD_TYPE_OBJ)
	{//obj file -> png texture render
		QString bmpTextureFile = filePath;
		bmpTextureFile.replace("obj", "bmp", Qt::CaseInsensitive);
		QFile file(bmpTextureFile);
		if (file.exists()) m_MeshPreviewer[frameNum]->CreateTexture(bmpTextureFile.toStdString().c_str(), IMG_TYPE_BMP);
	}
	m_MeshPreviewer[frameNum-1]->CreateModel(filePath.toStdString().c_str(), type);

	m_MeshPreviewer[frameNum-1]->Rendering();

	if (frameNum == 1)
	{
		ui.PathEdit_cad_1->setText(filePath);
		ui.SaveBtn_cad_1->setEnabled(true);
		ui.CapSaveBtn_cad_1->setEnabled(true);
	}

	else if (frameNum == 2)
	{
		ui.PathEdit_cad_2->setText(filePath);
		ui.SaveBtn_cad_2->setEnabled(true);
		ui.CapSaveBtn_cad_2->setEnabled(true);
	}

	else if (frameNum == 3)
	{
		ui.PathEdit_cad_3->setText(filePath);
		ui.SaveBtn_cad_3->setEnabled(true);
		ui.CapSaveBtn_cad_3->setEnabled(true);
	}

	else std::cout << "Check the frame Number!!\n";

}

void IOModule::slotLoadcadBtn_1Clicked()
{
	loadCadBtn(1);
}

void IOModule::slotLoadcadBtn_2Clicked()
{
	loadCadBtn(2);
}

void IOModule::slotLoadcadBtn_3Clicked()
{
	loadCadBtn(3);
}

/*
*/

/****************************************************************************************************/
void IOModule::Load2DImg(int type, QString filePath)
{
	if (m_IsImageViewer)
		m_ImagePreviewer->ReleaseModel();

	m_ImagePreviewer->GetRenderWindow()->SetSize(ui.Viewer_2d->width(), ui.Viewer_2d->height());
	m_ImagePreviewer->CreateModel(filePath.toStdString().c_str(), type);
	m_ImagePreviewer->Rendering();

	ui.PathEdit_2d->setText(filePath);
	ui.SaveBtn_2d->setEnabled(true);
	ui.CapSaveBtn_2d->setEnabled(true);
}



void IOModule::slotSave2dBtnClicked()
{
	if (!m_IsImageViewer)
		return;

	QString fileExtension = "*.png";
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "",
		tr("PNG (*.png);; JPG (*.jpg);; TIF (*.tif);; BMP (*.bmp)"), &fileExtension, QFileDialog::DontUseNativeDialog);

	if (fileName.isEmpty()) return;

	int imgType = this->GetImgType(fileExtension);
	QString filepath = fileName + fileExtension.mid(6, 4);
	if (imgType == -1)
		return;
	else
		m_ImagePreviewer->ImageSave(filepath.toStdString().c_str(), imgType);
}

void IOModule::slotCapSave2dBtnClicked()
{
	if (!m_IsImageViewer)
		return;

	QString fileExtension = "*.png";
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Capture Image"), "",
		tr("PNG (*.png);; JPG (*.jpg);; TIF (*.tif);; BMP (*.bmp)"), &fileExtension, QFileDialog::DontUseNativeDialog);

	if (fileName.isEmpty()) return;

	int imgType = this->GetImgType(fileExtension);
	QString filepath = fileName + fileExtension.mid(6, 4);
	if (imgType != -1)
		m_ImagePreviewer->CaptureSave(filepath.toStdString().c_str(), imgType,1);
}
/*************************save 3d button*************************/

void IOModule::saveCadBtn(int frameNumber)
{
	if (!m_IsMeshViewer[frameNumber-1])
		return;

	QString fileExtension = "*.stl";
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "",
		tr("STL (*.stl);; OBJ (*.obj);; PLY (*.ply)"), &fileExtension, QFileDialog::DontUseNativeDialog);

	if (fileName.isEmpty()) return;

	int imgType = this->GetCADType(fileExtension);
	QString filepath = fileName + fileExtension.mid(6, 4);

	if (imgType == -1)
		return;
	else if (imgType == CAD_TYPE_OBJ)
	{
		if (!m_MeshPreviewer[frameNumber - 1]->IsTexture())
		{
			m_MeshPreviewer[frameNumber - 1]->NonTextureMeshSave(fileName.toStdString().c_str(), CAD_TYPE_OBJ);
		}

		QString textureBMP = fileName + ".bmp";//obj file의 texture는 bmp로 저장
		m_MeshPreviewer[frameNumber - 1]->TextureMeshSave(fileName.toStdString().c_str(), CAD_TYPE_OBJ, textureBMP.toStdString().c_str(), IMG_TYPE_BMP);
	}
	else
		m_MeshPreviewer[frameNumber - 1]->MeshSave(filepath.toStdString().c_str(), imgType);
}
void IOModule::slotSaveCadBtn_1Clicked()
{
	saveCadBtn(1);
}
void IOModule::slotSaveCadBtn_2Clicked()
{
	saveCadBtn(2);
}
void IOModule::slotSaveCadBtn_3Clicked()
{
	saveCadBtn(3);
}
/*******************************************************************************************************************************/

void IOModule::CapSavebtn(int frameNumber)
{
	if (!m_IsMeshViewer[frameNumber-1])
		return;

	QString fileExtension = "*.png";
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Mesh Capture Image"), "",
		tr("PNG (*.png);; JPG (*.jpg);; TIF (*.tif);; BMP (*.bmp)"), &fileExtension, QFileDialog::DontUseNativeDialog);

	if (fileName.isEmpty()) return;

	int imgType = this->GetImgType(fileExtension);
	QString filepath = fileName + fileExtension.mid(6, 4);
	if (imgType != -1)
		m_MeshPreviewer[frameNumber - 1]->CaptureSave(filepath.toStdString().c_str(), imgType, 1);
}
void IOModule::slotCapSaveCadBtn_1Clicked()
{
	CapSavebtn(1);
}
void IOModule::slotCapSaveCadBtn_2Clicked()
{
	CapSavebtn(2);
}
void IOModule::slotCapSaveCadBtn_3Clicked()
{
	CapSavebtn(3);
}
/*************************save 3d button*************************/
int IOModule::GetImgType(QString filePath)
{
	if (filePath.contains(".dcm", Qt::CaseInsensitive))
		return IMG_TYPE_DCM;
	else if (filePath.contains(".png", Qt::CaseInsensitive))
		return IMG_TYPE_PNG;
	else if (filePath.contains(".jpg", Qt::CaseInsensitive))
		return IMG_TYPE_JPG;
	else if (filePath.contains(".tif", Qt::CaseInsensitive))
		return IMG_TYPE_TIF;
	else if (filePath.contains(".bmp", Qt::CaseInsensitive))
		return IMG_TYPE_BMP;
	else
		return -1;
}

int IOModule::GetCADType(QString filePath)
{
	if (filePath.contains(".stl", Qt::CaseInsensitive))
		return CAD_TYPE_STL;
	else if (filePath.contains(".obj", Qt::CaseInsensitive))
		return CAD_TYPE_OBJ;
	else if (filePath.contains(".ply", Qt::CaseInsensitive))
		return CAD_TYPE_PLY;
	else
		return -1;
}

/*frame 1*/
void IOModule::ViewVertex_1()
{
	m_MeshPreviewer[0]->ChangeViewMode(0); //0 point 1 wire 2 face 3 edgeface
}
void IOModule::ViewWireFrame_1()
{
	m_MeshPreviewer[0]->ChangeViewMode(1);
}

void IOModule::ViewFace_1()
{
	m_MeshPreviewer[0]->ChangeViewMode(2);
}

void IOModule::ViewEdgedFace_1()
{
	m_MeshPreviewer[0]->ChangeViewMode(3);
}


/*frame 2*/
void IOModule::ViewVertex_2()
{
	m_MeshPreviewer[1]->ChangeViewMode(0); //0 point 1 wire 2 face 3 edgeface
}
void IOModule::ViewWireFrame_2()
{
	m_MeshPreviewer[1]->ChangeViewMode(1);
}

void IOModule::ViewFace_2()
{
	m_MeshPreviewer[1]->ChangeViewMode(2);
}

void IOModule::ViewEdgedFace_2()
{
	m_MeshPreviewer[1]->ChangeViewMode(3);
}

/*frame 3*/
void IOModule::ViewVertex_3()
{
	m_MeshPreviewer[2]->ChangeViewMode(0); //0 point 1 wire 2 face 3 edgeface
}
void IOModule::ViewWireFrame_3()
{
	m_MeshPreviewer[2]->ChangeViewMode(1);
}

void IOModule::ViewFace_3()
{
	m_MeshPreviewer[2]->ChangeViewMode(2);
}

void IOModule::ViewEdgedFace_3()
{
	m_MeshPreviewer[0]->ChangeViewMode(3);
}


void IOModule::DefaultBtn(int frameNumber)
{
	m_MeshPreviewer[frameNumber-1]->GetRenderWindow()->AddRenderer(m_MeshPreviewer[frameNumber - 1]->m_Renderer);
	m_MeshPreviewer[frameNumber - 1]->GetInteractor()->SetInteractorStyle(m_MeshPreviewer[frameNumber - 1]->m_3DStyle);
	m_MeshPreviewer[frameNumber - 1]->GetRenderWindow()->SetInteractor(m_MeshPreviewer[frameNumber - 1]->m_IRen);
}
void IOModule::slotDefaultBtn_1Clicked() 
{
	DefaultBtn(1);
}
void IOModule::slotDefaultBtn_2Clicked()
{
	DefaultBtn(2);
}
void IOModule::slotDefaultBtn_3Clicked()
{
	DefaultBtn(3);
}


/*******************************************LandMark******************************************************************************/
void IOModule::LandMarkBtn(int frameNumber)
{
	m_MeshLandmarkStyle[frameNumber - 1]->initialize();
	m_MeshPreviewer[frameNumber - 1]->setStyle(m_MeshLandmarkStyle[frameNumber - 1]);
}

void IOModule::slotLandMarkBtn_1Clicked()
{
	LandMarkBtn(1);
}
void IOModule::slotLandMarkBtn_2Clicked()
{
	LandMarkBtn(2);
}
void IOModule::slotLandMarkBtn_3Clicked()
{
	LandMarkBtn(3);
}
/******************************************************************************************************************************/

void IOModule::ToOringBtn(int frameNumber)
{
	m_MeshLandmarkStyle[frameNumber-1]->Reset();
	//m_MeshPreviewer[frameNumber - 1]->ChangeToOrgin();
}
void IOModule::slotToOrignBtn_1Clicked()
{
	ToOringBtn(1);
}
void IOModule::slotToOrignBtn_2Clicked()
{
	ToOringBtn(2);
}
void IOModule::slotToOrignBtn_3Clicked()
{
	ToOringBtn(3);
}



void IOModule::slotAlignBtnClicked()
{
	std::vector<double3> left; 
	std::vector<double3> front; 
	std::vector<double3> right;

	if(m_MeshLandmarkStyle[0])
		left = m_MeshLandmarkStyle[0]->getData();

	if (m_MeshLandmarkStyle[1])
		front = m_MeshLandmarkStyle[1]->getData();

	if (m_MeshLandmarkStyle[2])
		right = m_MeshLandmarkStyle[2]->getData();

	for (int i = 0; i < left.size(); i++)
		std::cout << left[i] << "\n";
	std::cout << "\n";

	for (int i = 0; i < front.size(); i++)
		std::cout << front[i] << "\n";
	std::cout << "\n";

	for (int i = 0; i < right.size(); i++)
		std::cout << right[i] << "\n";
}


void IOModule::slotCapColBtnClicked()
{}

void IOModule::slotCapDepBtnClicked()
{}

void IOModule::slotRecordBtnClicked()
{
	//std::cout << "@@";
	//m_RelalSensePreviewer->drawStream();
}