
#include"DepthMapPreviewer.h"
DepthMapPreviewer::DepthMapPreviewer()
{
	InitializeVariables();
}

DepthMapPreviewer::~DepthMapPreviewer()
{
	DestroyVariables();
}

void DepthMapPreviewer::ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize)
{
	m_RenWin->SetParentId(uiCtrl);
	m_RenWin->SetSize(xCtrlSize, yCtrlSize);
}

int DepthMapPreviewer::CreateModel(std::string imagePath, int extType)
{
	if (!m_ImageData)
		return 0;

	//m_ImageIO->ImportImage(extType, imagePath, m_ImageData);
	m_ImageData->Modified();

//	m_ImageMapper->SetInputData(m_ImageData);
//	m_ImageMapper->Modified();

	//m_ImageActor->GetMapper()
	//m_ImageActor->SetMapper(m_ImageMapper);
	//m_ImageActor->SetMapper(m_ImageMapper);

	m_ImageActor->GetMapper()->SetInputData(m_ImageData);
	if (extType == 4)
	{
		//m_ImageActor->GetProperty()->SetColorWindow(m_ImageIO->m_wl[0]);
		//m_ImageActor->GetProperty()->SetColorLevel(m_ImageIO->m_wl[1]);
	}
	m_ImageActor->GetProperty()->SetColorWindow(1500);
	m_ImageActor->GetProperty()->SetColorLevel(500);
	m_ImageActor->Modified();

	m_Renderer->AddActor(m_ImageActor);
	m_Renderer->GetActiveCamera()->SetFocalPoint(m_ImageData->GetCenter());
	m_Renderer->GetActiveCamera()->SetPosition(m_ImageData->GetCenter()[0], m_ImageData->GetCenter()[1], 100000.0);
	m_Renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
	m_Renderer->ResetCamera();
	m_Renderer->Modified();
	//m_filePath = imagePath;

	return 1;
}

int DepthMapPreviewer::ReleaseModel()
{
	m_Renderer->RemoveActor(m_ImageActor);

	if (m_ImageActor)
	{
		m_ImageActor->Delete();
		m_ImageActor = NULL;
		m_ImageActor = vtkImageActor::New();
	}
	/*if (m_ImageMapper)
	{
		m_ImageMapper->Delete();
		m_ImageMapper = NULL;
		m_ImageMapper = vtkImageMapper3D::New();
	}*/
	if (m_ImageData)
	{
		m_ImageData->ReleaseData();
		m_ImageData->Delete();
		m_ImageData = NULL;
		m_ImageData = vtkImageData::New();
	}

	return 1;
}

int DepthMapPreviewer::Create2DScene()
{
	m_Renderer->GetActiveCamera()->ParallelProjectionOff();

	m_2DStyle->SetInteractionModeToImage2D();
	m_RenWin->AddRenderer(m_Renderer);
	m_IRen->SetInteractorStyle(m_2DStyle);
	m_RenWin->SetInteractor(m_IRen);
	m_RenWin->Modified();

	return 1;
}



int DepthMapPreviewer::InitializeVariables()
{
	//m_ImageIO = NULL;
	m_ImageData = NULL;
	m_ImageActor = NULL;
	m_ImageActor = NULL;
	m_Renderer = NULL;
	m_RenWin = NULL;
	m_IRen = NULL;
	m_2DStyle = NULL;

	//m_ImageIO = new ImageIO;

	m_ImageData = vtkImageData::New();
	//m_ImageMapper = vtkImageMapper3D::New();
	m_ImageActor = vtkImageActor::New();
	m_Renderer = vtkRenderer::New();
	m_RenWin = vtkRenderWindow::New();
	m_IRen = vtkRenderWindowInteractor::New();
	m_2DStyle = vtkInteractorStyleImage::New();

	return 1;
}

int DepthMapPreviewer::DestroyVariables()
{
	/*if (m_ImageIO)
	{
		delete m_ImageIO;
		m_ImageIO = NULL;
	}*/
	if (m_ImageData)
	{
		m_ImageData->ReleaseData();
		m_ImageData->Delete();
		m_ImageData = NULL;
	}
	/*if (m_ImageMapper)
	{
		m_ImageMapper->Delete();
		m_ImageMapper = NULL;
	}*/
	if (m_ImageActor)
	{
		m_ImageActor->Delete();
		m_ImageActor = NULL;
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
	if (m_2DStyle)
	{
		m_2DStyle->Delete();
		m_2DStyle = NULL;
	}

	return 1;
}

//int DepthMapPreviewer::CaptureSave(std::string imagePath, int extType, int sizeRatio)
//{
//	m_ImageIO->CaptureSaveImageFile(m_RenWin, extType, sizeRatio, imagePath);
//	m_RenWin->Render();
//
//	return 1;
//}
//
//int DepthMapPreviewer::ImageSave(std::string imagePath, int extType)
//{
//	m_ImageIO->ExportImageFile(extType, m_ImageData, imagePath);
//
//	return 1;
//}

void DepthMapPreviewer::Rendering()
{
	m_RenWin->Render();
}
