#pragma once

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkImageProperty.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>


class ImageIO;

class ImagePreview
{
public:
	ImagePreview();
	~ImagePreview();

	ImageIO*										m_ImageIO;
	ImageIO* GetImageIO() { return m_ImageIO; }

	vtkImageData*									m_ImageData;
	vtkImageData* GetImageData() { return m_ImageData; }

	vtkImageResliceMapper*							m_Mapper;
	vtkImageResliceMapper* GetMapper() { return m_Mapper; }

	vtkImageSlice*									m_Actor;
	vtkImageSlice* GetActor() { return m_Actor; }

	vtkRenderer*									m_Renderer;
	vtkRenderer* GetRenderer() { return m_Renderer; }

	vtkRenderWindow*								m_RenWin;
	vtkRenderWindow* GetRenderWindow() { return m_RenWin; }

	vtkRenderWindowInteractor*						m_IRen;
	vtkRenderWindowInteractor* GetInteractor() { return m_IRen; }

	vtkInteractorStyleImage*						m_2DStyle;
	vtkInteractorStyleImage* Get3DStyle() { return m_2DStyle; }

	int InitializeVariables();
	int DestroyVariables();

	void ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize);
	int Create2DScene();
	int CreateModel(std::string imagePath, int extType);
	int ReleaseModel();

	std::string m_filePath = "";
	std::string GetModelPath() { return m_filePath; };

	int CaptureSave(std::string imagePath, int extType, int sizeRatio);
	int ImageSave(std::string imagePath, int extType);
	void Rendering();
};
