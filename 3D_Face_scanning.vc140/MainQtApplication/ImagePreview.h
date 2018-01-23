#pragma once

#include <vtk-8.1\vtkSmartPointer.h>
#include <vtk-8.1\vtkImageData.h>
#include <vtk-8.1\vtkImageResliceMapper.h>
#include <vtk-8.1\vtkImageSlice.h>
#include <vtk-8.1\vtkImageProperty.h>
#include <vtk-8.1\vtkRenderer.h>
#include <vtk-8.1\vtkCamera.h>
#include <vtk-8.1\vtkRenderWindow.h>
#include <vtk-8.1\vtkRenderWindowInteractor.h>
#include <vtk-8.1\vtkInteractorStyleImage.h>


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
