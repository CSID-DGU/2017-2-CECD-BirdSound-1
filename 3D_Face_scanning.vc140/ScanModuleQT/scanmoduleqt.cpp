#include "scanmoduleqt.h"


#include"vtkImageViewer2.h"//이거 나주에 지워
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

	//delete RealSenseD415;
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

	connect(ui.TextureMappingBtn, SIGNAL(clicked()), this, SLOT(slotTextureMapping()));


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
	m_MeshPreviewer->CreateTexture("", 0);

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


/*
Scanner->InsertFrame(fra);
이부분에 fra에 frame만 넣어주면 됨.
*/
void ScanModuleQT::slotTextureMapping()
{

	//vtkImageViewer2 *test = vtkImageViewer2::New();
	//if(!m_MeshPreviewer->IsTexture())
	//m_MeshPreviewer->CreateTexture("", 0);
//	test->SetInputData(m_MeshPreviewer->m_ImageData);
	//test->Render();

	//vtkSmartPointer<vtkActor> texturedPlane =
		//vtkSmartPointer<vtkActor>::New();
	//texturedPlane->SetMapper(m_Mesh);
	//texturedPlane->SetTexture(texture);

// texture coordinates arrary 만들기
	//1/x축픽셀개수
	//1/y축픽셀개수
//	
//	vtkSmartPointer<vtkPoints> tmpPt = vtkSmartPointer<vtkPoints>::New();
//	tmpPt->DeepCopy(m_MeshPreviewer->GetPolyDataAt(0)->GetPoints());
//	tmpPt->Modified();
//
//	vtkSmartPointer<vtkCellArray> tmpPoly = vtkSmartPointer<vtkCellArray>::New();
//	tmpPoly->DeepCopy(m_MeshPreviewer->GetPolyDataAt(0)->GetPolys());
//	tmpPoly->Modified();
//
//	m_MeshPreviewer->GetPolyDataAt(0)->ReleaseData();
//	m_MeshPreviewer->GetPolyDataAt(0)->Delete();
//
//	m_MeshPreviewer->m_PolyData[0] = vtkPolyData::New();
//	m_MeshPreviewer->m_PolyData[0]->SetPoints(tmpPt);
//	m_MeshPreviewer->m_PolyData[0]->SetPolys(tmpPoly);
//	m_MeshPreviewer->m_PolyData[0]->Modified();
//
///*
//	vtkSmartPointer<vtkDoubleArray> textureCoords = vtkSmartPointer<vtkDoubleArray>::New();
//	textureCoords->SetNumberOfComponents(3);
//	double tcoords[3] = { 0.0, 0.0, 0.0 };
//	double rowSpacing = 1.0  / 1280.0;
//	double columnSpacing = 1.0 / 720.0;
//	double xCoord = 0.0;
//	double yCoord = 0.0;
//
//	//vtkPoints *pts = Scanner->GetPoints();
//	for (int i = 0; i<1280; i++)
//	{
//		xCoord = rowSpacing*i;
//		for (int j = 0; j<720; j++)
//		{
//			yCoord = columnSpacing*j;
//			tcoords[0] = xCoord;
//			tcoords[1] = yCoord;
//			tcoords[2] = 0.0;
//			textureCoords->InsertNextTuple(tcoords);
//
//			//std::cout << tcoords[0] << " " << tcoords[1] << " " << tcoords[2] << "\n";
//		}
//	}
//	textureCoords->Modified();
//
//	m_MeshPreviewer->GetPolyDataAt(0)->GetPointData()->SetTCoords(textureCoords);
//
//*/
//	vtkNew<vtkFloatArray> textureCoords;
//	textureCoords->SetNumberOfComponents(3);
//	float tcoords[3] = { 0.0, 0.0, 0.0 };
//	double rowSpacing = 1.0 / 1280.0;
//	double columnSpacing = 1.0 / 720.0;
//	double xCoord = 0.0;
//	double yCoord = 0.0;
//
//	vtkPoints *pts = Scanner->GetPoints();
//	vtkPLYWriter *wri = vtkPLYWriter::New();
//	wri->SetFileName("my.ply");
//	wri->SetInputData(m_MeshPreviewer->GetPolyDataAt(0));
//	//wri->SetFileTypeToBinary();
//	wri->SetFileTypeToASCII();
//	wri->Write();
//
//	vtkPNGWriter *ima = vtkPNGWriter::New();
//	ima->SetFileName("ima.jpg");
//	ima->SetInputData(m_MeshPreviewer->GetImageData());
//	ima->Write();
//
//	vtkPLYReader *stRead = vtkPLYReader::New();
//	stRead->SetFileName("my.ply");
//	stRead->Update();
//
//	vtkPolyData* pol = vtkPolyData::New();
//	pol->DeepCopy(stRead->GetOutput());
//	pol->Modified();
//
//
//	int n = pol->GetNumberOfPoints();
//
//	for (int i = 0; i<n; i++)
//	{
//		double temp[3];
//
//		pol->GetPoint(i, temp);
//
//		float abc[3];
//		abc[0] = temp[0];
//		abc[1] = temp[1];
//		abc[2] = 0.0;
//		textureCoords->InsertNextTuple(abc);
//	}
//	pol->GetPointData()->SetTCoords(textureCoords);
//	pol->Modified();
//
//	vtkPolyDataMapper *mp = vtkPolyDataMapper::New();
//	mp->SetInputData(pol);
//	mp->Update();
//	
//	vtkPNGReader *prd = vtkPNGReader::New();
//	prd->SetFileName("ima.jpg");
//	prd->Update();
//
//
//	vtkTexture *text = vtkTexture::New();
//	text->SetInputData(prd->GetOutput());
//	text->Modified();
//
//	vtkActor *act = vtkActor::New();
//	act->SetMapper(mp);
//	act->SetTexture(text);
//
//	vtkRenderer *ren = vtkRenderer::New();
//	ren->AddActor(act);
//	vtkRenderWindow *win = vtkRenderWindow::New();
//	win->AddRenderer(ren);
//	ren->ResetCamera();
//	win->Render();
//
//	int a = 0;
//	a++;
//
//	for (int i = 0; i<1280*720; i++)
//	{
//		double temp[3];
//
//		m_MeshPreviewer->GetPolyDataAt(0)->GetPoint(i, temp);
//		
//		float abc[3];
//		abc[0] = temp[0];
//		abc[1] = temp[1];
//		abc[2] = 0;
//		textureCoords->InsertNextTuple(abc);
//		int  a = 0;
//		//for (int j = 0; j<720; j++)
//		//{
//		//	yCoord = columnSpacing*j;
//		//	tcoords[0] = xCoord;
//		//	tcoords[1] = yCoord;
//		//	tcoords[2] = 0.0;
//		//	textureCoords->InsertNextTuple(tcoords);
//
//		//	//std::cout << tcoords[0] << " " << tcoords[1] << " " << tcoords[2] << "\n";
//		//}
//	}
//
//	//for (int i = 0; i<1280; i++)
//	//{
//	//	xCoord = rowSpacing*i;
//	//	for (int j = 0; j<720; j++)
//	//	{
//	//		yCoord = columnSpacing*j;
//	//		tcoords[0] = xCoord;
//	//		tcoords[1] = yCoord;
//	//		tcoords[2] = 0.0;
//	//		textureCoords->InsertNextTuple(tcoords);
//
//	//		//std::cout << tcoords[0] << " " << tcoords[1] << " " << tcoords[2] << "\n";
//	//	}
//	//}
//	textureCoords->Modified();
//
//	m_MeshPreviewer->GetPolyDataAt(0)->GetPointData()->SetTCoords(textureCoords.GetPointer());
//
//
//
//	m_MeshPreviewer->GetTexture()->SetInputData(m_MeshPreviewer->m_ImageData);
//	m_MeshPreviewer->GetTexture()->Update();
//
//	m_MeshPreviewer->m_Renderer->RemoveActor(m_MeshPreviewer->GetActorAt(0));
//	m_MeshPreviewer->m_Actor[0]->Delete();
//	m_MeshPreviewer->m_Actor[0] = NULL;
//	m_MeshPreviewer->GetMapperAt(0)->Delete();
//	m_MeshPreviewer->m_Mapper[0] = NULL;
//
//
//	m_MeshPreviewer->m_Mapper[0]= vtkPolyDataMapper::New();	
//	m_MeshPreviewer->m_Mapper[0]->SetInputData(m_MeshPreviewer->GetPolyDataAt(0));
//	m_MeshPreviewer->m_Mapper[0]->Update();
//
//	m_MeshPreviewer->m_Actor[0] = vtkActor::New();
//	m_MeshPreviewer->GetActorAt(0)->SetMapper(m_MeshPreviewer->m_Mapper[0]);
//	m_MeshPreviewer->GetActorAt(0)->SetTexture(m_MeshPreviewer->m_Texture);
//	m_MeshPreviewer->m_Actor[0]->GetProperty()->SetRepresentationToSurface();
//
//	
//	m_MeshPreviewer->m_Renderer->AddActor(m_MeshPreviewer->m_Actor[0]);
//	m_MeshPreviewer->m_Renderer->ResetCamera();
//	m_MeshPreviewer->m_RenWin->AddRenderer(m_MeshPreviewer->m_Renderer);
//	m_MeshPreviewer->m_IRen->SetRenderWindow(m_MeshPreviewer->GetRenderWindow());
//	//std::cout << m_MeshPreviewer->GetTexture()->GetImageDataInput();
//	
//	
//	m_MeshPreviewer->m_IRen->Modified();
//	m_MeshPreviewer->m_IRen->Render();
//	/*1. render 에서 actor remove 
//	2. actor delete
//	3. mapper delete
//	4. mapper 생성, 데이터 입력
//	5. actor setMapper / settexture
//	6. add actor
//	7. render. */
//
//	std::cout << "Done";
}
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


	/*이부분은 texture부분임. 여기는 fra에 rgb8 영상 넣으면됨. 귀찮으면 써놓은 select sensor복붙 ㄱㄱ 아래와 동일함. */
	RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_COLOR, realsense::R1280_720, realsense::RS_400_FORMAT::RGB8, realsense::RS_400_FPS::HZ30);
	rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_COLOR);
	Scanner->ScanTexture(m_MeshPreviewer,fra);
}

