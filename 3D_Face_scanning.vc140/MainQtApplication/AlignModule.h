#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Align.h"

#include"vtkRenderer.h"
#include"vtkActor.h"
#include<vector>
#include"vtkLandmarkTransform.h"
#include"vtkPoints.h"
#include"vtkPolyData.h"
#include"vtkVertexGlyphFilter.h"


#include"vtkRenderWindow.h"
#include"vtkPolyDataMapper.h"
#include"vtkTransformPolyDataFilter.h"
#include"vtkProperty.h"
#include"vtkPolyDataMapper.h"
#include"vtkRenderWindow.h"
#include"vtkRenderWindowInteractor.h"
#include"double3.h"
//#include"vtkMatrix4x4.h"

#include"MeshPreview.h"

#include"LandMarkInteractorStyle.h"
#include"vtkAppendPolyData.h"
#include"vtkTransformPolyDataFilter.h"
#include"vtkIterativeClosestPointTransform.h"
#include"vtkMatrix4x4.h"
#include"vtkTransform.h"

#include"vtkOBJExporter.h"
#include"vtkPointData.h"
#include"vtkTransformTextureCoords.h"
#include"vtkImageAppend.h"

#include "OverlapZippering.h"
#include"vtkIdList.h"
//이 이하 include는 test용임. 삭제할 것.
#include"vtkImageActor.h"
#include"vtkFloatArray.h"
#include"vtkCellArray.h"
enum { LEFT, FRONT, RIGHT };
class AlignModule : public QMainWindow
{
	Q_OBJECT
private:
	MeshPreview *left;
	MeshPreview *front;
	MeshPreview *right;
	OverlapZippering p;

	LandMarkInteractorStyle *leftStyle;
	LandMarkInteractorStyle *frontStyle;
	LandMarkInteractorStyle *rightStyle;
public:
	MeshPreview *resultMesh;
	void Rendering()
	{
		left->Rendering();
		front->Rendering();
		right->Rendering();
	}
	AlignModule();
	//void registeration();
	std::vector<double3> extractLandMark(vtkRenderer *rend);
	void setRight(MeshPreview *rend);
	void setFront(MeshPreview *rend);
	void setLeft(MeshPreview *rend);

	void InitializeVariables();
	int DestroyVariables();
	void InitializeUi();
	void registration(vtkPolyData *left, vtkPolyData *leftFront, vtkPolyData* rightFront, vtkPolyData* right);
	Pos* AlignModule::XYZ2Index(double3 a, int page);

private:
	vtkSmartPointer<vtkPolyData> point2mesh(vtkPoints *pts, vtkMatrix4x4 *Mat);
	void Copy(MeshPreview* src, MeshPreview* des);
	vtkSmartPointer<vtkDataArray> setTransformedCord(vtkPolyData *poly, vtkLandmarkTransform *trans);
	void RemoveCell(vtkPolyData *poly, int CellID);
	void InsertCell(vtkPolyData *poly, int triID[]);
public slots:
	void slotAlign();
	void slotLanMarkLeft();
	void slotLanMarkFront();
	void slotLanMarkRight();

	void slotLeftDefault();
	void slotFrontDefault();
	void slotRightDefault();


	void slotLeftOrigin();
	void slotFrontOrigin();
	void slotRightOrigin();
private:
	Ui::AlignModuleClass ui;

};
