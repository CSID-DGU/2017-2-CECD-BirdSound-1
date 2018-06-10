
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

	resultMesh = new MeshPreview(15);
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

vtkSmartPointer<vtkPolyData> AlignModule::point2mesh(vtkPoints *pts, vtkMatrix4x4 *Mat)
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

	vtkSmartPointer<vtkTransform>mat2trans= vtkSmartPointer<vtkTransform>::New();
	
	vtkSmartPointer<vtkTransformPolyDataFilter>trans = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	
	mat2trans->SetMatrix(Mat);

	trans->SetTransform(mat2trans);

	trans->SetInputData(poly);
	trans->Modified();

	poly->DeepCopy(trans->GetOutput());
	return poly;
}
void AlignModule::registration(vtkPolyData *left, vtkPolyData *leftFront, vtkPolyData* rightFront, vtkPolyData* right)
{
	//const int alpha = 10;//If alpha big -> too slow
	//vtkSmartPointer<vtkIterativeClosestPointTransform> IcpleftFront =vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	//IcpleftFront->SetSource(left);
	//IcpleftFront->SetTarget(leftFront);
	//IcpleftFront->GetLandmarkTransform()->SetModeToRigidBody();
	//IcpleftFront->SetMaximumNumberOfIterations(alpha);
	////icp->StartByMatchingCentroidsOn();
	//IcpleftFront->Modified();
	//IcpleftFront->Update();

	//vtkSmartPointer<vtkIterativeClosestPointTransform> IcprightFront = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	//IcprightFront->SetSource(right);
	//IcprightFront->SetTarget(rightFront);
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

void AlignModule::slotAlign()
{
	
	if (left == nullptr || front == nullptr || right == nullptr)
	{
		std::cout << "사진 3장 제대로 찍어요\n";
		return;
	}

	else
	{

		vtkCellArray *aqwe = vtkCellArray::New();
		
		vtkIdList*id = vtkIdList::New();
		resultMesh->GetPolyDataAt(0)->GetPolys()->GetCell(1, id);

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

		////////////////////////////////////		////////////////////////////////////
		//resultMesh->GetPolyDataAt(index)->DeepCopy(leftFilt->GetOutput());
		//resultMesh->GetPolyDataAt(index++)->DeepCopy(front->GetPolyDataAt(i));
		int index = 0;
		for (int i = 0; i < 5; i++)resultMesh->GetPolyDataAt(index++)->DeepCopy(left->GetPolyDataAt(i));
		for (int i = 0; i < 5; i++)resultMesh->GetPolyDataAt(index++)->DeepCopy(front->GetPolyDataAt(i));
		for (int i = 0; i < 5; i++)resultMesh->GetPolyDataAt(index++)->DeepCopy(right->GetPolyDataAt(i));

		Pos A(0, 0);
		int base_front = frontMark.size() / 2;
		Pos *tmp0;
		Pos *tmp2;

		std::cout << "\n\n";
		////p.setXYZPoints("No Need");
		p.setXYZPoints(*resultMesh);

		p.setLandmarkLeftFront(
			*XYZ2Index(leftMark[0], LEFT), *XYZ2Index(leftMark[2], LEFT),
			*XYZ2Index(frontMark[0], FRONT), *XYZ2Index(frontMark[2], FRONT));

		p.setLandmarkRightFront(
			*XYZ2Index(rightMark[0], RIGHT), *XYZ2Index(rightMark[2], RIGHT),
			*XYZ2Index(frontMark[0 + base_front], FRONT), *XYZ2Index(frontMark[2 + base_front], FRONT));
		////////////////////////////////////		////////////////////////////////////

	
		vtkSmartPointer<vtkPoints>leftPts = vtkSmartPointer<vtkPoints>::New();
		vtkSmartPointer<vtkPoints>rightPts = vtkSmartPointer<vtkPoints>::New();
		vtkSmartPointer<vtkPoints>frontNleft = vtkSmartPointer<vtkPoints>::New();
		vtkSmartPointer<vtkPoints>frontNright = vtkSmartPointer<vtkPoints>::New();

		for (int i = 0; i < leftMark.size(); i++)
			leftPts->InsertNextPoint(leftMark[i].X,leftMark[i].Y,leftMark[i].Z);
		for (int i = 0; i < frontMark.size() / 2; i++)
			frontNleft->InsertNextPoint(frontMark[i].X, frontMark[i].Y, frontMark[i].Z);
		for (int i = frontMark.size() / 2; i < frontMark.size(); i++)
			frontNright->InsertNextPoint(frontMark[i].X, frontMark[i].Y, frontMark[i].Z);
		for (int i = 0; i < rightMark.size(); i++)
			rightPts->InsertNextPoint(rightMark[i].X, rightMark[i].Y, rightMark[i].Z);
		

		vtkSmartPointer<vtkLandmarkTransform>left2front = vtkSmartPointer<vtkLandmarkTransform>::New();
		left2front->SetSourceLandmarks(leftPts);
		left2front->SetTargetLandmarks(frontNleft);
		left2front->SetModeToRigidBody();
		left2front->Update(); //should this be here?


		vtkSmartPointer<vtkLandmarkTransform>right2front = vtkSmartPointer<vtkLandmarkTransform>::New();
		right2front->SetSourceLandmarks(rightPts);
		right2front->SetTargetLandmarks(frontNright);
		right2front->SetModeToRigidBody();
		right2front->Update(); //should this be here?


		index = 0;
		for (int i = 0; i < 5; i++)resultMesh->m_ImageData[index++]->DeepCopy(left->GetImageData(i));
		for (int i = 0; i < 5; i++)resultMesh->m_ImageData[index++]->DeepCopy(front->GetImageData(i));
		for (int i = 0; i < 5; i++)resultMesh->m_ImageData[index++]->DeepCopy(right->GetImageData(i));
		for (int i = 0; i < 15; i++)resultMesh->m_ImageData[i]->Modified();



		index = 0;
		for (int i = 0; i < 5; i++)
		{
			vtkSmartPointer<vtkTransformPolyDataFilter> leftFilt = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
			leftFilt->SetInputData(left->GetPolyDataAt(i));
			leftFilt->SetTransform(left2front);
			leftFilt->Update();


			vtkSmartPointer<vtkDataArray>coord=setTransformedCord(left->GetPolyDataAt(i), left2front);
			resultMesh->GetPolyDataAt(index)->DeepCopy(leftFilt->GetOutput());
			index++;
			//resultMesh->GetPolyDataAt(index++)->GetPointData()->SetTCoords(coord);
		}
		
		for (int i = 0; i < 5; i++)
			resultMesh->GetPolyDataAt(index++)->DeepCopy(front->GetPolyDataAt(i));

		for (int i = 0; i < 5; i++)
		{
			vtkSmartPointer<vtkTransformPolyDataFilter>rightFilt = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
			rightFilt->SetInputData(right->GetPolyDataAt(i));
			rightFilt->SetTransform(right2front);
			rightFilt->Update();

			vtkSmartPointer<vtkDataArray>coord = setTransformedCord(right->GetPolyDataAt(i), right2front);
			resultMesh->GetPolyDataAt(index)->DeepCopy(rightFilt->GetOutput());
			index++;
			//resultMesh->GetPolyDataAt(index++)->GetPointData()->SetTCoords(coord);
			//resultMesh->GetPolyDataAt(index++)->DeepCopy(rightFilt->GetOutput());
		}

	
		for (int i = 0; i < resultMesh->size; i++)
		{
			resultMesh->GetTextureAt(i)->SetInputData(resultMesh->m_ImageData[i]);
			resultMesh->GetTextureAt(i)->Modified();
			resultMesh->GetActorAt(i)->SetTexture(resultMesh->GetTextureAt(i));
			resultMesh->GetActorAt(i)->Modified();
		}
		//p.writePoints();
		//std::cout << "Init Overlap,ZIppering";
		//p.deleteOverlap();
		//p.zipperMesh();

		/***************************************************/
		for (int i=0;i<15;i++)
		{
			std::cout << "전\t" << resultMesh->GetPolyDataAt(i)->GetNumberOfCells() << "\n";
			for (int j = 0; j < NumCellToRemove; j++)
				RemoveCell(resultMesh->GetPolyDataAt(i), cellToRemove[j]);//ID에 지울 놈들 cell ID 넣기			
			resultMesh->GetPolyDataAt(i)->RemoveDeletedCells();
			std::cout << "후\t" << resultMesh->GetPolyDataAt(i)->GetNumberOfCells() << "\n";
		}
		/***************************************************/


		std::cout << "Saved";
		resultMesh->GetRenderWindow()->Render();
		resultMesh->GetRenderWindow()->Start();
	}
}

void AlignModule::RemoveCell(vtkPolyData *poly, int CellID)
{
	//std::cout << poly->GetNumberOfCells() << "<-전";
	poly->BuildLinks();//<polyData에서 buildLink
	poly->DeleteCell(CellID);//지울 Cell ID
	//std::cout << poly->GetNumberOfCells() << "<-후";
}


vtkSmartPointer<vtkDataArray> AlignModule::setTransformedCord(vtkPolyData *poly, vtkLandmarkTransform *land)
{
	if (land != nullptr) {
		vtkSmartPointer<vtkTransform>trans = vtkSmartPointer<vtkTransform>::New();
		trans->SetMatrix(land->GetMatrix());

	
		vtkSmartPointer<vtkTransformTextureCoords> transCoord = vtkSmartPointer<vtkTransformTextureCoords>::New();
		transCoord->SetInputData(poly);

		transCoord->SetPosition(trans->GetOrientation());
		transCoord->Update();

		//poly->DeepCopy(transCoord->GetOutput());
		return transCoord->GetPolyDataOutput()->GetPointData()->GetTCoords();
		//<--여기서 coord * 4해야되나
		//poly->GetPointData()->SetTCoords(transCoord->GetPolyDataOutput()->GetPointData()->GetTCoords());
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
			vec.push_back(double3(pos[0], pos[1], pos[2]));
		}
	}

	return vec;

}