/*
rs2::frame fra = RealSenseD415->capture(realsense::RS400_STREAM_DEPTH);
Scanner->frame2Points(fra);
이부분에 fra에 frame만 넣어주면 됨.
*/
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
	Scanner->frame2Points(fra);
	Scanner->printDepthMap(m_DepthPreviewer,RealSenseD415, realsense::RS400_STREAM_DEPTH);


	/*이부분은 texture부분임. 여기는 fra에 rgb8 영상 넣으면됨. 귀찮으면 써놓은 select sensor복붙 ㄱㄱ*/
	RealSenseD415->selectSensorAndStreamProps(realsense::RS400_STREAM_COLOR, realsense::R1280_720, realsense::RS_400_FORMAT::RGB8, realsense::RS_400_FPS::HZ30);
	rs2::frame fra2 = RealSenseD415->capture(realsense::RS400_STREAM_COLOR);
	Scanner->ScanTexture(m_MeshPreviewer, fra2);
}

void ScanModuleQT::slotNextBtn() 
{
	if (m_IsMeshPreviewer)
		m_MeshPreviewer->ReleaseModel();
	m_MeshPreviewer->CreateModel("", 0);
	m_MeshPreviewer->CreateTexture("", 0);
	m_MeshPreviewer->Rendering();

	Scanner->upDataPoint(m_DepthPreviewer);

	Scanner->MeshConstruction(m_MeshPreviewer, 4, 0, 4);


	m_MeshPreviewer->GetRenderer()->ResetCamera();
}



