#pragma once
#ifndef LandMarkInteractorStyle_H
#define LandMarkInteractorStyle_H

#include <vtk-8.1\vtkRendererCollection.h>
#include <vtk-8.1\vtkWorldPointPicker.h>
#include <vtk-8.1\vtkRenderWindow.h>
#include <vtk-8.1\vtkRenderer.h>
#include <vtk-8.1\vtkSphereSource.h>
#include <vtk-8.1\vtkRenderWindowInteractor.h>
#include <vtk-8.1\vtkInteractorStyleTrackballCamera.h>

#include<vtk-8.1\vtkProperty.h>
#include<vtk-8.1\vtkPropPicker.h>
#include<vtk-8.1\vtkPolyDataMapper.h>
#include<vector>
#include<vtk-8.1\vtkActorCollection.h>

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