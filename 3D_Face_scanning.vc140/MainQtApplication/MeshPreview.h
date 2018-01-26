#pragma once

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkPolyDataMapper.h>
#include <vtkTexture.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkAbstractWidget.h>
class MeshIO;
class ImageIO;

class MeshPreview
{
public:
	MeshPreview();
	~MeshPreview();

	MeshIO*											m_MeshIO;
	ImageIO*										m_ImageIO;

	vtkPolyData*									m_PolyData;
	vtkPolyData* GetPolyData()						{ return m_PolyData; }

	vtkImageData*									m_ImageData;
	vtkImageData* GetImageData()					{ return m_ImageData; }

	vtkPolyDataMapper*								m_Mapper;
	vtkPolyDataMapper* GetMapper()					{ return m_Mapper; }

	vtkTexture*										m_Texture;
	vtkTexture* GetTexture()						{ return m_Texture; }
	int												m_IsTexture;
	int IsTexture()									{ return m_IsTexture; };

	vtkActor*										m_Actor;
	vtkActor* GetActor()							{ return m_Actor; }

	vtkRenderer*									m_Renderer;
	vtkRenderer* GetRenderer()						{ return m_Renderer; }

	vtkRenderWindow*								m_RenWin;
	vtkRenderWindow* GetRenderWindow()				{ return m_RenWin; }

	vtkRenderWindowInteractor*						m_IRen;
	vtkRenderWindowInteractor* GetInteractor()		{ return m_IRen; }
	


	vtkInteractorStyleTrackballCamera*				m_3DStyle;
	vtkInteractorStyleTrackballCamera* Get3DStyle()	{ return m_3DStyle; }

	vtkActor*										m_OrignActor;
	vtkActor* GetOrignActor()						{ return m_OrignActor; }

	void setStyle(vtkInteractorStyle *_style);
	int InitializeVariables();
	int DestroyVariables();

	void ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize);
	
	int Create3DScene();
	int CreateModel(std::string meshPath, int extType);
	int CreateTexture(std::string imgPath, int extType);
	int ReleaseModel();

	int CaptureSave(std::string imagePath, int extType, int sizeRatio);
	int MeshSave(std::string meshPath, int extType);
	int TextureMeshSave(std::string meshPath, int meshExtType, std::string imagePath, int imgExtType);
	int NonTextureMeshSave(std::string meshPath, int meshExtType);

	void ChangeViewMode(int mode); //0 point 1 wire 2 face 3 edgeface

	void Rendering();
	
	void ChangeToOrgin()
	{
		m_RenWin->ClearInRenderStatus();
		
		if (m_Renderer != NULL)
		{
			m_Renderer->Delete();
			m_Renderer = NULL;
		}
		m_Renderer = vtkRenderer::New();


		m_Renderer->AddActor(m_OrignActor);
		m_Renderer->ResetCamera();

		m_RenWin->AddRenderer(m_Renderer);

		Rendering();
		m_IRen->SetRenderWindow(m_RenWin);
		
		m_IRen->SetInteractorStyle(m_3DStyle);
		m_RenWin->SetInteractor(m_IRen);

	
	}

};
