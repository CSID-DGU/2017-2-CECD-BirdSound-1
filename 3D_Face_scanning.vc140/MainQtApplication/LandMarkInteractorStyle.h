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

class double3
{
public:
	double X, Y, Z;
	double3(double _X, double _Y, double _Z):X(_X), Y(_Y), Z(_Z){}

	friend std::ostream &operator<<(std::ostream &os, const double3& value)
	{
		os << value.X << " " << value.Y << " " << value.Z;
		return os;
	}

};
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
	void Delete();
	void Reset();
	void setRadis(vtkActor *_mainActor)
	{
		double *bound= _mainActor->GetBounds();
		double row = bound[1] - bound[0];
		double col = bound[3] - bound[2];
		double retv = (row)*(col);//*(bound[5]-bound[4]);

		if (row >= 1 && col >= 1) 
		{
			retv /= bound[1];
			retv /= bound[3];
			retv /= 1.2;
		}

		else retv /= 30;
		
		radius = abs(retv);
		for (int i = 0; i < 6; i++)
			std::cout << bound[i] << " ";

		mainActor = _mainActor;
		std::cout << radius << "\n";
	}

	std::vector<double3> getData();
private:
	vtkActor*				LastPickedActor=NULL;
	vtkActor*				mainActor = NULL;
	vtkProperty*			LastPickedProperty = NULL;
	vtkPropPicker *picker = vtkPropPicker::New();
	double					radius;
};
#endif