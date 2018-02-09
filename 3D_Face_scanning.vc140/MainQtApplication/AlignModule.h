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
class AlignModule
{
private:
	vtkRenderer* left;
	vtkRenderer* front;
	vtkRenderer* right;
public:
	AlignModule()
	{
		left = front = right = nullptr;
	}
	void align();
	std::vector<double3> extractLandMark(vtkRenderer *rend);
	void setRight(vtkRenderer *rend);
	void setFront(vtkRenderer *rend);
	void setLeft(vtkRenderer *rend);
};