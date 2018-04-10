
#include"AlignModule.h"

/**
Member 변수에 있는 left, front, right로 Align을 시행하고
결과를 vtkRenderer로 뱉어낸다.
*/

AlignModule::AlignModule()
{
	InitializeVariables();
	InitializeUi();
}
void AlignModule::InitializeVariables()
{
	left=NULL;
	front=NULL;
	right = NULL;

	leftStyle = frontStyle = rightStyle = NULL;


	left  = new MeshPreview(5);
	front = new MeshPreview(5);
	right = new MeshPreview(5);

	left->Create3DScene();
	front->Create3DScene();
	right->Create3DScene();


	leftStyle  = LandMarkInteractorStyle::New();
	frontStyle = LandMarkInteractorStyle::New();
	rightStyle = LandMarkInteractorStyle::New();

	resultMesh = new MeshPreview(3);
	resultMesh->CreateModel("",0);
	resultMesh->Create3DScene();
}

int AlignModule::DestroyVariables()
{
	return 1;
}

void AlignModule::slotLanMarkLeft()
{
	leftStyle->initialize();
	left->setStyle(leftStyle);
	leftStyle->setRadis(left->GetActorAt(0));

	leftStyle->setMainActors(left->m_Actor);
	leftStyle->SetDefaultRenderer(left->GetRenderer());
	
}
void AlignModule::slotLanMarkFront()
{
	frontStyle->initialize();
	front->setStyle(frontStyle);
	frontStyle->setRadis(front->GetActorAt(0));

	frontStyle->setMainActors(front->m_Actor);
	frontStyle->SetDefaultRenderer(front->GetRenderer());
}
void AlignModule::slotLanMarkRight()
{
	rightStyle->initialize();
	right->setStyle(rightStyle);
	rightStyle->setRadis(right->GetActorAt(0));

	rightStyle->setMainActors(right->m_Actor);
	rightStyle->SetDefaultRenderer(right->GetRenderer());
}


void AlignModule::slotLeftOrigin()
{
	left->GetInteractor()->SetInteractorStyle(left->m_3DStyle);
}
void AlignModule::slotFrontOrigin()
{
	front->GetInteractor()->SetInteractorStyle(front->m_3DStyle);
}
void AlignModule::slotRightOrigin()
{
	right->GetInteractor()->SetInteractorStyle(right->m_3DStyle);
}



void AlignModule::slotFrontDefault()
{
	frontStyle->Reset();
//	front->GetRenderWindow()->AddRenderer(front->m_Renderer);
	
}
void AlignModule::slotRightDefault()
{
	rightStyle->Reset();
//	right->GetRenderWindow()->AddRenderer(right->m_Renderer);
	
}
void AlignModule::slotLeftDefault()
{
	leftStyle->Reset();
//	left->GetRenderWindow()->AddRenderer(left->m_Renderer);
	
}




void AlignModule::InitializeUi()
{
	ui.setupUi(this);

	//ADD-HHS
	connect(ui.AlignBtn, SIGNAL(clicked()), this, SLOT(slotAlign()));
	connect(ui.LandMarkBtn_1, SIGNAL(clicked()), this, SLOT(slotLanMarkLeft()));
	connect(ui.LandMarkBtn_2, SIGNAL(clicked()), this, SLOT(slotLanMarkFront()));
	connect(ui.LandMarkBtn_3, SIGNAL(clicked()), this, SLOT(slotLanMarkRight()));

	connect(ui.ToOrignBtn_1, SIGNAL(clicked()), this, SLOT(slotLeftDefault()));
	connect(ui.ToOrignBtn_2, SIGNAL(clicked()), this, SLOT(slotFrontDefault()));
	connect(ui.ToOrignBtn_3, SIGNAL(clicked()), this, SLOT(slotRightDefault()));

	connect(ui.DefaultBtn_1, SIGNAL(clicked()), this, SLOT(slotLeftOrigin()));
	connect(ui.DefaultBtn_2, SIGNAL(clicked()), this, SLOT(slotFrontOrigin()));
	connect(ui.DefaultBtn_3, SIGNAL(clicked()), this, SLOT(slotRightOrigin()));
	int sizeX = 0;	int sizeY = 0;
	
	sizeX = this->ui.cadLeft->width();	sizeY = this->ui.cadLeft->height();
	left->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.cadLeft->winId()), sizeX, sizeY);
	
	sizeX = this->ui.cadRight->width();	sizeY = this->ui.cadRight->height();
	right->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.cadRight->winId()), sizeX, sizeY);

	sizeX = this->ui.cadFront->width();	sizeY = this->ui.cadFront->height();
	front->ConnectSceneToCtrl(reinterpret_cast<void*>(this->ui.cadFront->winId()), sizeX, sizeY);
}

