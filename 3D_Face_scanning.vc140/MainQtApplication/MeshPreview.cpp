#include "MeshPreview.h"
#include "MeshIO.h"
#include "ImageIO.h"

MeshPreview::MeshPreview(int size)
{
	setSize(size);
	InitializeVariables();
}

MeshPreview::MeshPreview()
{
	setSize(1);
	InitializeVariables();
}
void MeshPreview::setSize(int size)
{
	/*m_PolyData.clear();
	m_Actor.clear();
	m_Mapper.clear();*/

	m_PolyData.resize(size);
	m_Actor.resize(size);
	m_Mapper.resize(size);
	m_Texture.resize(size);
	m_ImageData.resize(size);

}
MeshPreview::~MeshPreview()
{
	DestroyVariables();
}

void MeshPreview::ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize)
{
	m_RenWin->SetParentId(uiCtrl);
	m_RenWin->SetSize(xCtrlSize, yCtrlSize);

	/*uiCtr= uiCtrl;
	uiX = xCtrlSize;
	uiY= yCtrlSize;*/
}

void MeshPreview::setStyle(vtkInteractorStyle *_style)
{
	m_IRen->SetInteractorStyle(_style);
}


int MeshPreview::CreateModel(std::string meshPath, int extType)
{
	if (meshPath != "")//only view
	{
		if (!m_PolyData[0])
			return 0;

		m_MeshIO->ImportMesh(extType, meshPath, m_PolyData[0]);
		m_PolyData[0]->Modified();

		int n = m_PolyData[0]->GetNumberOfPoints();

		m_Mapper[0]->SetInputData(m_PolyData[0]);
		m_Mapper[0]->Update();

		m_Actor[0]->SetMapper(m_Mapper[0]);//actor에 mapper을 set함. 

		if (m_IsTexture)
			m_Actor[0]->SetTexture(m_Texture[0]);
		m_Actor[0]->GetProperty()->SetInterpolationToGouraud();
		m_Actor[0]->GetProperty()->SetColor(1.0, 1.0, 1.0);
		m_Actor[0]->GetProperty()->BackfaceCullingOn();


		m_Actor[0]->Modified();

		m_Renderer->AddActor(m_Actor[0]);
		m_Renderer->ResetCamera();
		m_Renderer->Modified();

		return 1;
	}


	else 
	{
		for (int i = 0; i < m_Actor.size(); i++)
		{
			if (!m_PolyData[i])
			{
				return 0;
			}

			//	m_MeshIO->ImportMesh(extType, meshPath, m_PolyData[i]);
			m_PolyData[i]->Modified();

			//int n = m_PolyData[0]->GetNumberOfPoints();

			m_Mapper[i]->SetInputData(m_PolyData[i]);
			m_Mapper[i]->Update();
			m_Actor[i]->SetMapper(m_Mapper[i]);
			m_Renderer->AddActor(m_Actor[i]);

			if (m_IsTexture)
			{
				m_Actor[i]->SetTexture(m_Texture[i]);
				m_Actor[i]->GetProperty()->SetInterpolationToGouraud();
				m_Actor[i]->GetProperty()->SetColor(1.0, 1.0, 1.0);
				m_Actor[i]->GetProperty()->BackfaceCullingOn();
				m_Actor[i]->Modified();
			}
		}


		std::cout << " (" << m_Renderer->GetActors()->GetNumberOfItems() << ")!�� \n";
		m_Renderer->ResetCamera();
		m_Renderer->Modified();

		return 1;
	}
}

int MeshPreview::CreateTexture(std::string imgPath, int extType)
{
	//m_ImageIO->ImportImage(extType, imgPath, m_ImageData);
	
	for (int i = 0; i < m_ImageData.size(); i++)
	{
		m_ImageData[i]->Modified();
		m_Texture[i]->SetInputData(m_ImageData[i]);
		m_Texture[i]->Update();
	}
	

	m_IsTexture = 1;

	return 1;
}

int MeshPreview::ReleaseModel()
{
	std::cout << " (" << m_Renderer->GetActors()->GetNumberOfItems() << ")�� \n";

	for (int i = 0; i < m_Actor.size(); i++)
	{
		std::cout << "i 째 : " << i << "\n";

		m_Renderer->RemoveActor(m_Actor[i]);

		if (m_Actor[i])
		{
			m_Actor[i]->Delete();
			m_Actor[i] = NULL;
			m_Actor[i] = vtkActor::New();
		}
		if (m_Mapper[i])
		{
			m_Mapper[i]->Delete();
			m_Mapper[i] = NULL;
			m_Mapper[i] = vtkPolyDataMapper::New();
		}
		if (m_PolyData[i])
		{
			m_PolyData[i]->ReleaseData();
			m_PolyData[i]->Delete();
			m_PolyData[i] = NULL;
			m_PolyData[i] = vtkPolyData::New();
		}

		if (m_Texture[i])
		{
			m_Texture[i]->Delete();
			m_Texture[i] = NULL;
			m_Texture[i] = vtkTexture::New();
			m_IsTexture = 0;
		}

	}

	
	/*if (m_ImageData)
	{
	m_ImageData->ReleaseData();
	m_ImageData->Delete();
	m_ImageData = NULL;
	m_ImageData = vtkImageData::New();
	}*/

	return 1;
}

