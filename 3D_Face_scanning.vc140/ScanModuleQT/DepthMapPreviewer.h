#pragma once
#include"../DepthModule/device.h"
#include"vtkImageData.h"
#include"vtkTexture.h"
//#include"vtkPolyData.h"
//#include"vtkPolyDataMapper.h"
//#include"vtkActor.h"
#include"vtkImageMapper3D.h"
#include"vtkImageActor.h"

#include"vtkRenderWindowInteractor.h"
#include"vtkRenderWindow.h"
#include"vtkInteractorStyleImage.h"
#include"vtkActor2DCollection.h"
#include"vtkRenderer.h"
#include"vtkProperty.h"
#include"vtkProperty2D.h"
#include"vtkCamera.h"
#include"vtkImageProperty.h"

class DepthMapPreviewer
{
public:
	//vtkPolyData*									m_PolyData;
	//vtkPolyData*									GetPolyData() { return m_PolyData; }

	vtkImageData*									m_ImageData;
	vtkImageData*									GetImageData() { return m_ImageData; }

	/*vtkPolyDataMapper*								m_Mapper;
	vtkPolyDataMapper*								GetMapper() { return m_Mapper; }*/

	/*vtkTexture*										m_Texture;
	vtkTexture*										GetTexture() { return m_Texture; }*/
	int												m_IsTexture;
	int												IsTexture() { return m_IsTexture; };

	/*vtkActor*										m_Actor;
	vtkActor* GetActor() { return m_Actor; }*/

	vtkRenderer*									m_Renderer;
	vtkRenderer* GetRenderer() { return m_Renderer; }

	//vtkImageMapper3D *m_ImageMapper;
	vtkImageActor *m_ImageActor;
	vtkImageActor * GetActor() { return m_ImageActor; }

	vtkRenderWindow*								m_RenWin;
	vtkRenderWindow* GetRenderWindow() { return m_RenWin; }

	vtkRenderWindowInteractor*						m_IRen;
	vtkRenderWindowInteractor* GetInteractor() { return m_IRen; }

	//vtkImageViewer2 *viewer;
	vtkInteractorStyleImage*						m_2DStyle;
	vtkInteractorStyleImage*						Get2DStyle() { return m_2DStyle; }

	DepthMapPreviewer();
	~DepthMapPreviewer();


	void ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize);

	int CreateModel(std::string imagePath, int extType);
	int ReleaseModel();
	int Create2DScene();
	int InitializeVariables();
	int DestroyVariables();
	//int CaptureSave(std::string imagePath, int extType, int sizeRatio);
	//int ImageSave(std::string imagePath, int extType);
	void Rendering();



};