vtkPolyData* AlignModule::point2mesh(vtkPoints *pts)
{
	vtkPolyData* poly = vtkPolyData::New();
	vtkCellArray *cell = vtkCellArray::New();

	
	cell->InsertNextCell(pts->GetNumberOfPoints());
	for (int i = 0; i < pts->GetNumberOfPoints(); i++)
	{
		cell->InsertCellPoint(i);
	}

	poly->SetPolys(cell);
	poly->SetPoints(pts);

	cell->Delete();

	return poly;
}
void AlignModule::registration(vtkPoints *left, vtkPoints *leftFront, vtkPoints* rightFront, vtkPoints* right)
{
	//vtkPolyData *polyLeft  = vtkPolyData::New();
	//vtkPolyData *polyleFront = vtkPolyData::New();
	//vtkPolyData *polyriFront1 = vtkPolyData::New();
	//vtkPolyData *polyRight = vtkPolyData::New();


	//polyLeft = point2mesh(left);
	//polyleFront = point2mesh(leftFront);
	//polyriFront1 = point2mesh(rightFront);
	//polyRight = point2mesh(right);


	//const int alpha = 3;//If alpha big -> too slow
	//vtkSmartPointer<vtkIterativeClosestPointTransform> IcpleftFront =vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	//IcpleftFront->SetSource(polyLeft);
	//IcpleftFront->SetTarget(polyleFront);
	//IcpleftFront->GetLandmarkTransform()->SetModeToRigidBody();
	//IcpleftFront->SetMaximumNumberOfIterations(alpha);
	////icp->StartByMatchingCentroidsOn();
	//IcpleftFront->Modified();
	//IcpleftFront->Update();

	//vtkSmartPointer<vtkIterativeClosestPointTransform> IcprightFront = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	//IcprightFront->SetSource(polyRight);
	//IcprightFront->SetTarget(polyriFront1);
	//IcprightFront->GetLandmarkTransform()->SetModeToRigidBody();
	//IcprightFront->SetMaximumNumberOfIterations(alpha);
	////icp->StartByMatchingCentroidsOn();
	//IcprightFront->Modified();
	//IcprightFront->Update();


	//// Transform the source points by the ICP solution
	//vtkSmartPointer<vtkTransformPolyDataFilter> leftFrontFilter =vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	//leftFrontFilter->SetInputData(resultMesh->GetPolyDataAt(0));
	//leftFrontFilter->SetTransform(IcpleftFront);
	//leftFrontFilter->Update();

	//vtkSmartPointer<vtkTransformPolyDataFilter> rightFrontFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	//rightFrontFilter->SetInputData(resultMesh->GetPolyDataAt(2));
	//rightFrontFilter->SetTransform(IcprightFront);
	//rightFrontFilter->Update();



	//resultMesh->GetPolyDataAt(2)->ReleaseData();
	//resultMesh->GetPolyDataAt(2)->Delete();
	//resultMesh->m_PolyData[2] = vtkPolyData::New();
	//resultMesh->GetPolyDataAt(2)->DeepCopy(leftFrontFilter->GetOutput());
	//resultMesh->GetMapperAt(2)->SetInputData(resultMesh->m_PolyData[2]);
	//resultMesh->GetActorAt(2)->Modified();


	//resultMesh->GetPolyDataAt(0)->ReleaseData();
	//resultMesh->GetPolyDataAt(0)->Delete();
	//resultMesh->m_PolyData[0] = vtkPolyData::New();
	//resultMesh->GetPolyDataAt(0)->DeepCopy(rightFrontFilter->GetOutput());
	//resultMesh->GetMapperAt(0)->SetInputData(resultMesh->m_PolyData[0]);
	//resultMesh->GetActorAt(0)->Modified();
	//


	resultMesh->GetRenderWindow()->Render();
	resultMesh->GetRenderWindow()->Start();

}

