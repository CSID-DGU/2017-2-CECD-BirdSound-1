#include "RealSensePreviewer.h"

#include "MeshIO.h"
#include "ImageIO.h"

RealSensePreviewer::RealSensePreviewer()
{
	InitializeVariables();
}

RealSensePreviewer::~RealSensePreviewer()
{
	//DestroyVariables();
}

void RealSensePreviewer::ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize)
{
	m_RenWin->SetParentId(uiCtrl);
	m_RenWin->SetSize(xCtrlSize, yCtrlSize);
}

void RealSensePreviewer::setStyle(vtkInteractorStyle *_style)
{
	m_IRen->SetInteractorStyle(_style);
}


int RealSensePreviewer::CreateModel(std::string meshPath, int extType)
{
	if (!m_PolyData)
		return 0;

	m_MeshIO->ImportMesh(extType, meshPath, m_PolyData);
	m_PolyData->Modified();

	int n = m_PolyData->GetNumberOfPoints();

	m_Mapper->SetInputData(m_PolyData);
	m_Mapper->Update();

	m_Actor->SetMapper(m_Mapper);//actor에 mapper을 set함.  

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

int RealSensePreviewer::CreateTexture(std::string imgPath, int extType)
{
	m_ImageIO->ImportImage(extType, imgPath, m_ImageData);
	m_ImageData->Modified();

	m_Texture->SetInputData(m_ImageData);
	m_Texture->Update();

	m_IsTexture = 1;

	return 1;
}

int RealSensePreviewer::ReleaseModel()
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
int RealSensePreviewer::Create2DScene()
{
	m_Renderer->GetActiveCamera()->ParallelProjectionOff();

	m_RenWin->AddRenderer(m_Renderer);
	m_IRen->SetInteractorStyle(m_2DStyle);
	m_RenWin->SetInteractor(m_IRen);
	m_RenWin->Modified();



	
	m_ImageActor->SetMapper(m_ImageMapper);
	m_Renderer->AddActor2D(m_ImageActor);



	m_IRen->SetRenderWindow(m_RenWin);
	return 1;
}





int RealSensePreviewer::InitializeVariables()
{
	m_MeshIO = NULL;
	m_ImageIO = NULL;
	m_PolyData = NULL;
	m_ImageData = NULL;
	m_Mapper = NULL;
	m_Texture = NULL;
	m_Actor = NULL;
	m_Renderer = NULL;
	m_RenWin = NULL;
	m_IRen = NULL;
	m_ImageMapper = NULL;
	m_ImageActor = NULL;
	//viewer = NULL;

	m_MeshIO = new MeshIO;
	m_ImageIO = new ImageIO;

	m_PolyData = vtkPolyData::New();
	m_ImageData = vtkImageData::New();
	m_Mapper = vtkPolyDataMapper::New();
	m_Texture = vtkTexture::New();
	m_IsTexture = 0;
	m_Actor = vtkActor::New();
	m_Renderer = vtkRenderer::New();
	m_RenWin = vtkRenderWindow::New();
	m_IRen = vtkRenderWindowInteractor::New();
	//viewer = vtkImageViewer2::New();
	m_2DStyle = vtkInteractorStyleImage::New();
	m_ImageMapper = vtkImageMapper::New();
	m_ImageActor = vtkActor2D::New();

	return 1;
}

int RealSensePreviewer::DestroyVariables()
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


	return 1;
}

int RealSensePreviewer::CaptureSave(std::string imagePath, int extType, int sizeRatio)
{
	m_ImageIO->CaptureSaveImageFile(m_RenWin, extType, sizeRatio, imagePath);
	m_RenWin->Render();

	return 1;
}

int RealSensePreviewer::MeshSave(std::string meshPath, int extType)
{
	m_MeshIO->ExportMesh(extType, meshPath, m_PolyData);
	return 1;
}

