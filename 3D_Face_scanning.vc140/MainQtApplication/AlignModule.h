#pragma once
#include"vtkRenderer.h"
#include"vtkActor.h"
#include<vector>
#include"vtkLandmarkTransform.h"
#include"vtkPoints.h"
#include"vtkPolyData.h"
#include"vtkVertexGlyphFilter.h"
#include"vtkPolyDataMapper.h"
#include"vtkTransformPolyDataFilter.h"
#include"vtkProperty.h"
#include"vtkPolyDataMapper.h"
#include"vtkRenderWindow.h"
#include"vtkRenderWindowInteractor.h"
#include"double3.h"
#include"vtkMatrix4x4.h"

enum { LEFT, FRONT, RIGHT };
class AlignModule
{
private:
	vtkRenderer* left;
	vtkRenderer* front;
	vtkRenderer* right;

	vtkActor* leftActor;
	vtkActor* frontActor;
	vtkActor* rightActor;
public:
	AlignModule()
	{
		left = front = right = nullptr;
		leftActor = frontActor = rightActor = nullptr;
	}
	void align();
	std::vector<double3> extractLandMark(vtkRenderer *rend, int flag);
	void setRight(vtkRenderer *rend);
	void setFront(vtkRenderer *rend);
	void setLeft(vtkRenderer *rend);
};
