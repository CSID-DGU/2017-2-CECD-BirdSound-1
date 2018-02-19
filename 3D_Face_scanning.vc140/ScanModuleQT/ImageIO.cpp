#include "ImageIO.h"


ImageIO::ImageIO()
{
	m_wl[0] = 3500;
	m_wl[1] = 500;
}

ImageIO::~ImageIO()
{
}

int ImageIO::ImportBMPFile(std::string imagePath, vtkImageData* data)
{
	vtkSmartPointer<BMPImport> reader = vtkSmartPointer<BMPImport>::New();
	reader->SetFileName(imagePath.c_str());
	reader->Update();

	if (data->GetNumberOfPoints())
		data->ReleaseData();

	data->DeepCopy(reader->GetOutput());
	data->Modified();

	int n = data->GetNumberOfPoints();

	return 1;
}

int ImageIO::ImportJPGFile(std::string imagePath, vtkImageData* data)
{
	vtkSmartPointer<JPGImport> reader = vtkSmartPointer<JPGImport>::New();
	reader->SetFileName(imagePath.c_str());
	reader->Update();

	if (data->GetNumberOfPoints())
		data->ReleaseData();

	data->DeepCopy(reader->GetOutput());
	data->Modified();

	return 1;
}

int ImageIO::ImportPNGFile(std::string imagePath, vtkImageData* data)
{
	vtkSmartPointer<PNGImport> reader = vtkSmartPointer<PNGImport>::New();
	reader->SetFileName(imagePath.c_str());
	reader->Update();

	if (data->GetNumberOfPoints())
		data->ReleaseData();

	data->DeepCopy(reader->GetOutput());
	data->Modified();

	return 1;
}

int ImageIO::ImportTIFFile(std::string imagePath, vtkImageData* data)
{
	vtkSmartPointer<vtkTIFFReader> reader = vtkSmartPointer<vtkTIFFReader>::New();
	reader->SetFileName(imagePath.c_str());
	//reader->UpdateInformation();
	//int maxNumPieces = 4;
	//for (int cc = 0; cc < maxNumPieces; cc++)
	//	reader->UpdatePiece(cc, maxNumPieces, 0);
	//reader->UpdateWholeExtent();
	reader->Update();

	if (data->GetNumberOfPoints())
		data->ReleaseData();

	data->DeepCopy(reader->GetOutput());
	data->Modified();

	return 1;
}

int ImageIO::ImportImage(int extType, std::string imagePath, vtkImageData* data)//0 bmp, 1 jpg, 2 png, 3 tif
{
	if (!data)
		return 0;

	if (extType == 0)
		ImportBMPFile(imagePath, data);
	else if (extType == 1)
		ImportJPGFile(imagePath, data);
	else if (extType == 2)
		ImportPNGFile(imagePath, data);
	else if (extType == 3)
		ImportTIFFile(imagePath, data);
	else
		return 0;

	return 1;
}



int ImageIO::ExportBMPFile(vtkImageData* data, std::string imagePath)
{
	vtkSmartPointer<BMPExport> writer = vtkSmartPointer<BMPExport>::New();
	writer->SetInputData(data);
	writer->SetFileName(imagePath.c_str());
	writer->Write();

	return 1;
}

int ImageIO::ExportJPGFile(vtkImageData* data, std::string imagePath)
{
	vtkSmartPointer<JPGExport> writer = vtkSmartPointer<JPGExport>::New();
	writer->SetInputData(data);
	writer->SetFileName(imagePath.c_str());
	writer->Write();

	return 1;
}

int ImageIO::ExportPNGFile(vtkImageData* data, std::string imagePath)
{
	vtkSmartPointer<PNGExport> writer = vtkSmartPointer<PNGExport>::New();
	writer->SetInputData(data);
	writer->SetFileName(imagePath.c_str());
	writer->Write();

	return 1;
}

int ImageIO::ExportTIFFile(vtkImageData* data, std::string imagePath)
{
	vtkSmartPointer<vtkTIFFWriter> writer = vtkSmartPointer<vtkTIFFWriter>::New();
	writer->SetInputData(data);
	writer->SetFileName(imagePath.c_str());
	writer->Write();

	return 1;
}

int ImageIO::ExportImageFile(int extType, vtkImageData* data, std::string imagePath)//0 bmp, 1 jpg, 2 png, 3 tif
{
	if (!data)
		return 0;

	if (extType == 0)
		ExportBMPFile(data, imagePath);
	else if (extType == 1)
		ExportJPGFile(data, imagePath);
	else if (extType == 2)
		ExportPNGFile(data, imagePath);
	else if (extType == 3)
		ExportTIFFile(data, imagePath);
	else
		return 0;

	return 1;
}


int ImageIO::CaptureSaveImageFile(vtkRenderWindow* renWin, int extType, int sizeRatio, std::string imagePath)//0 bmp, 1 jpg, 2 png, 3 tif
{
	vtkSmartPointer<vtkWindowToImageFilter> windowToImage = vtkSmartPointer<vtkWindowToImageFilter>::New();
	windowToImage->SetInput(renWin);
	windowToImage->SetMagnification(sizeRatio); // 화면에 보이는 크기 그대로 찍음//2 862 742  1 431 371
	windowToImage->SetInputBufferTypeToRGB();
	windowToImage->Update();

	ExportImageFile(extType, windowToImage->GetOutput(), imagePath);

	return 1;
}
