#include "ScanModule.h"

ScanModule::ScanModule(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	InitializeVariables();
	InitializeScene();
	InitializeUi();
}

int ScanModule::DestroyVariables()
{
	/*delete[] m_MiniMeshPreviewer;
	delete m_MeshPreviewer;
	delete m_ImagePreviewer;*/

	for(int i=0;i<3;i++)
		m_MiniMeshPreviewer[i]->DestroyVariables();

	//delete m_ImagePreviewer;
	//delete RealSenseD415;
	delete Scanner;
	return 1;
}
ScanModule::~ScanModule()
{
	DestroyVariables();
}

void ScanModule::InitializeVariables()
{

	for (int i = 0; i < 3; i++)
	{
		m_MiniMeshPreviewer[i] = NULL;
		m_MiniMeshPreviewer[i] = 0;
	}

	//m_IsImageViewer = 0;
	//m_ImagePreviewer = NULL;

	m_ScannedMeshViewer = 0;
//	Scanner->Viewer = NULL;

	std::string serial = realsense::getFirstSerial();
	RealSenseD415=new realsense::Device(serial);
	Scanner=new Scan();
}

void ScanModule::InitializeScene()
{
	for (int i = 0; i < 3; i++)
	{
		m_MiniMeshPreviewer[i] = new MeshPreview;
		m_MiniMeshPreviewer[i]->Create3DScene();
		m_IsMiniMeshViewer[i] = 1;
	}


	m_ScannedMeshViewer = new MeshPreview(5);
	m_ScannedMeshViewer->Create3DScene();
	m_IsScannedMeshViewer = 1;

	for (int i = 0; i < 3; i++)
	{
		m_MiniMeshPreviewer[i] = new MeshPreview(5);
		m_MiniMeshPreviewer[i]->Create3DScene();
	}
//	m_ImagePreviewer = new RealSensePreviewer;
	//m_ImagePreviewer->Create2DScene();
	//m_IsImageViewer = 1;
}


void ScanModule::InitializeUi()
{
	ui.setupUi(this);

	//ADD-HHS
	connect(ui.CapBtn, SIGNAL(clicked()), this, SLOT(slotCapBtn()));
	connect(ui.NextBtn, SIGNAL(clicked()), this, SLOT(slotNextBtn()));
	connect(ui.LeftSaveBtn, SIGNAL(clicked()), this, SLOT(slotLeftSaveBtn()));
	connect(ui.RightSaveBtn, SIGNAL(clicked()), this, SLOT(slotRightSaveBtn()));
	connect(ui.FrontSaveBtn, SIGNAL(clicked()), this, SLOT(slotFrontSaveBtn()));
	connect(ui.StreamingBtn, SIGNAL(clicked()), this, SLOT(slotStreamingBtn()));
	connect(ui.MultiCapBtn, SIGNAL(clicked()), this, SLOT(slotCapPicBtn()));
	
	int sizeX = 0;	int sizeY = 0;
	sizeX = this->ui.Viewer_cad_2D->width();	sizeY = this->ui.Viewer_cad_2D->height();
	//m_ImagePreviewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_2D->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_cad_3D->width();	sizeY = this->ui.Viewer_cad_3D->height();
	//Scanner->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_3D->winId()), sizeX, sizeY);
	m_ScannedMeshViewer->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_3D->winId()), sizeX, sizeY);


	
	sizeX = this->ui.Viewer_cad_FRONT->width();	sizeY = this->ui.Viewer_cad_FRONT->height();
	m_MiniMeshPreviewer[0]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_LEFT->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_cad_LEFT->width();	sizeY = this->ui.Viewer_cad_LEFT->height();
	m_MiniMeshPreviewer[1]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_FRONT->winId()), sizeX, sizeY);

	sizeX = this->ui.Viewer_cad_RIGHT->width();	sizeY = this->ui.Viewer_cad_RIGHT->height();
	m_MiniMeshPreviewer[2]->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.Viewer_cad_RIGHT->winId()), sizeX, sizeY);
}

