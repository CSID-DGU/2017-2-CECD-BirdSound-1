#include "iomodule.h"
#include"AlignModule.h"

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
		m_MeshPreviewer = NULL;
		m_IsMeshViewer = 0;
	}
	

	m_IsImageViewer = 0;
	m_ImagePreviewer = NULL;
	/*for (int i = 0; i < 3; i++)
		m_MeshLandmarkStyle[i] = LandMarkInteractorStyle::New();*/
}

void IOModule::InitializeScene()
{
	for (int i = 0; i < 3; i++)
	{
		m_MeshPreviewer = new MeshPreview;
		m_MeshPreviewer->Create3DScene();
		m_IsMeshViewer = 1;
	}

	m_ImagePreviewer = new ImagePreview;
	m_ImagePreviewer->Create2DScene();
	m_IsImageViewer = 1;
}

void IOModule::InitializeUi()
{
	ui.setupUi(this);

	//ADD-HHS
	connect(ui.LoadBtn_2d, SIGNAL(clicked()), this, SLOT(slotLoad2dBtnClicked()));
	connect(ui.LoadBtn_cad_1, SIGNAL(clicked()), this, SLOT(loadCadBtn()));
	//connect(ui.LoadBtn_cad_2, SIGNAL(clicked()), this, SLOT(slotLoadcadBtn_2Clicked()));
	//connect(ui.LoadBtn_cad_3, SIGNAL(clicked()), this, SLOT(slotLoadcadBtn_3Clicked()));

	//connect(ui.SaveBtn_2d, SIGNAL(clicked()), this, SLOT(slotSave2dBtnClicked()));
	//connect(ui.CapSaveBtn_2d, SIGNAL(clicked()), this, SLOT(slotCapSave2dBtnClicked()));

	//connect(ui.SaveBtn_cad_1, SIGNAL(clicked()), this, SLOT(slotSaveCadBtn_1Clicked()));
	//connect(ui.CapSaveBtn_cad_1, SIGNAL(clicked()), this, SLOT(slotCapSaveCadBtn_1Clicked()));

	//connect(ui.SaveBtn_cad_2, SIGNAL(clicked()), this, SLOT(slotSaveCadBtn_2Clicked()));
	//connect(ui.CapSaveBtn_cad_2, SIGNAL(clicked()), this, SLOT(slotCapSaveCadBtn_2Clicked())); 

	//connect(ui.SaveBtn_cad_3, SIGNAL(clicked()), this, SLOT(slotSaveCadBtn_3Clicked()));
	//connect(ui.CapSaveBtn_cad_3, SIGNAL(clicked()), this, SLOT(slotCapSaveCadBtn_3Clicked()));
	
	
	//connect(ui.tab, SIGNAL(currentChanged(int)), this, SLOT(slotTabChanged(int)));


	connect(ui.ViewVertex_1, SIGNAL(clicked()), this, SLOT(ViewVertex_1()));
	connect(ui.ViewWireFrame_1, SIGNAL(clicked()), this, SLOT(ViewWireFrame_1()));
	connect(ui.ViewFace_1, SIGNAL(clicked()), this, SLOT(ViewFace_1()));
	connect(ui.ViewEdgedFace_1, SIGNAL(clicked()), this, SLOT(ViewEdgedFace_1()));


	int sizeX = 0;	int sizeY = 0;
	sizeX = this->ui.Viewer_cad_1->width();	sizeY = this->ui.Viewer_cad_1->height();
	m_MeshPreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_1->winId()), sizeX, sizeY);
	
	sizeX = this->ui.Viewer_2d->width();	sizeY = this->ui.Viewer_2d->height();
	m_ImagePreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_2d->winId()), sizeX, sizeY);
}

void IOModule::resizeEvent(QResizeEvent * event)
{
	//m_MeshPreviewer->GetRenderWindow()->SetSize(ui.Viewer_cad_1->width(), ui.Viewer_cad_1->height());
	//m_ImagePreviewer->GetRenderWindow()->SetSize(ui.Viewer_2d->width(), ui.Viewer_2d->height());
}



