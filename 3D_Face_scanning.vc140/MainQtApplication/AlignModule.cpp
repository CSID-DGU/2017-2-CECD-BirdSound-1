
#include"AlignModule.h"

vtkRenderer* left;
vtkRenderer* front;
vtkRenderer* right;

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

		leftMark = extractLandMark(left,LEFT);
		frontMark = extractLandMark(front,FRONT);
		rightMark = extractLandMark(right,RIGHT);


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

	
		leftActor->SetUserTransform(landmarkTransform);
		/*
		
		*/



		vtkRenderer*renderer = vtkRenderer::New();

		vtkRenderWindow*renderWindow = vtkRenderWindow::New();
		renderWindow->AddRenderer(renderer);
		vtkRenderWindowInteractor*renderWindowInteractor = vtkRenderWindowInteractor::New();
		renderWindowInteractor->SetRenderWindow(renderWindow);

		// Add the actor to the scene
		renderer->AddActor(leftActor);
		renderer->AddActor(frontActor);


		// Render and interact
		renderWindow->Render();
		renderWindowInteractor->Start();
	}

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
		if (i == 0)
		{
			if (flag == LEFT)leftActor = nextActor;
			if (flag == RIGHT)rightActor = nextActor;
			if (flag == FRONT)frontActor = nextActor;
		}
		if (i >= 1)
		{
			
			double *pos = nextActor->GetCenter();
			std::cout << pos[0] << " " << pos[1] << " " << pos[2] << "\n";

			vec.push_back(double3(pos[0], pos[1], pos[2]));
		}
	}

	return vec;

}
void AlignModule::setRight(vtkRenderer *rend)
{
	right = rend;
}
void AlignModule::setFront(vtkRenderer *rend)
{
	front = rend;
}
void AlignModule::setLeft(vtkRenderer *rend)
{
	left = rend;
}