void setTexture(MeshPreview *mesh)
{


	

	for (int i = 0; i < 1; i++)
	{
		vtkSmartPointer<vtkDoubleArray> textureCoordinates =vtkSmartPointer<vtkDoubleArray>::New();

		const int NumOfCom = mesh->GetPolyDataAt(i)->GetNumberOfPoints();
		
		textureCoordinates->SetNumberOfComponents(2);
		textureCoordinates->SetName("TextureCoordinates");

		for (int j = 0; j < NumOfCom; j++) 
		{
			double tuple[3] = { 0,0,0 };
			mesh->GetPolyDataAt(i)->GetPoint(j, tuple);
			textureCoordinates->InsertNextTuple(tuple);
			
		}

		mesh->GetPolyDataAt(i)->GetPointData()->SetTCoords(textureCoordinates);
		//mesh->GetActorAt(i)->SetTexture(mesh->GetTextureAt(i));
	}

	mesh->GetRenderWindow()->Modified();
	mesh->GetRenderWindow()->Render();
	mesh->GetRenderWindow()->Start();
	
	/*vtkRenderer *rend = vtkRenderer::New();
	vtkImageActor *act = vtkImageActor::New();
	act->SetInputData(mesh->m_ImageData[0]);

	rend->AddActor(act);
	vtkRenderWindow *win = vtkRenderWindow::New();


	win->AddRenderer(rend);
	win->Modified();
	win->Start();*/
	//mesh->GetActorAt(0)->SetTexture(mesh_
}
void ScanModule::slotCapBtn()
{

	
	if (m_ScannedMeshViewer)
	{
		m_ScannedMeshViewer->ReleaseModel();
		Scanner->ReleaseModel();
	}

	//m_ScannedMeshViewer->CreateTexture("", 0);
	m_ScannedMeshViewer->CreateModel("", 0);
	//m_ScannedMeshViewer->Rendering();

	RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_DEPTH, realsense::R1280_720, realsense::RS_400_FORMAT::Z16, realsense::RS_400_FPS::HZ30);

	rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
	Scanner->frame2Points(fra);
	Scanner->MeshConstruction(m_ScannedMeshViewer,0, 4,4);
	//Scanner->printDepthMap(m_DepthPreviewer, RealSenseD415, realsense::RS400_STREAM_DEPTH);


	/*이부분은 texture부분임. 여기는 fra에 rgb8 영상 넣으면됨. 귀찮으면 써놓은 select sensor복붙 ㄱㄱ*/
	RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_COLOR, realsense::R1280_720, realsense::RS_400_FORMAT::RGB8, realsense::RS_400_FPS::HZ30);
	rs2::frame fra2 = RealSenseD415->capture(realsense::RS400_STREAM_COLOR);
	Scanner->ScanTexture(m_ScannedMeshViewer, fra2);
	setTexture(m_ScannedMeshViewer);
	

	m_ScannedMeshViewer->Rendering();
}
void ScanModule::slotNextBtn()
{
	AlignModule* qwe = new AlignModule;
	qwe->setLeft(m_MiniMeshPreviewer[0]);
	qwe->setFront(m_MiniMeshPreviewer[1]);
	qwe->setRight(m_MiniMeshPreviewer[2]);



	//m_MiniMeshPreviewer
	qwe->Rendering();
	qwe->show();
	//qwe->align();
}
void ScanModule::slotLeftSaveBtn()
{
	m_MiniMeshPreviewer[0]->m_MeshIO->ExportOBJFile(m_MiniMeshPreviewer[0]->GetRenderWindow(),"Left.obj");
}
void ScanModule::slotRightSaveBtn()
{
	m_MiniMeshPreviewer[1]->m_MeshIO->ExportOBJFile(m_MiniMeshPreviewer[1]->GetRenderWindow(), "right.obj");
}
void ScanModule::slotFrontSaveBtn() 
{
	m_MiniMeshPreviewer[2]->m_MeshIO->ExportOBJFile(m_MiniMeshPreviewer[2]->GetRenderWindow(), "right.obj");
}


void Copy(MeshPreview* src, MeshPreview* des)
{	
	if (des != NULL)
	{
		des->ReleaseModel();
	}

	des->CreateTexture("", 0);
	des->CreateModel("",0);

	for (int i = 0; i < 5; i++)
	{
		des->m_PolyData[i]->DeepCopy(src->GetPolyDataAt(i));
		//des->m_PolyData[i]->ShallowCopy(src->GetPolyDataAt(i));
		//des->m_Mapper[i]->ShallowCopy(src->GetMapperAt(i));
		//des->m_Actor[i]->ShallowCopy(src->GetActorAt(i));
	}

	des->GetRenderer()->Modified();
	des->GetRenderWindow()->Render();
}
void ScanModule::slotCapPicBtn()
{
	if (index == 0)
	{
		Copy(m_ScannedMeshViewer, m_MiniMeshPreviewer[0]);
		ui.Viewer_cad_LEFT->setStyleSheet("border: 1px solid black;background-color:black;");
		ui.Viewer_cad_FRONT->setStyleSheet("border: 3px solid red;background-color:black;");
		index = 1;
	}

	else if (index == 1)
	{
		Copy(m_ScannedMeshViewer, m_MiniMeshPreviewer[1]);
		ui.Viewer_cad_FRONT->setStyleSheet("border: 1px solid black;background-color:black;");
		ui.Viewer_cad_RIGHT->setStyleSheet("border: 3px solid red;background-color:black;");
		index = 2;
	}

	else if (index == 2)
	{
		ui.Viewer_cad_RIGHT->setStyleSheet("border: 1px solid black;background-color:black;");
		Copy(m_ScannedMeshViewer, m_MiniMeshPreviewer[2]);
		index = 3;
		std::cout << "Index Full\n";
	}


	else
	{
		ui.Viewer_cad_RIGHT->setStyleSheet("border: 1px solid black;background-color:black;");
		ui.Viewer_cad_LEFT->setStyleSheet("border: 3px solid red;background-color:black;");
		index = 0;
	}
}


void ScanModule::slotStreamingBtn()
{

}
