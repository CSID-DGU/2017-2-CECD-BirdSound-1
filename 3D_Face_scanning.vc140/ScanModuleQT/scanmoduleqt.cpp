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

	delete RealSenseD415;
	delete Scanner;

	delete m_DepthPreviewer;
	delete m_MeshPreviewer;
	return 1;
}
ScanModuleQT::~ScanModuleQT()
{
	DestroyVariables();
}

void ScanModuleQT::InitializeVariables()
{
	m_IsMeshPreviewer = 0;
	m_IsDepthPreviewer = 0;
//	Scanner->Viewer = NULL;

	std::string serial = realsense::getFirstSerial();
	RealSenseD415=new realsense::Device(serial);
	Scanner=new Scan();

	m_MeshPreviewer = new MeshPreview();
	m_DepthPreviewer = new DepthMapPreviewer();
}

void ScanModuleQT::InitializeScene()
{

	m_IsDepthPreviewer = 1;
	m_DepthPreviewer->Create2DScene();
	//m_PointCloudPreviewer->CreateModel();

	m_IsMeshPreviewer = 1;
	m_MeshPreviewer->Create3DScene();
	//m_MeshPreviewer->CreateModel();
}



/*1번*/
void ScanModuleQT::imageMedian3D(int val)
{

	Scanner->imageMedian3D(m_DepthPreviewer, val);
	
}

/*2번*/
void ScanModuleQT::gausianFilterStd(int std)
{
	Scanner->gaussianStd(m_DepthPreviewer, (double)(std / 10.0));
}

/*3번*/
void ScanModuleQT::gausianFilterRad(int rad)
{
	Scanner->gaussianRad(m_DepthPreviewer, (double)(rad/40.0));
}

/*버튼으로 번경*/
void ScanModuleQT::MeshSmoothing()
{
	Scanner->meshSmooth(m_MeshPreviewer, 0.023);
	std::cout << "done";
}

void ScanModuleQT::GausStdBtn()
{
	ui.GausianStd_slid->setDisabled(true);
	ui.GausianRad_slid->setDisabled(false);
}
void ScanModuleQT::GausRadBtn()
{
	ui.GausianRad_slid->setDisabled(true);
}
void  ScanModuleQT::MedianBtn()
{
	ui.Median3D_slid->setDisabled(true);
	ui.GausianStd_slid->setDisabled(false);
}
void ScanModuleQT::InitializeUi()
{
	ui.setupUi(this);

	//ADD-HHS
	connect(ui.CapBtn, SIGNAL(clicked()), this, SLOT(slotCapBtn()));
	connect(ui.NextBtn, SIGNAL(clicked()), this, SLOT(slotNextBtn()));
	connect(ui.MultiCatpBtn, SIGNAL(clicked()), this, SLOT(slotMultiCapBtn()));
	connect(ui.FilterApplyBtn, SIGNAL(clicked()), this, SLOT(slotApplyFilter()));

	connect(ui.Median3D_slid, SIGNAL(valueChanged(int)), this, SLOT(imageMedian3D(int)));
	connect(ui.GausianStd_slid, SIGNAL(valueChanged(int)), this, SLOT(gausianFilterRad(int)));
	connect(ui.GausianRad_slid, SIGNAL(valueChanged(int)), this, SLOT(gausianFilterStd(int)));
	connect(ui.MeshSmoothBtn, SIGNAL(clicked()), this, SLOT(MeshSmoothing()));

	connect(ui.GausianStdBtn, SIGNAL(clicked()), this, SLOT(GausStdBtn()));
	connect(ui.GausianRadBtn, SIGNAL(clicked()), this, SLOT(GausRadBtn()));
	connect(ui.MedianBtn, SIGNAL(clicked()), this, SLOT(MedianBtn()));
	connect(ui.NextBtn2, SIGNAL(clicked()), this, SLOT(slotNextBtn2()));


	ui.GausianStd_slid->setDisabled(true);
	ui.GausianRad_slid->setDisabled(true);
	/*
	버튼 3개 더 달기
	
	*/

	int sizeX = 0;	int sizeY = 0;
	sizeX = this->ui.Viewer_cad_2D->width();	sizeY = this->ui.Viewer_cad_2D->height();
	
	m_DepthPreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_2D->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_cad_3D->width();	sizeY = this->ui.Viewer_cad_3D->height();
	m_MeshPreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_3D->winId()), sizeX, sizeY);

}

void ScanModuleQT::slotNextBtn2()
{
	if (m_IsMeshPreviewer)
		m_MeshPreviewer->ReleaseModel();
	m_MeshPreviewer->CreateModel("", 0);
	m_MeshPreviewer->Rendering();

	Scanner->MeshConstruction(m_MeshPreviewer, 4, 0, 4);
	m_MeshPreviewer->GetRenderer()->ResetCamera();
}
void ScanModuleQT::slotApplyFilter()
{
	m_DepthPreviewer->CreateModel("", 0);
	m_DepthPreviewer->Rendering();

	Scanner->frames2PointsCutOutlier();
	Scanner->printDepthMap(m_DepthPreviewer, RealSenseD415, realsense::RS400_STREAM_DEPTH);
	ui.MultiCatpBtn->setDisabled(false);
};
void ScanModuleQT::slotMultiCapBtn()
{
	if (m_IsDepthPreviewer)
	{
		m_DepthPreviewer->ReleaseModel();
		Scanner->ReleaseModel();
	}

	ui.MultiCatpBtn->setDisabled(true);
	//RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH, realsense::R1280_720, realsense::RS_400_FORMAT::Z16, realsense::RS_400_FPS::HZ30);

	for (int i = 0; i < 60; i++)
	{
		if(i%10==0)
		RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH, realsense::R1280_720, realsense::RS_400_FORMAT::Z16, realsense::RS_400_FPS::HZ30);
		rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
		Scanner->InsertFrame(fra);
	}
	
	//Scanner->frame2Points(fra);

}


void ScanModuleQT::slotCapBtn() 
{
	if (m_IsDepthPreviewer)
	{
		m_DepthPreviewer->ReleaseModel();
		Scanner->ReleaseModel();
	}
	m_DepthPreviewer->CreateModel("",0);
	m_DepthPreviewer->Rendering();
	RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH, realsense::R1280_720, realsense::RS_400_FORMAT::Z16, realsense::RS_400_FPS::HZ30);

	rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
	std::cout << "!";
	Scanner->frame2Points(fra);
	Scanner->printDepthMap(m_DepthPreviewer,RealSenseD415, realsense::RS400_STREAM_DEPTH);
}

void ScanModuleQT::slotNextBtn() 
{
	if (m_IsMeshPreviewer)
		m_MeshPreviewer->ReleaseModel();
	m_MeshPreviewer->CreateModel("", 0);
	m_MeshPreviewer->Rendering();
	Scanner->upDataPoint(m_DepthPreviewer);

	Scanner->MeshConstruction(m_MeshPreviewer, 4, 0, 4);


	m_MeshPreviewer->GetRenderer()->ResetCamera();
}



