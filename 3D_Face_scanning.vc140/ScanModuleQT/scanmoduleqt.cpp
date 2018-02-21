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

void ScanModuleQT::HybridMedian2D(int val)
{
	if (val == 1)
		Scanner->hybridMedian2D(m_DepthPreviewer,val);
	
}

void ScanModuleQT::imageMedian3D(int val)
{

	Scanner->imageMedian3D(m_DepthPreviewer, val);
	
}

void ScanModuleQT::gausianFilterStd(int std)
{
	//Scanner->imageMedian3D(m_DepthPreviewer, val);
	Scanner->gaussianStd(m_DepthPreviewer, (double)(std / 3.0));
}

void ScanModuleQT::gausianFilterRad(int rad)
{
	//Scanner->imageMedian3D(m_DepthPreviewer, val);
	Scanner->gaussianRad(m_DepthPreviewer, (double)(rad/3.0));
}

void ScanModuleQT::MeshSmoothing(int relax)
{
	//Scanner->imageMedian3D(m_DepthPreviewer, val);
	std::cout << relax / 100.0 << "@@@@";
	static bool test = false;
	if (test == false)
	{
		test = true;
		Scanner->meshSmooth(m_MeshPreviewer, (double)(relax / 100.0));
	}
}
void ScanModuleQT::InitializeUi()
{
	ui.setupUi(this);

	//ADD-HHS
	connect(ui.CapBtn, SIGNAL(clicked()), this, SLOT(slotCapBtn()));
	connect(ui.NextBtn, SIGNAL(clicked()), this, SLOT(slotNextBtn()));


	connect(ui.Hybrid2D_slid, SIGNAL(valueChanged(int)), this, SLOT(HybridMedian2D(int)));
	connect(ui.Median3D_slid, SIGNAL(valueChanged(int)), this, SLOT(imageMedian3D(int)));
	connect(ui.GausianStd_slid, SIGNAL(valueChanged(int)), this, SLOT(gausianFilterRad(int)));
	connect(ui.GausianRad_slid, SIGNAL(valueChanged(int)), this, SLOT(gausianFilterStd(int)));

	connect(ui.MeshSmooth_slid, SIGNAL(valueChanged(int)), this, SLOT(MeshSmoothing(int)));

	int sizeX = 0;	int sizeY = 0;
	sizeX = this->ui.Viewer_cad_2D->width();	sizeY = this->ui.Viewer_cad_2D->height();
	
	m_DepthPreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_2D->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_cad_3D->width();	sizeY = this->ui.Viewer_cad_3D->height();
	m_MeshPreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_3D->winId()), sizeX, sizeY);

}




void ScanModuleQT::slotCapBtn() 
{
	if(m_IsDepthPreviewer)
		m_DepthPreviewer->ReleaseModel();
	m_DepthPreviewer->CreateModel("",0);
	RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH, realsense::R1280_720, realsense::RS_400_FORMAT::Z16, realsense::RS_400_FPS::HZ30);

	rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
	std::cout << "!";
	Scanner->frame2Points(fra);
	Scanner->printDepthMap(m_DepthPreviewer,RealSenseD415, realsense::RS400_STREAM_DEPTH);
	//Scanner->printPointCloud(m_DepthPreviewer);
	//RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH,realsense::R1280_720,realsense::RS_400_FORMAT::Z16,realsense::RS_400_FPS::HZ30);

	//RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH, realsense::R1280_720, realsense::RS_400_FORMAT::Z16, realsense::RS_400_FPS::HZ30);
	//m_DepthMapPreviewer->ReleaseModel();
	//Scanner->printDepthMap(m_DepthMapPreviewer, RealSenseD415, realsense::RS400_STREAM_DEPTH);
	
	
}
void ScanModuleQT::slotNextBtn() 
{
	if (m_IsMeshPreviewer)
		m_MeshPreviewer->ReleaseModel();
	m_MeshPreviewer->CreateModel("", 0);

	Scanner->upDataPoint(m_DepthPreviewer);

	
	RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH, realsense::R1280_720, realsense::RS_400_FORMAT::Z16, realsense::RS_400_FPS::HZ30);

	for (int i = 0; i < 1; i++)
	{
		
		clock_t begin;
		begin = clock();
		//rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
		std::cout << "!";
		//Scanner->frame2Points(fra);
		std::cout << "!";
		Scanner->MeshConstruction(m_MeshPreviewer, 4, 0, 4);
		//printf("%d %lf", sizeof(fra), (double(clock()) - double(begin)) / 1000.0);
	}


}



