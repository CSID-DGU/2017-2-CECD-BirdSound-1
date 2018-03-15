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
class double3
{
public:
	double x, y, z;
	double3(double _x, double _y, double _z):x(_x),y(_y),z(_z){}
	
	double *getData()
	{
		double data[3] = { x,y,z };
		return data;
	}
};
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
	void align()
	{
		if (left == nullptr || front == nullptr || right == nullptr)
		{
			std::cout << "사진 3장 제대로 찍어요\n";
			return;
		}

		else
		{
			std::vector<double3>leftMark;
			std::vector<double3>frontMark;
			std::vector<double3>rightMark;

			leftMark = extractLandMark(left);
			frontMark = extractLandMark(front);
			rightMark = extractLandMark(right);


			vtkPoints*left =vtkPoints::New();
			vtkPoints*right = vtkPoints::New();
			vtkPoints*front = vtkPoints::New();

			for (int i = 0; i < leftMark.size(); i++)
			{
				left->InsertNextPoint(leftMark[i].getData());
				right->InsertNextPoint(rightMark[i].getData());
				front->InsertNextPoint(frontMark[i].getData());

			}

		

			// Setup the transform
			vtkLandmarkTransform*landmarkTransform =vtkLandmarkTransform::New();
			landmarkTransform->SetSourceLandmarks(left);
			landmarkTransform->SetTargetLandmarks(front);
			landmarkTransform->SetModeToRigidBody();
			landmarkTransform->Update(); //should this be here?

			vtkPolyData*leftPoly =vtkPolyData::New();
			leftPoly->SetPoints(left);

			vtkPolyData*frontPoly =vtkPolyData::New();
			frontPoly->SetPoints(front);

			vtkVertexGlyphFilter*leftFilter =vtkVertexGlyphFilter::New();


			leftFilter->SetInputData(leftPoly);
			leftFilter->Update();

			vtkVertexGlyphFilter*frontFilter =vtkVertexGlyphFilter::New();

			frontFilter->SetInputData(frontPoly);
			frontFilter->Update();

			vtkTransformPolyDataFilter*transformFilter =vtkTransformPolyDataFilter::New();
			transformFilter->SetInputConnection(leftFilter->GetOutputPort());
			transformFilter->SetTransform(landmarkTransform);
			transformFilter->Update();

			// Display the transformation matrix that was computed
			vtkMatrix4x4* mat = landmarkTransform->GetMatrix();

			// Visualize
			vtkPolyDataMapper*leftMapper =vtkPolyDataMapper::New();
			leftMapper->SetInputConnection(leftFilter->GetOutputPort());

			vtkActor*leftActor =vtkActor::New();
			leftActor->SetMapper(leftMapper);
			leftActor->GetProperty()->SetColor(0, 1, 0);
			leftActor->GetProperty()->SetPointSize(4);

			vtkPolyDataMapper*frontMapper =vtkPolyDataMapper::New();
			frontMapper->SetInputConnection(frontFilter->GetOutputPort());

			vtkActor*frontActor =vtkActor::New();
			frontActor->SetMapper(frontMapper);
			frontActor->GetProperty()->SetColor(1, 0, 0);
			frontActor->GetProperty()->SetPointSize(4);

			vtkPolyDataMapper*solutionMapper =vtkPolyDataMapper::New();
			solutionMapper->SetInputConnection(transformFilter->GetOutputPort());

			vtkActor*leftNfront =vtkActor::New();
			leftNfront->SetMapper(solutionMapper);
			leftNfront->GetProperty()->SetColor(0, 0, 1);
			leftNfront->GetProperty()->SetPointSize(3);








			// Create a renderer, render window, and interactor
			vtkRenderer*renderer =vtkRenderer::New();
			vtkRenderWindow*renderWindow =vtkRenderWindow::New();
			renderWindow->AddRenderer(renderer);
			vtkRenderWindowInteractor*renderWindowInteractor =vtkRenderWindowInteractor::New();
			renderWindowInteractor->SetRenderWindow(renderWindow);

			// Add the actor to the scene
			renderer->AddActor(leftActor);
			renderer->AddActor(frontActor);
			renderer->AddActor(leftNfront);
			

												 // Render and interact
			renderWindow->Render();
			renderWindowInteractor->Start();
		}
	
	}

	std::vector<double3> extractLandMark(vtkRenderer *rend)
	{
		std::vector<double3>vec;
		if (rend == NULL)return vec;

		vtkActorCollection * actorCol = rend->GetActors();
		actorCol->InitTraversal();

		for (vtkIdType i = 0; i < actorCol->GetNumberOfItems(); i++)
		{
			if (i >= 1) 
			{
				vtkActor *nextActor = actorCol->GetNextActor();
				double *pos = nextActor->GetCenter();
				std::cout << pos[0] << " " << pos[1] << " " << pos[2] << "\n";

				vec.push_back(double3(pos[0], pos[1], pos[2]));
			}
		}

		return vec;
		
	}
	void setRight(vtkRenderer *rend)
	{
		left = rend;
	}
	void setFront(vtkRenderer *rend)
	{
		left = rend;
	}
	void setLeft(vtkRenderer *rend)
	{
		left = rend;
	}
};