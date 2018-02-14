#include "MeshPreview.h"

#include "MeshIO.h"
#include "ImageIO.h"

MeshPreview::MeshPreview()
{
	InitializeVariables();
}

MeshPreview::~MeshPreview()
{
	DestroyVariables();
}

void MeshPreview::ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize)
{
	m_RenWin->SetParentId(uiCtrl);
	m_RenWin->SetSize(xCtrlSize, yCtrlSize);
}

void MeshPreview::setStyle(vtkInteractorStyle *_style)
{
	m_IRen->SetInteractorStyle(_style);
}


int MeshPreview::CreateModel(std::string meshPath, int extType)
{
	if (!m_PolyData)
		return 0;

	m_MeshIO->ImportMesh(extType, meshPath, m_PolyData);
	m_PolyData->Modified();

	int n = m_PolyData->GetNumberOfPoints();

	m_Mapper->SetInputData(m_PolyData);
	m_Mapper->Update();

	m_Actor->SetMapper(m_Mapper);//actor¿¡ mapperÀ» setÇÔ.  

	if (m_IsTexture)
		m_Actor->SetTexture(m_Texture);
	m_Actor->GetProperty()->SetInterpolationToGouraud();
	m_Actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
	m_Actor->GetProperty()->BackfaceCullingOn();
	
	//m_Actor->GetProperty()->SetOpacity();
	//m_Actor->GetProperty()->SetAmbient();
	//m_Actor->GetProperty()->SetDiffuse();
	//m_Actor->GetProperty()->SetSpecular();
	//m_Actor->GetProperty()->SetSpecularPower();
	//m_Actor->GetProperty()->VertexVisibilityOn();
	//m_Actor->GetProperty()->SetVertexColor();
	//m_Actor->GetProperty()->EdgeVisibilityOn();
	//m_Actor->GetProperty()->SetEdgeColor();
	m_Actor->Modified();


	m_Renderer->AddActor(m_Actor);
	m_Renderer->ResetCamera();
	m_Renderer->Modified();

	return 1;
}

int MeshPreview::CreateTexture(std::string imgPath, int extType)
{
	m_ImageIO->ImportImage(extType, imgPath, m_ImageData);
	m_ImageData->Modified();

	m_Texture->SetInputData(m_ImageData);
	m_Texture->Update();

	m_IsTexture = 1;
		
	return 1;
}

int MeshPreview::ReleaseModel()
{
	m_Renderer->RemoveActor(m_Actor);

	/*if (m_OrignActor)
	{
		m_OrignActor->Delete();
		m_OrignActor = NULL;
		m_OrignActor = vtkActor::New();
	}*/
	if (m_Actor)
	{
		m_Actor->Delete();
		m_Actor = NULL;
		m_Actor = vtkActor::New();
	}
	if (m_Mapper)
	{
		m_Mapper->Delete();
		m_Mapper = NULL;
		m_Mapper = vtkPolyDataMapper::New();
	}
	if (m_PolyData)
	{
		m_PolyData->ReleaseData();
		m_PolyData->Delete();
		m_PolyData = NULL;
		m_PolyData = vtkPolyData::New();
	}
	if (m_Texture)
	{
		m_Texture->Delete();
		m_Texture = NULL;
		m_Texture = vtkTexture::New();
		m_IsTexture = 0;
	}
	if (m_ImageData)
	{
		m_ImageData->ReleaseData();
		m_ImageData->Delete();
		m_ImageData = NULL;
		m_ImageData = vtkImageData::New();
	}
	
	
	return 1;
}

int MeshPreview::Create3DScene()
{
	m_Renderer->GetActiveCamera()->ParallelProjectionOff();

	m_RenWin->AddRenderer(m_Renderer);
	m_IRen->SetInteractorStyle(m_3DStyle);
	m_RenWin->SetInteractor(m_IRen);
	m_RenWin->Modified();

	return 1;
}



int MeshPreview::InitializeVariables()
{
	m_MeshIO		= NULL;
	m_ImageIO		= NULL;
	m_PolyData		= NULL;
	m_ImageData		= NULL;
	m_Mapper		= NULL;
	m_Texture		= NULL;
	m_Actor			= NULL;
	m_Renderer		= NULL;
	m_RenWin		= NULL;
	m_IRen			= NULL;
	m_3DStyle		= NULL;

	m_MeshIO = new MeshIO;
	m_ImageIO = new ImageIO;

	m_PolyData		= vtkPolyData::New();
	m_ImageData		= vtkImageData::New();
	m_Mapper		= vtkPolyDataMapper::New();
	m_Texture		= vtkTexture::New();
	m_IsTexture = 0;
	m_Actor			= vtkActor::New();
	m_Renderer		= vtkRenderer::New();
	m_RenWin		= vtkRenderWindow::New();
	m_IRen			= vtkRenderWindowInteractor::New();
	m_3DStyle		= vtkInteractorStyleTrackballCamera::New();

	return 1;
}

