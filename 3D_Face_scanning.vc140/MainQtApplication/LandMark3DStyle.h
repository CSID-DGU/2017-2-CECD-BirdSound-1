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

#include<vtkInteractorStyleImage.h>
#include <vector>

class PointXYZR
{
public:
	double X, Y, Z;
	double R=0.0;
	PointXYZR() 
	{
		X = Y = Z = 0.0;
	}
	PointXYZR(double _x, double _y, double _z,double _rad) :X(_x), Y(_y), Z(_z), R(_rad) {}
	//PointXYZR(double *points, double _rad) :X(points[0]), Y(points[1]), Z(points[2]), R(_rad){}
	PointXYZR(double _x, double _y, double _z) :X(_x), Y(_y), Z(_z){}
	PointXYZR(double points[],double _rad)
	{
		X = points[0];
		Y = points[1];
		Z = points[2];
		R = _rad;
	}
	void Set(double _x, double _y, double _z)
	{
		X = _x; Y = _y; Z = _z;
	}
	void Set(double _x, double _y, double _z, double _rad)
	{
		X = _x; Y = _y; Z = _z; R = _rad;
	}
	void Set(double points[], double _rad = 0.0f)
	{
		X = points[0];
		Y = points[1];
		Z = points[2];
		R = 0.0f;
	}
	friend bool operator==(PointXYZR &circle, PointXYZR &point)
	{
	/*	std::cout << circle.X << " " << circle.Y << " " << circle.Z << "\n";
		std::cout << point.X << " " << point.Y << " " << point.Z << "\n";*/
		if (point.R == 0)
		{
			double _X = (circle.X - point.X)*(circle.X - point.X);
			double _Y = (circle.Y - point.Y)*(circle.Y - point.Y);
			double _Z = (circle.Z - point.Z)*(circle.Z - point.Z);

			/*std::cout << "XYZ " << _X << " " << _Y << " " << _Z << "\n";
			std::cout << "Sum " << _X + _Y + _Z << " " << circle.R << "\n";*/
			if (_X + _Y + _Z <= 2.5*circle.R)return true;
			else return false;
		}

		else
		{
		/*	std::cout << "inverse";*/
			double _X = (circle.X - point.X)*(circle.X - point.X);
			double _Y = (circle.Y - point.Y)*(circle.Y - point.Y);
			double _Z = (circle.Z - point.Z)*(circle.Z - point.Z);

			/*std::cout << "XYZ " << _X << " " << _Y << " " << _Z << "\n";
			std::cout << "Sum " << _X + _Y + _Z << " " << circle.R << "\n";*/
			if (_X + _Y + _Z <= 2.5*point.R)return true;
			else return false;
		}
	}

	friend std::ostream &operator<<(std::ostream &os, PointXYZR &point)
	{
		os << point.X << " " << point.Y << " " << point.Z;
		return os;
	}
};

class Picking
{
private:
	PointXYZR point;
	vtkActor *actor;
	vtkPolyDataMapper *mapper;
	vtkPropPicker *picker;
	vtkSphereSource* sphereSource;

public:
	PointXYZR getPoint()						{return point;}
	void  SetPoint(PointXYZR _point)			{ point=_point; }

	vtkActor* getActor()						{return actor;}
	void  SetActor(vtkActor* _actor)			{ actor = _actor; }

	vtkPolyDataMapper* getMapper()				{return mapper;}
	void  SetMapper(vtkPolyDataMapper* _mapper) { mapper = _mapper; }

	vtkPropPicker *getPicker()					{return picker;}
	void  SetPicker(vtkPropPicker* _picker)		{ picker = _picker; }

	vtkSphereSource* getsphereSource()			{return sphereSource;}
	void  SetSphere(vtkSphereSource*  _shpere)	{sphereSource = _shpere; }

public:
	Picking()
	{
		actor = vtkActor::New();
		mapper = vtkPolyDataMapper::New();
		picker = vtkPropPicker::New();
		sphereSource = vtkSphereSource::New();
	}

	void Delete()
	{
		actor->Delete();
		mapper->Delete();
		picker->Delete();
		sphereSource->Delete();
	}
	void upDataActor(vtkRenderer *render, PointXYZR _point)
	{
		render->RemoveActor(actor);
		sphereSource->SetCenter(_point.X, _point.Y, _point.Z);
		sphereSource->SetRadius(point.R);
		point.Set(_point.X, _point.Y, _point.Z);
		
		mapper->SetInputConnection(sphereSource->GetOutputPort());
		actor->SetMapper(mapper);
		render->AddActor(actor);
	}
	void removeActor(vtkRenderer *render)
	{
		render->RemoveActor(actor);
		Delete();
	}
	void Render(vtkRenderer *render)
	{
		render->Render();
	}

	bool IsUseless()
	{
		if (point.X == 0 && point.Y == 0 && point.Z == 0)return true;
		else return false;
	}
};

class LandMark3DStyle : public vtkInteractorStyleTrackballCamera
{
public: 
	LandMark3DStyle()		{initialize();}

	~LandMark3DStyle()
	{
		for (int i = 0; i < locLandMark.size(); i++)
			locLandMark[i].Delete();
		locLandMark.clear();
	}
	
	static LandMark3DStyle* New();
	vtkTypeMacro(LandMark3DStyle, vtkInteractorStyleTrackballCamera);
	virtual void OnLeftButtonDown();
	virtual void OnKeyPress();
	virtual void OnLeftButtonUp();

	void initialize()
	{
		LastPickedActor = NULL;
		LastPickedProperty = vtkProperty::New();
	}

private:
	
	std::vector<Picking> locLandMark;
	PointXYZR	markedPoint;
	vtkActor    *LastPickedActor;
	vtkProperty *LastPickedProperty;
	int			indexToMove=-1;
};
#endif