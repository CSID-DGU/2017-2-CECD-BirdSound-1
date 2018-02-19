#pragma once
#include"../ScanModule/Scan.h"
#include"../DepthModule/device.h"

#include<vtkActor.h>
#include<vtkPolyData.h>
#include<vtkImageData.h>
#include<vtkPolyDataMapper.h>
#include<vtkProperty.h>
#include<vtkInteractorStyle.h>
#include<vtkInteractorStyleImage.h>
#include<vtkImageMapper.h>
#include<vtkActor2D.h>

class MeshIO;
class ImageIO;
class RealSensePreviewer : public Scan
{
public:
	
	RealSensePreviewer();
	~RealSensePreviewer();

	MeshIO*											m_MeshIO;
	ImageIO*										m_ImageIO;

	vtkPolyData*									m_PolyData;
	vtkPolyData*									GetPolyData() { return m_PolyData; }

	vtkImageData*									m_ImageData;
	vtkImageData*									GetImageData() { return m_ImageData; }

	vtkPolyDataMapper*								m_Mapper;
	vtkPolyDataMapper*								GetMapper() { return m_Mapper; }

	vtkTexture*										m_Texture;
	vtkTexture*										GetTexture() { return m_Texture; }
	int												m_IsTexture;
	int IsTexture()									{ return m_IsTexture; };

	vtkActor*										m_Actor;
	vtkActor* GetActor()							{ return m_Actor; }

	vtkRenderer*									m_Renderer;
	vtkRenderer* GetRenderer()						{ return m_Renderer; }

	vtkImageMapper *m_ImageMapper;
	vtkActor2D *m_ImageActor;

	vtkRenderWindow*								m_RenWin;
	vtkRenderWindow* GetRenderWindow()				{ return m_RenWin; }

	vtkRenderWindowInteractor*						m_IRen;
	vtkRenderWindowInteractor* GetInteractor()		{ return m_IRen; }

	//vtkImageViewer2 *viewer;
	vtkInteractorStyleImage*						m_2DStyle;
	vtkInteractorStyleImage*						Get2DStyle() { return m_2DStyle; }


	void setStyle(vtkInteractorStyle *_style);
	int InitializeVariables();
	int DestroyVariables();

	void ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize);

	int Create2DScene();
	int CreateModel(std::string meshPath, int extType);
	int CreateTexture(std::string imgPath, int extType);
	int ReleaseModel();

	int CaptureSave(std::string imagePath, int extType, int sizeRatio);
	int MeshSave(std::string meshPath, int extType);
	int TextureMeshSave(std::string meshPath, int meshExtType, std::string imagePath, int imgExtType);
	int NonTextureMeshSave(std::string meshPath, int meshExtType);
	void streamingColorRaw16();
	void streamingColorRGB8();
	
	void Rendering();
};