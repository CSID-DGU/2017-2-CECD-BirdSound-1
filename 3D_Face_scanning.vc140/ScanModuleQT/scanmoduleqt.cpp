#include "scanmoduleqt.h"

ScanModuleQT::ScanModuleQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	InitializeVariables();
	InitializeScene();
	InitializeUi();
}

int ScanModuleQT::DestroyVariables()
{
	/*delete[] m_MiniMeshPreviewer;
	delete m_MeshPreviewer;
	delete m_ImagePreviewer;*/

	for(int i=0;i<3;i++)
		m_MiniMeshPreviewer[i]->DestroyVariables();

	delete m_ImagePreviewer;
	delete RealSenseD415;
	delete Scanner;
	return 1;
}
ScanModuleQT::~ScanModuleQT()
{
	DestroyVariables();
}

void ScanModuleQT::InitializeVariables()
{

	for (int i = 0; i < 3; i++)
	{
		m_MiniMeshPreviewer[i] = NULL;
		m_MiniMeshPreviewer[i] = 0;
	}

	m_IsImageViewer = 0;
	m_ImagePreviewer = NULL;

	m_ScannedMeshViewer = 0;
//	Scanner->Viewer = NULL;

	std::string serial = realsense::getFirstSerial();
	RealSenseD415=new realsense::Device(serial);
	Scanner=new Scan();
}

void ScanModuleQT::InitializeScene()
{
	for (int i = 0; i < 3; i++)
	{
		m_MiniMeshPreviewer[i] = new MeshPreview;
		m_MiniMeshPreviewer[i]->Create3DScene();
		m_IsMiniMeshViewer[i] = 1;
	}


	m_ScannedMeshViewer = 1;

	m_ImagePreviewer = new RealSensePreviewer;
	m_ImagePreviewer->Create2DScene();
	m_IsImageViewer = 1;
}


void ScanModuleQT::InitializeUi()
{
	ui.setupUi(this);

	//ADD-HHS
	connect(ui.CapBtn, SIGNAL(clicked()), this, SLOT(slotCapBtn()));
	connect(ui.NextBtn, SIGNAL(clicked()), this, SLOT(slotNextBtn()));
	connect(ui.LeftSaveBtn, SIGNAL(clicked()), this, SLOT(slotLeftSaveBtn()));
	connect(ui.RightSaveBtn, SIGNAL(clicked()), this, SLOT(slotRightSaveBtn()));
	connect(ui.FrontSaveBtn, SIGNAL(clicked()), this, SLOT(slotFrontSaveBtn()));
	connect(ui.StreamingBtn, SIGNAL(clicked()), this, SLOT(slotStreamingBtn()));

	
	int sizeX = 0;	int sizeY = 0;
	sizeX = this->ui.Viewer_cad_2D->width();	sizeY = this->ui.Viewer_cad_2D->height();
	m_ImagePreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_2D->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_cad_3D->width();	sizeY = this->ui.Viewer_cad_3D->height();
	Scanner->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_3D->winId()), sizeX, sizeY);


	
	sizeX = this->ui.Viewer_cad_FRONT->width();	sizeY = this->ui.Viewer_cad_FRONT->height();
	m_MiniMeshPreviewer[0]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_FRONT->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_cad_LEFT->width();	sizeY = this->ui.Viewer_cad_LEFT->height();
	m_MiniMeshPreviewer[1]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_LEFT->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_cad_RIGHT->width();	sizeY = this->ui.Viewer_cad_RIGHT->height();
	m_MiniMeshPreviewer[2]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_RIGHT->winId()), sizeX, sizeY);
}




void ScanModuleQT::slotCapBtn() 
{

	
	RealSenseD415->selectSensorAndStreamProps();

	
	//Scanner->eraseFrame();
	//for (int i = 0; i < 5; i++)
	//{
	//	rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
	//	Scanner->InsertFrame(fra);
	//}


	//clock_t begin;
	//begin = clock();
	////sc->frame2Points(fra);
	//Scanner->frames2Points();
	//printf("%lf", (double(clock()) - double(begin)) / 1000.0);
	//Scanner->MeshConstruction(0, 0);
	for (int i = 0; i < 1; i++) 
	{
		Scanner->ReleaseModel();
		clock_t begin;
		begin = clock();
		rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
		std::cout << "!";
		Scanner->frame2Points(fra);
		std::cout << "!";
		Scanner->MeshConstruction(0, 0);
		printf("%d %lf", sizeof(fra), (double(clock()) - double(begin)) / 1000.0);
	}
	
}
void ScanModuleQT::slotNextBtn() {}
void ScanModuleQT::slotLeftSaveBtn() {}
void ScanModuleQT::slotRightSaveBtn() {}
void ScanModuleQT::slotFrontSaveBtn() {}


void ScanModuleQT::slotStreamingBtn() 
{
	RealSenseD415->selectSensorAndStreamPropsForPreviewer();
	m_ImagePreviewer->ReleaseModel();
	m_ImagePreviewer->streamingColorRaw16(RealSenseD415);
}