int MeshPreview::Create3DScene()
{
	m_Renderer->GetActiveCamera()->ParallelProjectionOff();
	//m_Renderer->GetActiveCamera()->SetPosition(m_Actor[0]->GetCenter());
	//m_Renderer->GetActiveCamera()->SetFocalPoint(m_Actor[0]->GetCenter());

	m_RenWin->AddRenderer(m_Renderer);
	m_IRen->SetInteractorStyle(m_3DStyle);
	m_RenWin->SetInteractor(m_IRen);
	m_RenWin->Modified();

	return 1;
}



int MeshPreview::InitializeVariables()
{
	m_MeshIO = NULL;
	m_ImageIO = NULL;

	

	//m_Texture = NULL;

	m_Renderer = NULL;
	m_RenWin = NULL;
	m_IRen = NULL;
	m_3DStyle = NULL;

	for (int i = 0; i < m_Actor.size(); i++) {
		m_ImageData[i] = vtkImageData::New();;
		m_PolyData[i] = vtkPolyData::New();
		m_Mapper[i] = vtkPolyDataMapper::New();
		m_Actor[i] = vtkActor::New();
		m_Texture[i] = vtkTexture::New();
	}

	m_MeshIO = new MeshIO;
	m_ImageIO = new ImageIO;

	
	
	m_IsTexture = 0;
	m_Renderer = vtkRenderer::New();
	m_RenWin = vtkRenderWindow::New();
	m_IRen = vtkRenderWindowInteractor::New();
	m_3DStyle = vtkInteractorStyleTrackballCamera::New();

	//m_RenWin->SetParentId(uiCtr);
	//m_RenWin->SetSize(uiX, uiY);
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
	for (int i = 0; i < m_Actor.size(); i++)
	{
		if (m_ImageData[i])
		{
			m_ImageData[i]->ReleaseData();
			m_ImageData[i]->Delete();
			m_ImageData[i] = NULL;
		}

		if (m_PolyData[i])
		{
			m_PolyData[i]->ReleaseData();
			m_PolyData[i]->Delete();
			m_PolyData[i] = NULL;
		}

		if (m_Mapper[i])
		{
			m_Mapper[i]->Delete();
			m_Mapper[i] = NULL;
		}
		if (m_Actor[i])
		{
			m_Actor[i]->Delete();
			m_Actor[i] = NULL;
		}

		if (m_Texture[i])
		{
			m_Texture[i]->Delete();
			m_Texture[i] = NULL;
		}
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
	//	m_MeshIO->ExportMesh(extType, meshPath, m_PolyData);
	std::cout << "�ѹ��� ���� polyData�� Export�ϴ� ����� Ȯ���ϼ���";
	return 1;
}

int MeshPreview::TextureMeshSave(std::string meshPath, int meshExtType, std::string imagePath, int imgExtType)
{
	/*m_MeshIO->ExportOBJFile(m_RenWin, meshPath);
	m_ImageIO->ExportImageFile(imgExtType, m_ImageData, imagePath);

	return 1;*/
	return 1;
}

int MeshPreview::NonTextureMeshSave(std::string meshPath, int meshExtType)
{
	m_MeshIO->ExportOBJFile(m_RenWin, meshPath);

	return 1;
}


void MeshPreview::ChangeViewMode(int mode) //0 point 1 wire 2 face 3 edgeface
{
	for (int i = 0; i < m_Actor.size(); i++)
	{
		if (mode == 0)
		{
			m_Actor[i]->GetProperty()->SetRepresentationToPoints();
			m_Actor[i]->GetProperty()->SetVertexColor(1.0, 1.0, 1.0);
		}
		else if (mode == 1)
		{
			m_Actor[i]->GetProperty()->SetRepresentationToWireframe();
			m_Actor[i]->GetProperty()->EdgeVisibilityOn();
			m_Actor[i]->GetProperty()->SetEdgeColor(1.0, 1.0, 1.0);
		}
		else if (mode == 2)
		{
			m_Actor[i]->GetProperty()->SetRepresentationToSurface();
			m_Actor[i]->GetProperty()->SetColor(1.0, 1.0, 1.0);
			m_Actor[i]->GetProperty()->EdgeVisibilityOff();
		}
		else// (mode == 3)
		{
			m_Actor[i]->GetProperty()->SetRepresentationToSurface();
			m_Actor[i]->GetProperty()->SetColor(1.0, 1.0, 1.0);
			m_Actor[i]->GetProperty()->EdgeVisibilityOn();
			m_Actor[i]->GetProperty()->SetEdgeColor(0.0, 1.0, 0.0);
		}
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