int AlignModule::getIndex(vtkPolyData *poly, double *pos)
{
	
	return poly->FindPoint(pos);

}
void AlignModule::slotAlign()
{
	if (left == nullptr || front == nullptr || right == nullptr)
	{
		std::cout << "사진 3장 제대로 찍어요\n";
		return;
	}

	else
	{
		/*vtkAppendPolyData *a = vtkAppendPolyData::New();
		vtkAppendPolyData *b = vtkAppendPolyData::New();
		vtkAppendPolyData *c = vtkAppendPolyData::New();
	

		for (int i = 0; i < 5; i++)a->AddInputData(left->GetPolyDataAt(i));
		for (int i = 0; i < 5; i++)b->AddInputData(front->GetPolyDataAt(i));
		for (int i = 0; i < 5; i++)c->AddInputData(right->GetPolyDataAt(i));
		a->Update(); b->Update(); c->Update();

		vtkSTLWriter *stl = vtkSTLWriter::New();
		stl->SetFileName("front.stl");
		stl->SetInputData(a->GetOutput());
		stl->Write();

		stl->SetFileName("left.stl");
		stl->SetInputData(b->GetOutput());
		stl->Write();


		stl->SetFileName("right.stl");
		stl->SetInputData(c->GetOutput());
		stl->Write();*/



		if (!resultMesh)
		{
			resultMesh->ReleaseModel();
			resultMesh->CreateModel("",0);
		}
		std::vector<double3>leftMark;
		std::vector<double3>frontMark;
		std::vector<double3>rightMark;

		leftMark = extractLandMark(left->GetRenderer());
		frontMark = extractLandMark(front->GetRenderer());
		rightMark = extractLandMark(right->GetRenderer());

	
		vtkPoints*leftPts = vtkPoints::New();
		vtkPoints*rightPts = vtkPoints::New();
		vtkPoints*frontNleft = vtkPoints::New();
		vtkPoints*frontNright = vtkPoints::New();

		for (int i = 0; i < leftMark.size(); i++)
			leftPts->InsertNextPoint(leftMark[i].X,leftMark[i].Y,leftMark[i].Z);
		for (int i = 0; i < frontMark.size() / 2; i++)
			frontNleft->InsertNextPoint(frontMark[i].X, frontMark[i].Y, frontMark[i].Z);
		for (int i = frontMark.size() / 2; i < frontMark.size(); i++)
			frontNright->InsertNextPoint(frontMark[i].X, frontMark[i].Y, frontMark[i].Z);
		for (int i = 0; i < rightMark.size(); i++)
			rightPts->InsertNextPoint(rightMark[i].X, rightMark[i].Y, rightMark[i].Z);
		
		for (int i = 0; i < leftMark.size(); i++)
		{
			std::cout << "left "		<<leftMark[i].X << " " << leftMark[i].Y << " " << leftMark[i].Z << "\n";
			std::cout << "frontNleft "	<< frontMark[i].X << " " << frontMark[i].Y << " " << frontMark[i].Z << "\n";
		}
		vtkLandmarkTransform* left2front = vtkLandmarkTransform::New();
		left2front->SetSourceLandmarks(leftPts);
		left2front->SetTargetLandmarks(frontNleft);
		left2front->SetModeToRigidBody();
		left2front->Update(); //should this be here?


		vtkLandmarkTransform*right2front = vtkLandmarkTransform::New();
		right2front->SetSourceLandmarks(rightPts);
		right2front->SetTargetLandmarks(frontNright);
		right2front->SetModeToRigidBody();
		right2front->Update(); //should this be here?


		vtkAppendPolyData *leftpoly = vtkAppendPolyData::New();
		vtkAppendPolyData *frontpoly = vtkAppendPolyData::New();
		vtkAppendPolyData *rightpoly = vtkAppendPolyData::New();

		
		for (int i = 0; i < 5; i++)leftpoly->AddInputData(left->GetPolyDataAt(i));
		for (int i = 0; i < 5; i++)frontpoly->AddInputData(front->GetPolyDataAt(i));
		for (int i = 0; i < 5; i++)rightpoly->AddInputData(right->GetPolyDataAt(i));
		

		frontpoly->Update();
		rightpoly->Update();
		leftpoly->Update();
		vtkMatrix4x4 *mat = vtkMatrix4x4::New();
		mat = left2front->GetMatrix();

		std::cout << *mat <<"\n";
		std::cout << "left의 cell의 갯수는" << leftpoly->GetOutput()->GetNumberOfCells() << "\n";
	

		
		vtkTransformPolyDataFilter *leftFilt = vtkTransformPolyDataFilter::New();
		leftFilt->SetInputData(leftpoly->GetOutput());
		leftFilt->SetTransform(left2front);
		leftFilt->Update();
		
		std::cout << "1";
		vtkTransformPolyDataFilter *rightFilt = vtkTransformPolyDataFilter::New();
		rightFilt->SetInputData(rightpoly->GetOutput());
		rightFilt->SetTransform(right2front);
		rightFilt->Update();

		std::cout << "2";

		resultMesh->GetPolyDataAt(0)->DeepCopy(leftFilt->GetOutput());
		resultMesh->GetPolyDataAt(1)->DeepCopy(frontpoly->GetOutput());
		resultMesh->GetPolyDataAt(2)->DeepCopy(rightFilt->GetOutput());



		registration(leftPts, frontNleft, frontNright, rightPts);

		rightFilt->Delete();
		leftFilt->Delete();
		leftpoly->Delete();
		frontpoly->Delete();
		rightpoly->Delete();
		right2front->Delete();
		leftPts->Delete();
		rightPts->Delete();
		frontNleft->Delete();
		frontNright->Delete();
		left2front->Delete();
		leftMark.clear(); 
		frontMark.clear();
		rightMark.clear();

	
	}
}

