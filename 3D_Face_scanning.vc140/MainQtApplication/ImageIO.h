#pragma once

#include "BMPImport.h"
#include "JPGImport.h"
#include "PNGImport.h"
#include "BMPExport.h"
#include "JPGExport.h"
#include "PNGExport.h"

#include <vtkTIFFReader.h>
#include <vtkTIFFWriter.h>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkWindowToImageFilter.h>


class ImageIO
{
public:
	ImageIO();
	~ImageIO();

	double m_wl[2];

	int ImportBMPFile(std::string imagePath, vtkImageData* data);
	int ImportJPGFile(std::string imagePath, vtkImageData* data);
	int ImportPNGFile(std::string imagePath, vtkImageData* data);
	int ImportTIFFile(std::string imagePath, vtkImageData* data);
	int ImportImage(int extType, std::string imagePath, vtkImageData* data);//0 bmp, 1 jpg, 2 png, 3 tif 4 dcmSingle

	int ExportBMPFile(vtkImageData* data, std::string imagePath);
	int ExportJPGFile(vtkImageData* data, std::string imagePath);
	int ExportPNGFile(vtkImageData* data, std::string imagePath);
	int ExportTIFFile(vtkImageData* data, std::string imagePath);
	int ExportImageFile(int extType, vtkImageData* data, std::string imagePath);//0 bmp, 1 jpg, 2 png, 3 tif

	int CaptureSaveImageFile(vtkRenderWindow* renWin, int extType, int sizeRatio, std::string imagePath);//0 bmp, 1 jpg, 2 png, 3 tif
};

