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
	char value = val + '0';
	ui.MedianVal->setText(QString(value));
}

/*2번*/
void ScanModuleQT::gausianFilterStd(int std)
{
	double value = (double)(std / 50.0);
	Scanner->gaussianStd(m_DepthPreviewer, value);

	std::stringstream str;
	str << std::fixed << setprecision(15) << value;
	std::string ss = str.str();
	ui.StdVal->setText(QString(ss.c_str()));

}

/*3번*/
void ScanModuleQT::gausianFilterRad(int rad)
{
	double value = (double)(rad / 10.0);
	Scanner->gaussianRad(m_DepthPreviewer, value);


	std::stringstream str;
	str << std::fixed << setprecision(15) << value;
	std::string ss = str.str();
	ui.RadVal->setText(QString(ss.c_str()));
}

/*버튼으로 번경*/
void ScanModuleQT::MeshSmoothing()
{
	Scanner->meshSmooth(m_MeshPreviewer, 0.02);
	//std::cout << "done";
	ui.MeshSmoothBtn->setDisabled(true);
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

/*
1. 디비
2. 전자계산기
3. os <- 수켈링 자료구조 나오
4. 데통
5. se

*/
void ScanModuleQT::InitializeUi()
{
	ui.setupUi(this);

	//ADD-HHS
	connect(ui.CapBtn, SIGNAL(clicked()), this, SLOT(slotCapBtn()));
	connect(ui.NextBtn, SIGNAL(clicked()), this, SLOT(slotNextBtn()));
	connect(ui.MultiCatpBtn, SIGNAL(clicked()), this, SLOT(slotMultiCapBtn()));
	connect(ui.FilterApplyBtn, SIGNAL(clicked()), this, SLOT(slotApplyFilter()));

	connect(ui.Median3D_slid, SIGNAL(valueChanged(int)), this, SLOT(imageMedian3D(int)));
	connect(ui.GausianRad_slid, SIGNAL(valueChanged(int)), this, SLOT(gausianFilterRad(int)));
	connect(ui.GausianStd_slid, SIGNAL(valueChanged(int)), this, SLOT(gausianFilterStd(int)));
	connect(ui.MeshSmoothBtn, SIGNAL(clicked()), this, SLOT(MeshSmoothing()));

	connect(ui.GausianStdBtn, SIGNAL(clicked()), this, SLOT(GausStdBtn()));
	connect(ui.GausianRadBtn, SIGNAL(clicked()), this, SLOT(GausRadBtn()));
	connect(ui.MedianBtn, SIGNAL(clicked()), this, SLOT(MedianBtn()));
	connect(ui.NextBtn2, SIGNAL(clicked()), this, SLOT(slotNextBtn2()));
	
	connect(ui.ResetBtn, SIGNAL(clicked()), this, SLOT(slotResetBtn()));


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
void ScanModuleQT::slotResetBtn()
{
	/*
	1. Slider를 활성화 한다.
	2. DepthMap을 Origin으로 변경한다.  
	3. 기존의 DepthMap을 다시 Rendering한다.
	*/
	//ui.GausianRad_slid;
	//ui.GausianStd_slid;
	ui.Median3D_slid->setDisabled(false);
	ui.MeshSmoothBtn->setDisabled(false);

	ui.GausianStd_slid->setDisabled(true);
	ui.GausianRad_slid->setDisabled(true);

	ui.GausianStd_slid->setValue(0);
	ui.GausianRad_slid->setValue(0);
	ui.Median3D_slid->setValue(0);

	vtkImageData *image = vtkImageData::New();
	if (m_IsDepthPreviewer)
	{
		image->DeepCopy(m_DepthPreviewer->m_OriginImage);
		m_DepthPreviewer->ReleaseModel();
	}

	m_DepthPreviewer->CreateModel("",0);
	m_DepthPreviewer->m_ImageData->DeepCopy(image);
	m_DepthPreviewer->m_OriginImage->DeepCopy(image);

	//m_DepthPreviewer->GetActor()->GetMapper()->SetInputData(m_DepthPreviewer->m_ImageData);
	m_DepthPreviewer->GetRenderWindow()->Modified();
	m_DepthPreviewer->GetRenderer()->ResetCamera();
	m_DepthPreviewer->Rendering();
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

	for (int i = 0; i < 30; i++)
	{
		if(i%10==0)
		RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH, realsense::R1280_720, realsense::RS_400_FORMAT::Z16, realsense::RS_400_FPS::HZ30);
		rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
		Scanner->InsertFrame(fra);
	}

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