int RealSensePreviewer::TextureMeshSave(std::string meshPath, int meshExtType, std::string imagePath, int imgExtType)
{
	m_MeshIO->ExportOBJFile(m_RenWin, meshPath);
	m_ImageIO->ExportImageFile(imgExtType, m_ImageData, imagePath);

	return 1;
}

int RealSensePreviewer::NonTextureMeshSave(std::string meshPath, int meshExtType)
{
	m_MeshIO->ExportOBJFile(m_RenWin, meshPath);
	return 1;
}



void RealSensePreviewer::Rendering()
{
	m_RenWin->Render();
}


void RealSensePreviewer::streamingColorRGB8()
{
	std::string devSerialNumber = realsense::getFirstSerial();
	realsense::Device* device = new realsense::Device(devSerialNumber);
	double dimensions[3] = { 1920, 1080, 1 };
	const int nComponents = m_ImageData->GetNumberOfScalarComponents();
	int nScalar = dimensions[2] * dimensions[1] * dimensions[0] * nComponents * 3;

	m_ImageData->SetDimensions(dimensions[0], dimensions[1], dimensions[2]);
	m_ImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
	m_ImageData->Modified();


	device->EnableEmitter(0.0f);

	device->selectSensorAndStreamProps();
	while (1)
	{
		auto fColor = device->capture(realsense::RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		const unsigned char* data = static_cast<const unsigned char*>(fColor.get_data());
		/*getstream ****************************/

		unsigned char* scalarPointer = static_cast<unsigned char*>(m_ImageData->GetScalarPointer(0, 0, 0));

		for (int i = 0; i < nScalar; i++)
		{
			scalarPointer[i] = data[i];
			//std::cout << int(data[i]) << " ";
			//std::cout << i << " ";
		}

		m_ImageMapper->SetInputData(m_ImageData);
		m_ImageActor->SetMapper(m_ImageMapper);
		m_Renderer->AddActor2D(m_ImageActor);
		m_RenWin->Render();

		_sleep(10);
	}
}


/*raw16 format을 steaming하는 것*/
void RealSensePreviewer::streamingColorRaw16()
{

	std::string devSerialNumber = realsense::getFirstSerial();
	realsense::Device* device = new realsense::Device(devSerialNumber);
	double dimensions[3] = { 1920, 1080, 1 };
	const int nComponents = m_ImageData->GetNumberOfScalarComponents();
	int nScalar = dimensions[2] * dimensions[1] * dimensions[0] * nComponents;

	m_ImageData->SetDimensions(dimensions[0], dimensions[1], dimensions[2]);
	m_ImageData->AllocateScalars(VTK_UNSIGNED_SHORT, 1);
	m_ImageData->Modified();


	device->EnableEmitter(0.0f);
	device->selectSensorAndStreamProps();
	while (1)
	{
		
		auto fColor = device->capture(realsense::RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
		const unsigned short* data = static_cast<const unsigned short*>(fColor.get_data());
		/*getstream ****************************/

		unsigned short* scalarPointer = static_cast<unsigned short*>(m_ImageData->GetScalarPointer(0, 0, 0));

		for (int i = 0; i < nScalar; i++)
		{
			scalarPointer[i] = data[i];
			//std::cout << i << " ";
		}

		m_ImageMapper->SetInputData(m_ImageData);
		m_ImageActor->SetMapper(m_ImageMapper);
		//m_Renderer여기서 랜더러에 있는 actor을 지우고 해야하나.?
		m_Renderer->AddActor2D(m_ImageActor);

		//m_Renderer->GetActiveCamera()->SetFocalPoint(m_ImageData->GetCenter());
		//m_Renderer->GetActiveCamera()->SetPosition(m_ImageData->GetCenter()[0], m_ImageData->GetCenter()[1], 100000.0);
		m_Renderer->ResetCamera();
		m_Renderer->Modified();
		m_RenWin->Render();

		//_sleep(100);
	}

}