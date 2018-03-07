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
//#include <vtkAbstractWidget.h>
#include<vector>

class MeshIO;
class ImageIO;

class MeshPreview
{
public:
	MeshPreview();
	~MeshPreview();
	MeshPreview(int size);

	MeshIO*											m_MeshIO;
	ImageIO*										m_ImageIO;

	std::vector<vtkPolyData*>						m_PolyData;
	vtkPolyData* GetPolyDataAt(int index) { return m_PolyData[index]; }

	std::vector<vtkImageData*>						m_ImageData;
	vtkImageData*									GetImageData(int index) { return m_ImageData[index]; }

	std::vector<vtkPolyDataMapper*>					m_Mapper;
	vtkPolyDataMapper* GetMapperAt(int index) { return m_Mapper[index]; }

	std::vector<vtkTexture*>						m_Texture;
	vtkTexture* GetTexture(int index)				{ return m_Texture[index]; }
	int												m_IsTexture;
	int IsTexture() { return m_IsTexture; };

	std::vector<vtkActor*>							m_Actor;
	vtkActor* GetActorAt(int index) { return m_Actor[index]; }

	vtkRenderer*									m_Renderer;
	vtkRenderer* GetRenderer() { return m_Renderer; }

	vtkRenderWindow*								m_RenWin;
	vtkRenderWindow* GetRenderWindow() { return m_RenWin; }

	vtkRenderWindowInteractor*						m_IRen;
	vtkRenderWindowInteractor* GetInteractor() { return m_IRen; }



	vtkInteractorStyleTrackballCamera*				m_3DStyle;
	vtkInteractorStyleTrackballCamera* Get3DStyle() { return m_3DStyle; }

	void setStyle(vtkInteractorStyle *_style);
	int InitializeVariables();
	int DestroyVariables();

	void ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize);

	int Create3DScene();
	int CreateModel(std::string meshPath, int extType);
	int CreateTexture(std::string imgPath, int extType);
	int ReleaseModel();
	void setSize(int size);
	int CaptureSave(std::string imagePath, int extType, int sizeRatio);
	int MeshSave(std::string meshPath, int extType);
	int TextureMeshSave(std::string meshPath, int meshExtType, std::string imagePath, int imgExtType);
	int NonTextureMeshSave(std::string meshPath, int meshExtType);

	void ChangeViewMode(int mode); //0 point 1 wire 2 face 3 edgeface

	void Rendering();
};