void IOModule::DestroyVariables()
{
	if (m_IsMeshViewer)
	{
		for (int i = 0; i < 3; i++)
		{
			delete m_MeshPreviewer;
			m_MeshPreviewer = NULL;
		}
	}
	if (m_IsImageViewer)
	{
		delete m_ImagePreviewer;
		m_ImagePreviewer = NULL;
	}

}


void IOModule::slotTabChanged(int idx)
{
	if (idx == 1)//////check here
		m_MeshPreviewer->GetRenderWindow()->SetSize(ui.Viewer_cad_1->width(), ui.Viewer_cad_1->height());
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
void IOModule::loadCadBtn()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open CAD Data"), "", tr("CAD data(*.stl *.obj *.ply)"),
		NULL, QFileDialog::DontUseNativeDialog);

	if (filename.isEmpty())	return;

	int DataType = this->GetCADType(filename);
	

	if (DataType != -1)this->LoadCADData(DataType, filename);

}

void IOModule::LoadCADData(int type, QString filePath)
{
	if (m_IsMeshViewer)
	{
		m_MeshPreviewer->ReleaseModel();
	}
	
	//m_MeshPreviewer[frameNum-1]->GetRenderWindow()->SetSize(ui.Viewer_cad_1->width(), ui.Viewer_cad_1->height());
	if (type == CAD_TYPE_OBJ)
	{//obj file -> png texture render
		QString bmpTextureFile = filePath;
		bmpTextureFile.replace("obj", "bmp", Qt::CaseInsensitive);
		QFile file(bmpTextureFile);
		if (file.exists()) m_MeshPreviewer->CreateTexture(bmpTextureFile.toStdString().c_str(), IMG_TYPE_BMP);
	}
	m_MeshPreviewer->CreateModel(filePath.toStdString().c_str(), type);

	m_MeshPreviewer->Rendering();
	ui.PathEdit_cad_1->setText(filePath);

	std::cout << "Smile";
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

void IOModule::saveCadBtn()
{
	if (!m_IsMeshViewer)
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
		if (!m_MeshPreviewer->IsTexture())
		{
			m_MeshPreviewer->NonTextureMeshSave(fileName.toStdString().c_str(), CAD_TYPE_OBJ);
		}

		QString textureBMP = fileName + ".bmp";//obj file의 texture는 bmp로 저장
		m_MeshPreviewer->TextureMeshSave(fileName.toStdString().c_str(), CAD_TYPE_OBJ, textureBMP.toStdString().c_str(), IMG_TYPE_BMP);
	}
	else
		m_MeshPreviewer->MeshSave(filepath.toStdString().c_str(), imgType);
}

/*******************************************************************************************************************************/

void IOModule::CapSavebtn()
{
	if (!m_IsMeshViewer)
		return;

	QString fileExtension = "*.png";
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Mesh Capture Image"), "",
		tr("PNG (*.png);; JPG (*.jpg);; TIF (*.tif);; BMP (*.bmp)"), &fileExtension, QFileDialog::DontUseNativeDialog);

	if (fileName.isEmpty()) return;

	int imgType = this->GetImgType(fileExtension);
	QString filepath = fileName + fileExtension.mid(6, 4);
	if (imgType != -1)
		m_MeshPreviewer->CaptureSave(filepath.toStdString().c_str(), imgType, 1);
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
	m_MeshPreviewer->ChangeViewMode(0); //0 point 1 wire 2 face 3 edgeface
}
void IOModule::ViewWireFrame_1()
{
	m_MeshPreviewer->ChangeViewMode(1);
}

void IOModule::ViewFace_1()
{
	m_MeshPreviewer->ChangeViewMode(2);
}

void IOModule::ViewEdgedFace_1()
{
	m_MeshPreviewer->ChangeViewMode(3);
}