int MeshPreview::DestroyVariables()
{
	if (m_MeshIO)
	{
		delete m_MeshIO;
		m_MeshIO = NULL;
	}
	if (m_ImageIO)
	{
		delete m_ImageIO;
		m_ImageIO = NULL;
	}
	if (m_PolyData)
	{
		m_PolyData->ReleaseData();
		m_PolyData->Delete();
		m_PolyData = NULL;
	}
	if (m_ImageData)
	{
		m_ImageData->ReleaseData();
		m_ImageData->Delete();
		m_ImageData = NULL;
	}
	if (m_Mapper)
	{
		m_Mapper->Delete();
		m_Mapper = NULL;
	}
	if (m_Texture)
	{
		m_Texture->Delete();
		m_Texture = NULL;
	}
	if (m_Actor)
	{
		m_Actor->Delete();
		m_Actor = NULL;
	}
	if (m_Renderer)
	{
		m_Renderer->Delete();
		m_Renderer = NULL;
	}
	if (m_RenWin)
	{
		m_RenWin->Delete();
		m_RenWin = NULL;
	}
	if (m_IRen)
	{
		m_IRen->Delete();
		m_IRen = NULL;
	}
	if (m_3DStyle)
	{
		m_3DStyle->Delete();
		m_3DStyle = NULL;
	}

	return 1;
}

int MeshPreview::CaptureSave(std::string imagePath, int extType, int sizeRatio)
{
	m_ImageIO->CaptureSaveImageFile(m_RenWin, extType, sizeRatio, imagePath);
	m_RenWin->Render();

	return 1;
}

int MeshPreview::MeshSave(std::string meshPath, int extType)
{
	m_MeshIO->ExportMesh(extType, meshPath, m_PolyData);

	return 1;
}

int MeshPreview::TextureMeshSave(std::string meshPath, int meshExtType, std::string imagePath, int imgExtType)
{
	m_MeshIO->ExportOBJFile(m_RenWin, meshPath);
	m_ImageIO->ExportImageFile(imgExtType, m_ImageData, imagePath);

	return 1;
}

int MeshPreview::NonTextureMeshSave(std::string meshPath, int meshExtType)
{
	m_MeshIO->ExportOBJFile(m_RenWin, meshPath);

	return 1;
}


void MeshPreview::ChangeViewMode(int mode) //0 point 1 wire 2 face 3 edgeface
{
	if (mode == 0)
	{
		m_Actor->GetProperty()->SetRepresentationToPoints();
		m_Actor->GetProperty()->SetVertexColor(1.0, 1.0, 1.0);
	}
	else if (mode == 1)
	{
		m_Actor->GetProperty()->SetRepresentationToWireframe();
		m_Actor->GetProperty()->EdgeVisibilityOn();
		m_Actor->GetProperty()->SetEdgeColor(1.0, 1.0, 1.0);
	}
	else if (mode == 2)
	{
		m_Actor->GetProperty()->SetRepresentationToSurface();
		m_Actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
		m_Actor->GetProperty()->EdgeVisibilityOff();
	}
	else// (mode == 3)
	{
		m_Actor->GetProperty()->SetRepresentationToSurface();
		m_Actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
		m_Actor->GetProperty()->EdgeVisibilityOn();
		m_Actor->GetProperty()->SetEdgeColor(0.0, 1.0, 0.0);
	}

	Rendering();
}

void MeshPreview::Rendering()
{
	m_RenWin->Render();
}
//m_Actor->GetProperty()->SetInterpolationToGouraud();
//m_Actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
//m_Actor->GetProperty()->BackfaceCullingOn();
//m_Actor->GetProperty()->SetOpacity();
//m_Actor->GetProperty()->SetAmbient();
//m_Actor->GetProperty()->SetDiffuse();
//m_Actor->GetProperty()->SetSpecular();
//m_Actor->GetProperty()->SetSpecularPower();
//m_Actor->GetProperty()->VertexVisibilityOn();
//m_Actor->GetProperty()->SetVertexColor();
//m_Actor->GetProperty()->EdgeVisibilityOn();
//m_Actor->GetProperty()->SetEdgeColor();


