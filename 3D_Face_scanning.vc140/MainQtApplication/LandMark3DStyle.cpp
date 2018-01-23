#pragma once
#include<LandMark3DStyle.h>
vtkStandardNewMacro(LandMark3DStyle);

void LandMark3DStyle::OnLeftButtonUp()
{
	std::cout << "I am called";
	if(!(markedPoint == PointXYZR(0, 0, 0)) && indexToMove>=0)
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();
		Picking picker;
		picker.getPicker()->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
		double* pos = picker.getPicker()->GetPickPosition();
		
		locLandMark[indexToMove].upDataActor(this->GetDefaultRenderer(), PointXYZR(pos[0], pos[1], pos[2]));
	}

	vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
	
}

void LandMark3DStyle::OnLeftButtonDown()
{
	int* clickPos = this->GetInteractor()->GetEventPosition();
	Picking picker;
	picker.getPicker()->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
	double* pos = picker.getPicker()->GetPickPosition();
	int mode = 2;

	for (int i=0;i<locLandMark.size();i++)
	{
		std::cout << "I give"<<" "<< locLandMark[i].getPoint()<<"\n";
		if (locLandMark[i].getPoint() == PointXYZR(pos[0], pos[1], pos[2], 0.0))
		{
			mode = 1;//color the mark
			indexToMove=i;
		}
	}
	

	if (mode==1) //색칠하기 
	{
		if (LastPickedActor)
			this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);
	
		this->LastPickedActor = picker.getPicker()->GetActor();
		if (this->LastPickedActor)
		{
			this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());
			this->LastPickedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
			this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
			this->LastPickedActor->GetProperty()->SetSpecular(0.0);
		}

		markedPoint.Set(pos[0], pos[1], pos[2], 0);
	}

	else if (mode==2) //그리기
	{
		std::cout << "Picked actor: " << picker.getPicker()->GetActor() << std::endl;
		//Create a sphere

		picker.getsphereSource()->SetCenter(pos[0], pos[1], pos[2]);
		double rad = 2.5;
		picker.getsphereSource()->SetRadius(rad);
		picker.SetPoint(PointXYZR(pos[0], pos[1], pos[2], rad));

		//Create a mapper and actor
		picker.getMapper()->SetInputConnection(picker.getsphereSource()->GetOutputPort());
		picker.getActor()->SetMapper(picker.getMapper());
		picker.getActor()->GetProperty()->SetColor(0, 0, 1);

		this->GetDefaultRenderer()->AddActor(picker.getActor());//Rendering

		if (!picker.IsUseless())
			locLandMark.push_back(picker);
		for (auto itr : locLandMark)
			std::cout << itr.getPoint() << "\n";
	}
	
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}
void LandMark3DStyle::OnKeyPress()
{
	std::string PressedKey = this->Interactor->GetKeySym();
	if (PressedKey == "Delete")
	{
		if ((markedPoint.X == 0 && markedPoint.Y == 0 && markedPoint.Z == 0) || locLandMark.size() == 0){/*Do nothing*/}

		else
		{
			for (int i = 0; i < locLandMark.size(); i++)
			{
				if (locLandMark[i].getPoint() == markedPoint)
				{
					locLandMark[i].removeActor(this->GetDefaultRenderer());
					locLandMark.erase(locLandMark.begin() + i);
					this->GetDefaultRenderer()->Render();
					this->Modified();
					markedPoint = PointXYZR(0, 0, 0, 0);
					break;
				}
			}

			if (locLandMark.size() <= 0)LastPickedActor = NULL;
			else LastPickedActor = locLandMark[locLandMark.size() - 1].getActor();
		}
	}
	this->Modified();
	vtkInteractorStyleTrackballCamera::OnKeyPress();
}