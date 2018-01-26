#pragma warning (disable:4996)

#include "STLImport.h"

#include "vtkByteSwap.h"
#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkErrorCode.h"
#include "vtkFloatArray.h"
#include "vtkIncrementalPointLocator.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkMergePoints.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <vtk-8.1/vtksys/SystemTools.hxx>

vtkStandardNewMacro(STLImport);

#define VTK_ASCII 0
#define VTK_BINARY 1

vtkCxxSetObjectMacro(STLImport, Locator, vtkIncrementalPointLocator);

STLImport::STLImport()
{
	this->FileName = NULL;
	this->Merging = 1;
	this->ScalarTags = 0;
	this->Locator = NULL;

	this->SetNumberOfInputPorts(0);
}

STLImport::~STLImport()
{
	this->SetFileName(0);
	this->SetLocator(0);
}

vtkMTimeType STLImport::GetMTime()
{
	vtkMTimeType mTime1 = this->Superclass::GetMTime();

	if (this->Locator)
	{
		vtkMTimeType mTime2 = this->Locator->GetMTime();
		mTime1 = std::max(mTime1, mTime2);
	}

	return mTime1;
}

int STLImport::RequestData(vtkInformation *vtkNotUsed(request), vtkInformationVector **vtkNotUsed(inputVector), vtkInformationVector *outputVector)
{
	vtkInformation *outInfo = outputVector->GetInformationObject(0);
	vtkPolyData *output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

	if (outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER()) > 0)
	{
		return 0;
	}

	if (!this->FileName || *this->FileName == 0)
	{
		vtkErrorMacro(<< "A FileName must be specified.");
		this->SetErrorCode(vtkErrorCode::NoFileNameError);
		return 0;
	}

	// Initialize
	FILE *fp = fopen(this->FileName, "r");
	if (fp == NULL)
	{
		vtkErrorMacro(<< "File " << this->FileName << " not found");
		this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
		return 0;
	}

	vtkPoints *newPts = vtkPoints::New();
	vtkCellArray *newPolys = vtkCellArray::New();
	vtkFloatArray *newScalars = 0;

	if (this->GetSTLFileType(this->FileName) == VTK_ASCII)
	{
		newPts->Allocate(5000);
		newPolys->Allocate(10000);
		if (this->ScalarTags)
		{
			newScalars = vtkFloatArray::New();
			newScalars->Allocate(5000);
		}
		if (!this->ReadASCIISTL(fp, newPts, newPolys, newScalars))
		{
			fclose(fp);
			return 0;
		}
	}
	else
	{
		fclose(fp);
		fp = fopen(this->FileName, "rb");
		if (fp == NULL)
		{
			vtkErrorMacro(<< "File " << this->FileName << " not found");
			this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
			return 0;
		}

		if (!this->ReadBinarySTL(fp, newPts, newPolys))
		{
			fclose(fp);
			return 0;
		}
	}

	vtkDebugMacro(<< "Read: " << newPts->GetNumberOfPoints() << " points, " << newPolys->GetNumberOfCells() << " triangles");

	fclose(fp);

	vtkPoints *mergedPts = newPts;
	vtkCellArray *mergedPolys = newPolys;
	vtkFloatArray *mergedScalars = newScalars;
	if (this->Merging)
	{
		mergedPts = vtkPoints::New();
		mergedPts->Allocate(newPts->GetNumberOfPoints() / 2);
		mergedPolys = vtkCellArray::New();
		mergedPolys->Allocate(newPolys->GetSize());
		if (newScalars)
		{
			mergedScalars = vtkFloatArray::New();
			mergedScalars->Allocate(newPolys->GetSize());
		}

		vtkSmartPointer<vtkIncrementalPointLocator> locator = this->Locator;
		if (this->Locator == NULL)
		{
			locator.TakeReference(this->NewDefaultLocator());
		}
		locator->InitPointInsertion(mergedPts, newPts->GetBounds());

		int nextCell = 0;
		vtkIdType *pts = 0;
		vtkIdType npts;
		for (newPolys->InitTraversal(); newPolys->GetNextCell(npts, pts);)
		{
			vtkIdType nodes[3];
			for (int i = 0; i < 3; i++)
			{
				double x[3];
				newPts->GetPoint(pts[i], x);
				locator->InsertUniquePoint(x, nodes[i]);
			}

			if (nodes[0] != nodes[1] && nodes[0] != nodes[2] && nodes[1] != nodes[2])
			{
				mergedPolys->InsertNextCell(3, nodes);
				if (newScalars)
				{
					mergedScalars->InsertNextValue(newScalars->GetValue(nextCell));
				}
			}
			nextCell++;
		}

		newPts->Delete();
		newPolys->Delete();
		if (newScalars)
		{
			newScalars->Delete();
		}

		vtkDebugMacro(<< "Merged to: " << mergedPts->GetNumberOfPoints() << " points, " << mergedPolys->GetNumberOfCells() << " triangles");
	}

	output->SetPoints(mergedPts);
	mergedPts->Delete();

	output->SetPolys(mergedPolys);
	mergedPolys->Delete();

	if (mergedScalars)
	{
		mergedScalars->SetName("STLSolidLabeling");
		output->GetCellData()->SetScalars(mergedScalars);
		mergedScalars->Delete();
	}

	if (this->Locator)
	{
		this->Locator->Initialize();
	}

	output->Squeeze();

	return 1;
}

