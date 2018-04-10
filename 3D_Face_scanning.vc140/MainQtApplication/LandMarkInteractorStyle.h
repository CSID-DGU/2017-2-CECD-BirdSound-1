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


#include<vtkPointPicker.h>

#include<vtkCellPicker.h>
#include<vtkSelectionNode.h>
#include<vtkSelection.h>
#include<vtkExtractSelection.h>
#include<vtkUnstructuredGrid.h>
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
	
		if (row < 0)row = -row;
		double retv = row;//*(bound[5]-bound[4]);

		std::cout << retv << " ";
		retv / 25;
		
		radius = 0.005;
		std::cout << radius << "이 원 크기\n";
	}

private:
	vtkActor*				LastPickedActor=NULL;
	vtkActor*				mainActor[5];


	vtkProperty*			LastPickedProperty = NULL;
	vtkCellPicker *picker = vtkCellPicker::New();
	vtkSmartPointer<vtkPointPicker> pointPicker = vtkSmartPointer<vtkPointPicker>::New();
	double					radius;
};
#endif