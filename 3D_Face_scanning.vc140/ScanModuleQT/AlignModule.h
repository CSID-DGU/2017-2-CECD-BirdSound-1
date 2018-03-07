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
//#include"vtkMatrix4x4.h"

#include"MeshPreview.h"
#include"vtkAssembly.h"
enum { LEFT, FRONT, RIGHT };
class AlignModule
{
private:
	MeshPreview *left;
	MeshPreview *front;
	MeshPreview *right;

public:
	AlignModule()
	{
		left = front = right = nullptr;
	}
	void align();
	void mergeActors(MeshPreview *mesh, int place);
	//void registeration();
	std::vector<double3> extractLandMark(vtkRenderer *rend, int flag);
	void setRight(MeshPreview *rend);
	void setFront(MeshPreview *rend);
	void setLeft(MeshPreview *rend);
};