void AlignModule::Copy(MeshPreview* src, MeshPreview* des)
{
	if (des != NULL)
	{
		des->ReleaseModel();
	}

	des->CreateModel("", 0);
	
	for (int i = 0; i < 5; i++)
	{
		des->m_PolyData[i]->DeepCopy(src->GetPolyDataAt(i));
		des->m_ImageData[i]->DeepCopy(src->m_ImageData[i]);
		des->m_ImageData[i]->Modified();
		des->m_Texture[i]->SetInputData(des->m_ImageData[i]);
		des->GetActorAt(i)->SetTexture(des->m_Texture[i]);
		des->GetTextureAt(i)->Update(); 
		des->GetActorAt(i)->Modified();
	}

	des->GetRenderer()->Modified();
	des->GetRenderWindow()->Render();
}


void AlignModule::setRight(MeshPreview *rend)
{
	Copy(rend, right);
	rightStyle->setRadis(right->GetActorAt(0));
}

void AlignModule::setLeft(MeshPreview *rend)
{
	//front = rend;
	//left = rend;
	Copy(rend, left);
	leftStyle->setRadis(left->GetActorAt(0));
}

void AlignModule::setFront(MeshPreview *rend)
{
	//front = rend;
	//left = rend;
	//frontStyle->setRadis(rend->GetActorAt(0));
	Copy(rend, front);
	frontStyle->setRadis(front->GetActorAt(0));
}
Pos* AlignModule::XYZ2Index(double3 a, int page) {
	/*
	RMS 를 이용하여 최솟값 찾기
	1. PAGE에 따른 최소값 찾아보기 지금 조건문 설정안되어 있음

	*/
	double _t1, _t2, _t3;
	double min_rms;
	int min_rms_idx, min_rms_k;
	double tmp_rms;
	vtkPoints *value[4];
	min_rms = 1.0;
	min_rms_idx = 0;
	int subPOINTS = 0;

	for (int k = 0; k < 4; k++) {
		value[k] = resultMesh->GetPolyDataAt(page * 5 + k)->GetPoints();
		subPOINTS = value[k]->GetNumberOfPoints();
		for (int j = 0; j < subPOINTS; j++)
		{
			_t1 = value[k]->GetPoint(j)[0];
			_t2 = value[k]->GetPoint(j)[1];
			_t3 = value[k]->GetPoint(j)[2];
			tmp_rms = abs(_t1 - a.X) + abs(_t2 - a.Y) + abs(_t3 - a.Z);
			if (tmp_rms < min_rms) {
				min_rms = tmp_rms;
				min_rms_k = k;
				min_rms_idx = j;
			}
		}
	}
	//
	_t1 = value[min_rms_k]->GetPoint(min_rms_idx)[0];
	_t2 = value[min_rms_k]->GetPoint(min_rms_idx)[1];
	_t3 = value[min_rms_k]->GetPoint(min_rms_idx)[2];
	//
	int row = (min_rms_k*subPOINTS + min_rms_idx) % WIDTH;
	int col = (min_rms_k*subPOINTS + min_rms_idx) / WIDTH;
	std::cout << "Find Index\t\t";
	std::cout << "\t" << min_rms << "\n";
	std::cout << "\t" << (_t1) << " " << (_t2) << " " << (_t3) << "\n";
	std::cout << "\t" << (a.X) << " " << (a.Y) << " " << (a.Z) << "\n";
	std::cout << "\n";
	return new Pos(row, col);
}