#pragma once
#include<LandMarkInteractorStyle.h>

vtkStandardNewMacro(LandMarkInteractorStyle);

void LandMarkInteractorStyle::OnLeftButtonUp()
{

	int* clickPos = this->GetInteractor()->GetEventPosition();
	picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());


	if (LastPickedActor != NULL && mainActor != NULL && LastPickedActor != mainActor[0]
		&& LastPickedActor != mainActor[1] && LastPickedActor != mainActor[2] && 
		LastPickedActor != mainActor[3] && LastPickedActor != mainActor[4])
	{
		vtkMapper *mapperMove = LastPickedActor->GetMapper();
		vtkSphereSource *sp = vtkSphereSource::New();

		double* pos = picker->GetPickPosition();
		this->GetDefaultRenderer()->RemoveActor(LastPickedActor);
		sp->SetCenter(pos[0], pos[1], pos[2]);
		sp->SetRadius(radius);
		mapperMove->SetInputConnection(sp->GetOutputPort());

		LastPickedActor->SetMapper(mapperMove);
		this->GetDefaultRenderer()->AddActor(LastPickedActor);
		this->Modified();

	}

	vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
	this->SetMotionFactor(1);
}


/* mainActor을 제외한 모든 actor을 지운다.  */
void LandMarkInteractorStyle::Reset()
{
	vtkActorCollection * actorCol = NULL;

	if (this->GetDefaultRenderer())
		actorCol = this->GetDefaultRenderer()->GetActors();


	if (actorCol)
	{
		actorCol->InitTraversal();
		const int loopSIZE = actorCol->GetNumberOfItems();
		vtkActor *nextActor;

		std::cout << loopSIZE << "\n";
		for (vtkIdType i = 0; i<loopSIZE; i++)
		{
			nextActor = actorCol->GetNextActor();
			std::cout << i << "@#!@#!@#\n";
			if (i >= 5)
			{
				std::cout << "deleted" << " " << i << "\n";
				this->GetDefaultRenderer()->RemoveActor(nextActor);
				nextActor->GetMapper()->Delete();
				nextActor->Delete();
				nextActor = NULL;

			}
		}
	}

	if (LastPickedActor)
	{
		//LastPickedActor->Delete();위에 모든 actor을 지우면서 lastPicked Actor을 이미 지워짐.
		LastPickedActor = NULL;
	}

	if (this->GetDefaultRenderer() != NULL)
	{
		this->GetDefaultRenderer()->Modified();
		this->GetDefaultRenderer()->GetRenderWindow()->Render();
	}

}

void LandMarkInteractorStyle::initialize()
{
	LastPickedActor = NULL;
	LastPickedProperty = vtkProperty::New();
	pointPicker->SetTolerance(0.01);
}

void LandMarkInteractorStyle::OnLeftButtonDown()
{
	int* clickPos = this->GetInteractor()->GetEventPosition();

	picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

	vtkActor* temp = picker->GetActor();
	double* pos = picker->GetPickPosition();

	int mode = 1;

	for (int i = 0; i < 5; i++)
	{
		if (mainActor[i] == temp)
		{
			mode = 2;
			break;
		}
	}


	if (mode == 1) //색칠하기 
	{
		if (LastPickedActor)this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);

		this->LastPickedActor = picker->GetActor();
		if (this->LastPickedActor)
		{
			this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());
			this->LastPickedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
			this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
			this->LastPickedActor->GetProperty()->SetSpecular(0.0);
		}
	}

	else if (mode == 2) //그리기
	{
		
		pointPicker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
		pos = pointPicker->GetPickPosition();

		vtkSphereSource *sp = vtkSphereSource::New();
		sp->SetCenter(pos[0], pos[1], pos[2]);
		sp->SetRadius(radius);

		std::cout <<"점 찍어서"<< pos[0] << " " << pos[1] << " " << pos[2] << "\n";
		vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();

		mapper->SetInputConnection(sp->GetOutputPort());

		vtkActor* actor = vtkActor::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor(0, 0, 1);

		if (pos[0] == 0 || pos[1] == 0 || pos[2] == 0)
		{
			sp->Delete();
			mapper->Delete();
			actor->Delete();
		}
		else this->GetDefaultRenderer()->AddActor(actor);//Rendering
	}

	this->Modified();
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	this->SetMotionFactor(0);
}

void LandMarkInteractorStyle::OnKeyPress()
{
	std::string PressedKey = this->Interactor->GetKeySym();

	if (PressedKey == "Delete" && LastPickedActor != NULL)//LastPickedActor가 삭제된다. 
	{
		//vtkPolyData* data=LastPickedActor->GetMapper()->GetInput()->deepCopy;
		LastPickedActor->GetMapper()->Delete();
		this->GetDefaultRenderer()->RemoveActor(LastPickedActor);
		LastPickedActor->Delete();
		this->GetDefaultRenderer()->Render();
		LastPickedActor = NULL;
	}

	this->GetDefaultRenderer()->GetRenderWindow()->Render();
	vtkInteractorStyleTrackballCamera::OnKeyPress();
}
