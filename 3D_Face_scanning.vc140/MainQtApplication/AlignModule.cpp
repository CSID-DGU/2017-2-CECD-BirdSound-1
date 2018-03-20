
#include"AlignModule.h"

vtkAssembly* leftActor;
vtkAssembly* frontActor;
vtkAssembly* rightActor;

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

void AlignModule::mergeActors(MeshPreview *mesh,int place)
{
	vtkSmartPointer<vtkAssembly> assembly =vtkSmartPointer<vtkAssembly>::New();
	
	
	for (int i = 0; i < 5; i++)
	{
		assembly->AddPart(mesh->GetActorAt(i));
	}
	/*meshPreviewer에 있는*/
	if (place == LEFT)
		leftActor = assembly;
	else if (place == RIGHT)
		rightActor = assembly;
	else if (place == FRONT)
		frontActor = assembly;

}
void AlignModule::registration()
{


//	vtkSmartPointer<vtkIterativeClosestPointTransform> icp =vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
//	icp->SetSource(source);
//	icp->SetTarget(target);
//	icp->GetLandmarkTransform()->SetModeToRigidBody();
//	icp->SetMaximumNumberOfIterations(20);
//	//icp->StartByMatchingCentroidsOn();
//	icp->Modified();
//	icp->Update();
//
//	// Get the resulting transformation matrix (this matrix takes the source points to the target points)
//	vtkSmartPointer<vtkMatrix4x4> m = icp->GetMatrix();
//	std::cout << "The resulting matrix is: " << *m << std::endl;
//
//	// Transform the source points by the ICP solution
//	vtkSmartPointer<vtkTransformPolyDataFilter> icpTransformFilter =
//		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
//#if VTK_MAJOR_VERSION <= 5
//	icpTransformFilter->SetInput(source);
//#else
//	icpTransformFilter->SetInputData(source);
//#endif
//	icpTransformFilter->SetTransform(icp);
//	icpTransformFilter->Update();
//
//	/*
//	// If you need to take the target points to the source points, the matrix is:
//	icp->Inverse();
//	vtkSmartPointer<vtkMatrix4x4> minv = icp->GetMatrix();
//	std::cout << "The resulting inverse matrix is: " << *minv << std::cout;
//	*/
//
//	// Visualize
//	vtkSmartPointer<vtkPolyDataMapper> sourceMapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//#if VTK_MAJOR_VERSION <= 5
//	sourceMapper->SetInputConnection(source->GetProducerPort());
//#else
//	sourceMapper->SetInputData(source);
//#endif
//
//	vtkSmartPointer<vtkActor> sourceActor =
//		vtkSmartPointer<vtkActor>::New();
//	sourceActor->SetMapper(sourceMapper);
//	sourceActor->GetProperty()->SetColor(1, 0, 0);
//	sourceActor->GetProperty()->SetPointSize(4);
//
//	vtkSmartPointer<vtkPolyDataMapper> targetMapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//#if VTK_MAJOR_VERSION <= 5
//	targetMapper->SetInputConnection(target->GetProducerPort());
//#else
//	targetMapper->SetInputData(target);
//#endif
//
//	vtkSmartPointer<vtkActor> targetActor =
//		vtkSmartPointer<vtkActor>::New();
//	targetActor->SetMapper(targetMapper);
//	targetActor->GetProperty()->SetColor(0, 1, 0);
//	targetActor->GetProperty()->SetPointSize(4);
//
//	vtkSmartPointer<vtkPolyDataMapper> solutionMapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//	solutionMapper->SetInputConnection(icpTransformFilter->GetOutputPort());
//
//	vtkSmartPointer<vtkActor> solutionActor =
//		vtkSmartPointer<vtkActor>::New();
//	solutionActor->SetMapper(solutionMapper);
//	solutionActor->GetProperty()->SetColor(0, 0, 1);
//	solutionActor->GetProperty()->SetPointSize(3);
//
//	// Create a renderer, render window, and interactor
//	vtkSmartPointer<vtkRenderer> renderer =
//		vtkSmartPointer<vtkRenderer>::New();
//	vtkSmartPointer<vtkRenderWindow> renderWindow =
//		vtkSmartPointer<vtkRenderWindow>::New();
//	renderWindow->AddRenderer(renderer);
//	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();
//	renderWindowInteractor->SetRenderWindow(renderWindow);
//
//	// Add the actor to the scene
//	renderer->AddActor(sourceActor);
//	renderer->AddActor(targetActor);
//	renderer->AddActor(solutionActor);
//	renderer->SetBackground(.3, .6, .3); // Background color green
//
//										 // Render and interact
//	renderWindow->Render();
//	renderWindowInteractor->Start();
//
	//return EXIT_SUCCESS;

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
		vtkPoints*frontPtsHead = vtkPoints::New();
		vtkPoints*frontPtsTail = vtkPoints::New();

		for (int i = 0; i < leftMark.size(); i++)
			leftPts->InsertNextPoint(leftMark[i].getData());

		for (int i = 0; i < frontMark.size()/2; i++)
			frontPtsHead->InsertNextPoint(frontMark[i].getData());

		for (int i = frontMark.size() / 2; i < frontMark.size(); i++)
			frontPtsTail->InsertNextPoint(frontMark[i].getData());
	
		for (int i = 0; i < rightMark.size(); i++)
			rightPts->InsertNextPoint(rightMark[i].getData());
		
		std::cout << "leftMark\n";
		for (int i = 0; i < leftMark.size(); i++)
			std::cout << leftMark[i] << " ";
		std::cout << "\n";

		std::cout << "frontMark he\n";
		for (int i = 0; i < frontMark.size()/2; i++)
			std::cout << frontMark[i] << " ";
		std::cout << "\n";

		std::cout << "frontMark ta\n";
		for (int i = frontMark.size()/2; i < frontMark.size(); i++)
			std::cout << frontMark[i] << " ";
		std::cout << "\n";

		std::cout << "rightMark\n";
		for (int i = 0; i < rightMark.size(); i++)
			std::cout << rightMark[i] << " ";
		std::cout << "\n";


		/*if (leftMark.size() != 3 || rightMark.size() != 3 || frontPtsHead->GetNumberOfPoints() != 3 || frontPtsTail->GetNumberOfPoints() != 3)
		{
			std::cout << "3개씩 넣어요";
			return;
		}*/

		vtkLandmarkTransform*landmarkTransform = vtkLandmarkTransform::New();
		landmarkTransform->SetSourceLandmarks(frontPtsHead);
		landmarkTransform->SetTargetLandmarks(leftPts);
		landmarkTransform->SetModeToRigidBody();
		landmarkTransform->Update(); //should this be here?


		vtkLandmarkTransform*landmarkTransform2 = vtkLandmarkTransform::New();
		landmarkTransform2->SetSourceLandmarks(frontPtsTail);
		landmarkTransform2->SetTargetLandmarks(rightPts);
		landmarkTransform2->SetModeToRigidBody();
		landmarkTransform2->Update(); //should this be here?


		vtkAppendPolyData *leftpoly = vtkAppendPolyData::New();
		vtkAppendPolyData *frontpoly = vtkAppendPolyData::New();
		vtkAppendPolyData *rightpoly = vtkAppendPolyData::New();

		
		for (int i = 0; i < 5; i++)leftpoly->AddInputData(left->m_PolyData[i]);
		for (int i = 0; i < 5; i++)frontpoly->AddInputData(front->GetPolyDataAt(i));
		for (int i = 0; i < 5; i++)rightpoly->AddInputData(right->GetPolyDataAt(i));
		

		frontpoly->Update();
		rightpoly->Update();
		leftpoly->Update();
		std::cout << "left의 cell의 갯수는" << leftpoly->GetOutput()->GetNumberOfCells() << "\n";
	

		
		vtkTransformPolyDataFilter *leftFilt = vtkTransformPolyDataFilter::New();
		leftFilt->SetInputData(leftpoly->GetOutput());
		leftFilt->SetTransform(landmarkTransform);
		leftFilt->Update();

		vtkTransformPolyDataFilter *rightFilt = vtkTransformPolyDataFilter::New();
		rightFilt->SetInputData(rightpoly->GetOutput());
		rightFilt->SetTransform(landmarkTransform2);
		rightFilt->Update();


		/*vtkAppendPolyData *res = vtkAppendPolyData::New();
		res->AddInputData(leftFilt->GetOutput());
		res->AddInputData(frontpoly->GetOutput());
		res->AddInputData(rightFilt->GetOutput());
		res->Update();*/



		resultMesh->GetPolyDataAt(0)->DeepCopy(leftFilt->GetOutput());
		resultMesh->GetPolyDataAt(1)->DeepCopy(frontpoly->GetOutput());
		resultMesh->GetPolyDataAt(2)->DeepCopy(rightFilt->GetOutput());


		resultMesh->GetRenderWindow()->Modified();
		resultMesh->GetRenderWindow()->Render();
		resultMesh->GetRenderWindow()->Start();



	
		rightFilt->Delete();
		leftFilt->Delete();
		leftpoly->Delete();
		frontpoly->Delete();
		rightpoly->Delete();
		landmarkTransform->Delete();
		leftPts->Delete();
		rightPts->Delete();
		frontPtsHead->Delete();
		frontPtsTail->Delete();
		landmarkTransform2->Delete();
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
			std::cout << pos[0] << " " << pos[1] << " " << pos[2] << "\n";

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
		//des->m_Mapper[i]->ShallowCopy(src->GetMapperAt(i));
		//des->m_Actor[i]->ShallowCopy(src->GetActorAt(i));
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