bool STLImport::ReadBinarySTL(FILE *fp, vtkPoints *newPts, vtkCellArray *newPolys)
{
	typedef struct { float  n[3], v1[3], v2[3], v3[3]; } facet_t;

	vtkDebugMacro(<< "Reading BINARY STL file");

	char header[81];
	if (fread(header, 1, 80, fp) != 80)
	{
		vtkErrorMacro("STLReader error reading file: " << this->FileName << " Premature EOF while reading header.");
		return false;
	}

	unsigned long ulint;
	if (fread(&ulint, 1, 4, fp) != 4)
	{
		vtkErrorMacro("STLReader error reading file: " << this->FileName << " Premature EOF while reading header.");
		return false;
	}
	vtkByteSwap::Swap4LE(&ulint);

	int numTris = static_cast<int>(ulint);
	if (numTris <= 0)
	{
		vtkDebugMacro(<< "Bad binary count: attempting to correct(" << numTris << ")");
	}

	unsigned long ulFileLength = vtksys::SystemTools::FileLength(this->FileName);
	ulFileLength -= (80 + 4);
	ulFileLength /= 50;

	if (numTris < static_cast<int>(ulFileLength))
	{
		numTris = static_cast<int>(ulFileLength);
	}

	newPts->Allocate(numTris * 3);
	newPolys->Allocate(numTris);

	facet_t facet;
	for (int i = 0; fread(&facet, 48, 1, fp) > 0; i++)
	{
		unsigned short ibuff2;
		if (fread(&ibuff2, 2, 1, fp) != 1)
		{
			vtkErrorMacro("STLReader error reading file: " << this->FileName << " Premature EOF while reading extra junk.");
			return false;
		}

		vtkByteSwap::Swap4LE(facet.n);
		vtkByteSwap::Swap4LE(facet.n + 1);
		vtkByteSwap::Swap4LE(facet.n + 2);

		vtkByteSwap::Swap4LE(facet.v1);
		vtkByteSwap::Swap4LE(facet.v1 + 1);
		vtkByteSwap::Swap4LE(facet.v1 + 2);

		vtkByteSwap::Swap4LE(facet.v2);
		vtkByteSwap::Swap4LE(facet.v2 + 1);
		vtkByteSwap::Swap4LE(facet.v2 + 2);

		vtkByteSwap::Swap4LE(facet.v3);
		vtkByteSwap::Swap4LE(facet.v3 + 1);
		vtkByteSwap::Swap4LE(facet.v3 + 2);

		vtkIdType pts[3];
		pts[0] = newPts->InsertNextPoint(facet.v1);
		pts[1] = newPts->InsertNextPoint(facet.v2);
		pts[2] = newPts->InsertNextPoint(facet.v3);

		newPolys->InsertNextCell(3, pts);

		if ((i % 5000) == 0 && i != 0)
		{
			vtkDebugMacro(<< "triangle# " << i);
			this->UpdateProgress(static_cast<double>(i) / numTris);
		}
	}

	return true;
}

