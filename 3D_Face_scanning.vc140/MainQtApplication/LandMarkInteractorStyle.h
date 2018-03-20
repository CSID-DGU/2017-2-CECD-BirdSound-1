#pragma once
#ifndef LandMarkInteractorStyle_H
#define LandMarkInteractorStyle_H

#include <vtkRendererCollection.h>
#include <vtkWorldPointPicker.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include<vtkProperty.h>
#include<vtkPropPicker.h>
#include<vtkPolyDataMapper.h>
#include<vector>
#include<vtkActorCollection.h>
#include"double3.h"


class LandMarkInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public: 
	LandMarkInteractorStyle()
	{
		initialize();
	}

	static LandMarkInteractorStyle* New();
	vtkTypeMacro(LandMarkInteractorStyle, vtkInteractorStyleTrackballCamera);
	virtual void OnLeftButtonDown();
	virtual void OnKeyPress();
	virtual void OnLeftButtonUp();
	void initialize();
	void Reset();
	void setMainActors(std::vector<vtkActor*> actor)
	{
		for (int i = 0; i < 5; i++)
			mainActor[i] = actor[i];
	}
	void setRadis(vtkActor *_mainActor)
	{
		double *bound= _mainActor->GetBounds();
		double row = bound[1] - bound[0];
		double col = bound[3] - bound[2];
		double retv = (row)*(col);//*(bound[5]-bound[4]);

		std::cout << retv << " ";
		if (row >= 1 && col >= 1) 
		{
			retv /= bound[1];
			retv /= bound[3];
		}

		else retv /= 10;
		
		radius = abs(retv);
		std::cout << radius << "\n";
	}

private:
	vtkActor*				LastPickedActor=NULL;
	vtkActor*				mainActor[5];
	vtkProperty*			LastPickedProperty = NULL;
	vtkPropPicker *picker = vtkPropPicker::New();
	double					radius;
};
#endif