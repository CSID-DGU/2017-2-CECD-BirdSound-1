
#include"AlignModule.h"

vtkAssembly* leftActor;
vtkAssembly* frontActor;
vtkAssembly* rightActor;

/**
Member 변수에 있는 left, front, right로 Align을 시행하고
결과를 vtkRenderer로 뱉어낸다.
*/
void AlignModule::mergeActors(MeshPreview *mesh,int place)
{
	vtkSmartPointer<vtkAssembly> assembly =vtkSmartPointer<vtkAssembly>::New();
	
	
	for (int i = 0; i < 5; i++)
	{
		assembly->AddPart(mesh->GetActorAt(i));
	}
	/*
	meshPreviewer에 있는 
	*/
	if (place == LEFT)
		leftActor = assembly;
	else if (place == RIGHT)
		rightActor = assembly;
	else if (place == FRONT)
		frontActor = assembly;

}
void AlignModule::align()
{
	if (left == nullptr || front == nullptr || right == nullptr)
	{
		std::cout << "사진 3장 제대로 찍어요\n";
		return;
	}

	else
	{
		std::vector<double3>leftMark;
		std::vector<double3>frontMark;
		std::vector<double3>rightMark;

		leftMark = extractLandMark(left->GetRenderer(), LEFT);
		frontMark = extractLandMark(front->GetRenderer(), FRONT);
		rightMark = extractLandMark(right->GetRenderer(), RIGHT);


		vtkPoints*leftPts = vtkPoints::New();
		vtkPoints*rightPts = vtkPoints::New();
		vtkPoints*frontPts = vtkPoints::New();

		for (int i = 0; i < leftMark.size(); i++)
		{
			leftPts->InsertNextPoint(leftMark[i].getData());
			//rightPts->InsertNextPoint(rightMark[i].getData());
			frontPts->InsertNextPoint(frontMark[i].getData());

			std::cout << (leftMark[i]) << " is left \n";
			std::cout << (frontMark[i]) << "is front \n";

		}



		vtkLandmarkTransform*landmarkTransform = vtkLandmarkTransform::New();
		landmarkTransform->SetSourceLandmarks(frontPts);
		landmarkTransform->SetTargetLandmarks(leftPts);
		landmarkTransform->SetModeToRigidBody();
		landmarkTransform->Update(); //should this be here?


		/*
		이 부분을 getActorAt(0)이 아니고 left assembly로 회전 시켜야한다. 
		*/
		left->GetActorAt(0)->SetUserTransform(landmarkTransform);
		/**/

		vtkRenderer*renderer = vtkRenderer::New();

		vtkRenderWindow*renderWindow = vtkRenderWindow::New();
		renderWindow->AddRenderer(renderer);
		vtkRenderWindowInteractor*renderWindowInteractor = vtkRenderWindowInteractor::New();
		renderWindowInteractor->SetRenderWindow(renderWindow);

		// Add the actor to the scene
		//renderer->AddActor(left->GetActorAt(0));
		//renderer->AddActor(front->GetActorAt(0));
		
		vtkSmartPointer<vtkPropCollection> collection =vtkSmartPointer<vtkPropCollection>::New();
		leftActor->GetActors(collection);
		collection->InitTraversal();
		for (vtkIdType i = 0; i < collection->GetNumberOfItems(); i++)
		{
			renderer->AddActor(collection->GetNextProp());
			//vtkActor::SafeDownCast(collection->GetNextProp())->GetProperty()->SetOpacity(0.5);
		}

		// Render and interact
		renderWindow->Render();
		renderWindowInteractor->Start();










		vtkLandmarkTransform*landmarkTransform2 = vtkLandmarkTransform::New();
		landmarkTransform2->SetSourceLandmarks(frontPts);
		landmarkTransform2->SetTargetLandmarks(rightPts);
		landmarkTransform2->SetModeToRigidBody();
		landmarkTransform2->Update(); //should this be here?


		right->GetActorAt(0)->SetUserTransform(landmarkTransform2);
		/**/

		vtkRenderer*renderer = vtkRenderer::New();

		vtkRenderWindow*renderWindow = vtkRenderWindow::New();
		renderWindow->AddRenderer(renderer);
		vtkRenderWindowInteractor*renderWindowInteractor = vtkRenderWindowInteractor::New();
		renderWindowInteractor->SetRenderWindow(renderWindow);

		// Add the actor to the scene
		//renderer->AddActor(right->GetActorAt(0));
	
		vtkSmartPointer<vtkPropCollection> collection1 = vtkSmartPointer<vtkPropCollection>::New();
		rightActor->GetActors(collection);
		collection1->InitTraversal();
		for (vtkIdType i = 0; i < collection1->GetNumberOfItems(); i++)
		{
			renderer->AddActor(collection1->GetNextProp());
			//vtkActor::SafeDownCast(collection->GetNextProp())->GetProperty()->SetOpacity(0.5);
		}

		// Render and interact
		renderWindow->Render();
		renderWindowInteractor->Start();
	}

	//여기까지가 left, front붙이는것임. 
	//renderWindow를 return한다. 

}

std::vector<double3> AlignModule::extractLandMark(vtkRenderer *rend, int flag)
{
	std::vector<double3>vec;
	if (rend == NULL)return vec;

	vtkActorCollection * actorCol = rend->GetActors();
	actorCol->InitTraversal();

	for (vtkIdType i = 0; i < actorCol->GetNumberOfItems(); i++)
	{
		vtkActor *nextActor = actorCol->GetNextActor();
		/*if (i == 0)
		{
		if (flag == LEFT)leftActor = nextActor;
		if (flag == RIGHT)rightActor = nextActor;
		if (flag == FRONT)frontActor = nextActor;
		}*/
		if (i >= 1)
		{

			double *pos = nextActor->GetCenter();
			std::cout << pos[0] << " " << pos[1] << " " << pos[2] << "\n";

			vec.push_back(double3(pos[0], pos[1], pos[2]));
		}
	}

	return vec;

}
void AlignModule::setRight(MeshPreview *rend)
{
	right = rend;
}
void AlignModule::setFront(MeshPreview *rend)
{
	front = rend;
}
void AlignModule::setLeft(MeshPreview *rend)
{
	left = rend;
}