#include "ImagePreview.h"

#include "ImageIO.h"

ImagePreview::ImagePreview()
{
	InitializeVariables();
}

ImagePreview::~ImagePreview()
{
	DestroyVariables();
}

void ImagePreview::ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize)
{
	m_RenWin->SetParentId(uiCtrl);
	m_RenWin->SetSize(xCtrlSize, yCtrlSize);
}

int ImagePreview::CreateModel(std::string imagePath, int extType)
{
	if (!m_ImageData)
		return 0;

	m_ImageIO->ImportImage(extType, imagePath, m_ImageData);
	m_ImageData->Modified();

	m_Mapper->SetInputData(m_ImageData);
	m_Mapper->Modified();

	m_Actor->SetMapper(m_Mapper);

	if (extType == 4)
	{
		m_Actor->GetProperty()->SetColorWindow(m_ImageIO->m_wl[0]);
		m_Actor->GetProperty()->SetColorLevel(m_ImageIO->m_wl[1]);
	}
	m_Actor->Modified();

	m_Renderer->AddActor(m_Actor);
	m_Renderer->GetActiveCamera()->SetFocalPoint(m_ImageData->GetCenter());
	m_Renderer->GetActiveCamera()->SetPosition(m_ImageData->GetCenter()[0], m_ImageData->GetCenter()[1], 100000.0);
	m_Renderer->GetActiveCamera()->SetViewUp(0,1,0);
	m_Renderer->ResetCamera();
	m_Renderer->Modified();
	m_filePath = imagePath;

	return 1;
}

int ImagePreview::ReleaseModel()
{
	m_Renderer->RemoveActor(m_Actor);

	if (m_Actor)
	{
		m_Actor->Delete();
		m_Actor = NULL;
		m_Actor = vtkImageSlice::New();
	}
	if (m_Mapper)
	{
		m_Mapper->Delete();
		m_Mapper = NULL;
		m_Mapper = vtkImageResliceMapper::New();
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

int ImagePreview::Create2DScene()
{
	m_Renderer->GetActiveCamera()->ParallelProjectionOff();

	m_RenWin->AddRenderer(m_Renderer);
	m_IRen->SetInteractorStyle(m_2DStyle);
	m_RenWin->SetInteractor(m_IRen);
	m_RenWin->Modified();

	return 1;
}



int ImagePreview::InitializeVariables()
{
	m_ImageIO = NULL;
	m_ImageData = NULL;
	m_Mapper = NULL;
	m_Actor = NULL;
	m_Renderer = NULL;
	m_RenWin = NULL;
	m_IRen = NULL;
	m_2DStyle = NULL;

	m_ImageIO = new ImageIO;

	m_ImageData = vtkImageData::New();
	m_Mapper = vtkImageResliceMapper::New();
	m_Actor = vtkImageSlice::New();
	m_Renderer = vtkRenderer::New();
	m_RenWin = vtkRenderWindow::New();
	m_IRen = vtkRenderWindowInteractor::New();
	m_2DStyle = vtkInteractorStyleImage::New();

	return 1;
}

int ImagePreview::DestroyVariables()
{
	if (m_ImageIO)
	{
		delete m_ImageIO;
		m_ImageIO = NULL;
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
	if (m_2DStyle)
	{
		m_2DStyle->Delete();
		m_2DStyle = NULL;
	}

	return 1;
}

int ImagePreview::CaptureSave(std::string imagePath, int extType, int sizeRatio)
{
	m_ImageIO->CaptureSaveImageFile(m_RenWin, extType, sizeRatio, imagePath);
	m_RenWin->Render();

	return 1;
}

int ImagePreview::ImageSave(std::string imagePath, int extType)
{
	m_ImageIO->ExportImageFile(extType, m_ImageData, imagePath);

	return 1;
}

void ImagePreview::Rendering()
{
	m_RenWin->Render();
}