std::vector<double3> AlignModule::extractLandMark(vtkRenderer *rend)
{
	std::vector<double3>vec;
	if (rend == NULL)return vec;

	vtkActorCollection * actorCol = rend->GetActors();
	actorCol->InitTraversal();

	for (vtkIdType i = 0; i < actorCol->GetNumberOfItems(); i++)
	{
		vtkActor *nextActor = actorCol->GetNextActor();
		
		if (i >= 5)//나머지 0~4는 그림임 그림
		{

			double *pos = nextActor->GetCenter();
			std::cout << "찍은거 읽어서 "<<pos[0] << " " << pos[1] << " " << pos[2] << "\n";

			vec.push_back(double3(pos[0], pos[1], pos[2]));
		}
	}

	return vec;

}


void Copy1(MeshPreview* src, MeshPreview* des)
{
	if (des != NULL)
	{
		des->ReleaseModel();
	}

	des->CreateModel("", 0);

	for (int i = 0; i < 5; i++)
	{
		des->m_PolyData[i]->DeepCopy(src->GetPolyDataAt(i));
	}

	des->GetRenderer()->Modified();
	des->GetRenderWindow()->Render();
}


void AlignModule::setRight(MeshPreview *rend)
{
	Copy1(rend, right);
	rightStyle->setRadis(right->GetActorAt(0));
}

void AlignModule::setLeft(MeshPreview *rend)
{
	//front = rend;
	//left = rend;
	Copy1(rend, left);
	leftStyle->setRadis(left->GetActorAt(0));
}

void AlignModule::setFront(MeshPreview *rend)
{
	//front = rend;
	//left = rend;
	//frontStyle->setRadis(rend->GetActorAt(0));
	Copy1(rend, front);
	frontStyle->setRadis(front->GetActorAt(0));
}