bool STLImport::ReadASCIISTL(FILE *fp, vtkPoints *newPts, vtkCellArray *newPolys, vtkFloatArray *scalars)
{
	vtkDebugMacro(<< "Reading ASCII STL file");

	char line[256];
	float x[3];
	int currentSolid = 0;

	// header
	if (!fgets(line, 255, fp))
	{
		vtkErrorMacro("STLReader error reading file: " << this->FileName << " Premature EOF while reading header at line 0.");
		return false;
	}

	int done = !fgets(line, 255, fp);
	int lineCount = 2;
	if (strstr(line, "COLOR") || strstr(line, "color"))
	{
		done = !fgets(line, 255, fp);
		lineCount++;
	}

	try
	{
		while (!done)
		{
			vtkIdType pts[3];

			if (!fgets(line, 255, fp))
			{
				throw std::runtime_error("unable to read STL outer loop.");
			}
			lineCount++;

			if (fscanf(fp, "%*s %f %f %f\n", x, x + 1, x + 2) != 3)
			{
				throw std::runtime_error("unable to read STL vertex.");
			}
			lineCount++;
			pts[0] = newPts->InsertNextPoint(x);

			if (fscanf(fp, "%*s %f %f %f\n", x, x + 1, x + 2) != 3)
			{
				throw std::runtime_error("unable to read STL vertex.");
			}
			lineCount++;
			pts[1] = newPts->InsertNextPoint(x);

			if (fscanf(fp, "%*s %f %f %f\n", x, x + 1, x + 2) != 3)
			{
				throw std::runtime_error("unable to read STL vertex.");
			}
			lineCount++;
			pts[2] = newPts->InsertNextPoint(x);

			if (!fgets(line, 255, fp))
			{
				throw std::runtime_error("unable to read STL endloop.");
			}
			lineCount++;

			if (!fgets(line, 255, fp))
			{
				throw std::runtime_error("unable to read STL endfacet.");
			}
			lineCount++;

			newPolys->InsertNextCell(3, pts);
			if (scalars)
			{
				scalars->InsertNextValue(currentSolid);
			}

			if ((newPolys->GetNumberOfCells() % 5000) == 0)
			{
				this->UpdateProgress((newPolys->GetNumberOfCells() % 50000) / 50000.0);
			}

			done = (fscanf(fp, "%255s", line) == EOF);
			if (!strcmp(line, "ENDSOLID") || !strcmp(line, "endsolid"))
			{
				currentSolid++;
				if (!fgets(line, 255, fp) && !feof(fp))
				{
					throw std::runtime_error("unable to read STL endsolid.");
				}

				done = feof(fp);
				while (!strstr(line, "SOLID") && !strstr(line, "solid") && !done)
				{
					if (!fgets(line, 255, fp))
					{
						done = feof(fp);
						if (!done)
						{
							throw std::runtime_error("unable to read STL solid.");
						}
					}
					lineCount++;
					done = feof(fp);
				}

				done = (fscanf(fp, "%255s", line) == EOF);
				if (!strcmp(line, "COLOR") || !strcmp(line, "color"))
				{
					done = !fgets(line, 255, fp);
					lineCount++;
				}

				if (!done)
				{
					done = !fgets(line, 255, fp);
					lineCount++;
				}
			}
			else if (!done)
			{
				done = !fgets(line, 255, fp);
				lineCount++;
			}
		}
	}
	catch (const std::runtime_error &e)
	{
		vtkErrorMacro("STLReader: error while reading file " <<
			this->FileName << " at line " << lineCount << ": " << e.what());
		return false;
	}

	return true;
}

int STLImport::GetSTLFileType(const char *filename)
{
	vtksys::SystemTools::FileTypeEnum ft =
		vtksys::SystemTools::DetectFileType(filename);
	switch (ft)
	{
	case vtksys::SystemTools::FileTypeBinary:
		return VTK_BINARY;
	case vtksys::SystemTools::FileTypeText:
		return VTK_ASCII;
	case vtksys::SystemTools::FileTypeUnknown:
		vtkWarningMacro("File type not recognized; attempting binary");
		return VTK_BINARY;
	default:
		vtkErrorMacro("Case not handled, file type is " << static_cast<int>(ft));
		return VTK_BINARY; // should not happen
	}
}

vtkIncrementalPointLocator* STLImport::NewDefaultLocator()
{
	return vtkMergePoints::New();
}
