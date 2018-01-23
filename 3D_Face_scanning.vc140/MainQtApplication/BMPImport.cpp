#include "BMPImport.h"

#include "vtk-8.1\vtkByteSwap.h"
#include "vtk-8.1\vtkImageData.h"
#include "vtk-8.1\vtkLookupTable.h"
#include "vtk-8.1\vtkObjectFactory.h"
#include "vtk-8.1\vtkPointData.h"

vtkStandardNewMacro(BMPImport);

#ifdef read
#undef read
#endif

#ifdef close
#undef close
#endif

BMPImport::BMPImport()
{
	this->Colors = NULL;
	this->SetDataByteOrderToLittleEndian();
	this->Depth = 0;
	this->LookupTable = vtkLookupTable::New();
	this->Allow8BitBMP = 0;
}

BMPImport::~BMPImport()
{
	delete[] this->Colors;
	this->Colors = NULL;

	if (this->LookupTable)
	{
		this->LookupTable->Delete();
		this->LookupTable = NULL;
	}
}

void BMPImport::ExecuteInformation()
{
	int xsize, ysize;
	FILE *fp;
	vtkTypeInt32 tmp;
	vtkTypeInt32 offset;
	vtkTypeInt32 infoSize;
	vtkTypeInt16 stmp1, stmp2;

	delete[] this->Colors;
	this->Colors = NULL;

	if (this->DataExtent[4] == 0 && this->DataExtent[5] == 0 &&
		(this->DataVOI[4] || this->DataVOI[5]))
	{
		this->DataExtent[4] = this->DataVOI[4];
		this->DataExtent[5] = this->DataVOI[5];
	}

	this->ComputeInternalFileName(this->DataExtent[4]);
	if (this->InternalFileName == NULL || this->InternalFileName[0] == '\0')
	{
		return;
	}
	fp = fopen(this->InternalFileName, "rb");
	if (!fp)
	{
		vtkErrorMacro("Unable to open file " << this->InternalFileName);
		return;
	}

	if ((fgetc(fp) != 'B') || (fgetc(fp) != 'M'))
	{
		vtkErrorMacro(<< "Unknown file type! " << this->InternalFileName
			<< " is not a Windows BMP file!");
		fclose(fp);
		return;
	}

	bool errorOccurred = false;

	if (fread(&tmp, 4, 1, fp) != 1)
	{
		errorOccurred = true;
	}
	else if (fread(&tmp, 4, 1, fp) != 1)
	{
		errorOccurred = true;
	}
	else if (fread(&offset, 4, 1, fp) != 1)
	{
		errorOccurred = true;
	}
	else if (fread(&infoSize, 4, 1, fp) != 1)
	{
		errorOccurred = true;
	}

	if (errorOccurred)
	{
		vtkErrorMacro("Error reading file: " << this->InternalFileName
			<< " Premature end of file.");
		fclose(fp);
		return;
	}

	vtkByteSwap::Swap4LE(&infoSize);

	if ((infoSize != 40) && (infoSize != 12))
	{
		vtkErrorMacro("Unknown file type! " << this->InternalFileName
			<< " is not a Windows BMP file!");
		fclose(fp);
		return;
	}

	if (infoSize == 40)
	{
		if (fread(&xsize, 4, 1, fp) != 1)
		{
			errorOccurred = true;
		}
		else if (fread(&ysize, 4, 1, fp) != 1)
		{
			errorOccurred = true;
		}
		vtkByteSwap::Swap4LE(&xsize);
		vtkByteSwap::Swap4LE(&ysize);
	}
	else
	{
		if (fread(&stmp1, 2, 1, fp) != 1)
		{
			errorOccurred = true;
		}
		else if (fread(&stmp2, 2, 1, fp) != 1)
		{
			errorOccurred = true;
		}
		vtkByteSwap::Swap2LE(&stmp1);
		vtkByteSwap::Swap2LE(&stmp2);
		xsize = stmp1;
		ysize = stmp2;
	}

	if (errorOccurred)
	{
		vtkErrorMacro("BMPReader error reading file: " << this->InternalFileName
			<< " Premature EOF while reading size.");
		fclose(fp);
		return;
	}

	if (ysize < 0)
	{
		ysize = ysize*-1;
		this->FileLowerLeft = 0;
	}
	else
	{
		this->FileLowerLeft = 1;
	}

	if (fread(&stmp1, 2, 1, fp) != 1)
	{
		errorOccurred = true;
	}
	else if (fread(&stmp2, 2, 1, fp) != 1)
	{
		errorOccurred = true;
	}

	if (errorOccurred)
	{
		vtkErrorMacro("BMPReader error reading file: " << this->InternalFileName
			<< " Premature EOF while reading depth.");
		fclose(fp);
		return;
	}

	vtkByteSwap::Swap2LE(&stmp2);
	this->Depth = stmp2;

	if ((this->Depth != 8) && (this->Depth != 24))
	{
		vtkErrorMacro("Only BMP depths of (8,24) are supported. Not "
			<< this->Depth);
		fclose(fp);
		return;
	}

	if (infoSize == 40)
	{
		int skip[6];
		if (fread(&skip, 4, 6, fp) != 6)
		{
			vtkErrorMacro("BMPReader error reading file: " << this->InternalFileName
				<< " Premature EOF skipping rest of info for long format.");
			fclose(fp);
			return;
		}
	}

	if (this->Depth < 24)
	{
		int numColors = 256;
		this->Colors = new unsigned char[numColors * 3];
		for (tmp = 0; tmp < numColors; tmp++)
		{
			this->Colors[tmp * 3 + 2] = fgetc(fp);
			this->Colors[tmp * 3 + 1] = fgetc(fp);
			this->Colors[tmp * 3] = fgetc(fp);
			if (infoSize == 40)
			{
				fgetc(fp);
			}
		}
		if (this->Allow8BitBMP)
		{
			if (!this->LookupTable)
			{
				this->LookupTable = vtkLookupTable::New();
			}
			this->LookupTable->SetNumberOfTableValues(numColors);
			for (tmp = 0; tmp<numColors; tmp++)
			{
				this->LookupTable->SetTableValue(tmp,
					(float)this->Colors[tmp * 3 + 0] / 255.0,
					(float)this->Colors[tmp * 3 + 1] / 255.0,
					(float)this->Colors[tmp * 3 + 2] / 255.0,
					1);
			}
			this->LookupTable->SetRange(0, 255);
		}
	}

	if (fclose(fp))
	{
		vtkWarningMacro("File close failed on " << this->InternalFileName);
	}

	vtkByteSwap::Swap4LE(&offset);
	this->ManualHeaderSize = 1;
	this->HeaderSize = offset;

	if (this->DataVOI[0] || this->DataVOI[1] ||
		this->DataVOI[2] || this->DataVOI[3] ||
		this->DataVOI[4] || this->DataVOI[5])
	{
		if ((this->DataVOI[0] < 0) ||
			(this->DataVOI[1] >= xsize) ||
			(this->DataVOI[2] < 0) ||
			(this->DataVOI[3] >= ysize))
		{
			vtkWarningMacro("The requested VOI is larger than the file's (" << this->InternalFileName << ") extent ");
			this->DataVOI[0] = 0;
			this->DataVOI[1] = xsize - 1;
			this->DataVOI[2] = 0;
			this->DataVOI[3] = ysize - 1;
		}
	}

	this->DataExtent[0] = 0;
	this->DataExtent[1] = xsize - 1;
	this->DataExtent[2] = 0;
	this->DataExtent[3] = ysize - 1;

	this->SetDataScalarTypeToUnsignedChar();
	if ((this->Depth == 8) && this->Allow8BitBMP)
	{
		this->SetNumberOfScalarComponents(1);
	}
	else
	{
		this->SetNumberOfScalarComponents(3);
	}

	this->vtkImageReader::ExecuteInformation();
}

void BMPImport::ComputeDataIncrements()
{
	int idx;
	vtkIdType fileDataLength;

	switch (this->DataScalarType)
	{
	case VTK_FLOAT:
		fileDataLength = sizeof(float);
		break;
	case VTK_INT:
		fileDataLength = sizeof(int);
		break;
	case VTK_SHORT:
		fileDataLength = sizeof(short);
		break;
	case VTK_UNSIGNED_SHORT:
		fileDataLength = sizeof(unsigned short);
		break;
	case VTK_UNSIGNED_CHAR:
		fileDataLength = sizeof(unsigned char);
		break;
	default:
		vtkErrorMacro(<< "Unknown DataScalarType");
		return;
	}

	fileDataLength *= (this->Depth / 8);

	this->DataIncrements[0] = fileDataLength;
	fileDataLength = fileDataLength *
		(this->DataExtent[1] - this->DataExtent[0] + 1);
	fileDataLength = fileDataLength + (4 - fileDataLength % 4) % 4;

	for (idx = 1; idx < 3; ++idx)
	{
		this->DataIncrements[idx] = fileDataLength;
		fileDataLength = fileDataLength *
			(this->DataExtent[idx * 2 + 1] - this->DataExtent[idx * 2] + 1);
	}
}

template <class OT>
void BMPImportUpdate2(BMPImport *self, vtkImageData *data, OT *outPtr)
{
	vtkIdType inIncr[3], outIncr[3];
	OT *outPtr0, *outPtr1, *outPtr2;
	vtkIdType streamSkip0, streamSkip1;
	vtkIdType streamRead;
	int idx0, idx1, idx2, pixelRead;
	int inExtent[6];
	int dataExtent[6];
	int pixelSkip;
	unsigned char *inPtr;
	unsigned char *Colors;
	unsigned long count = 0;
	unsigned long target;
	int Keep8bit = 0;

	data->GetExtent(inExtent);
	self->ComputeInverseTransformedExtent(inExtent, dataExtent);

	data->GetIncrements(inIncr);
	self->ComputeInverseTransformedIncrements(inIncr, outIncr);

	Colors = self->GetColors();

	if ((self->GetDepth() == 8) && self->GetAllow8BitBMP())
	{
		Keep8bit = 1;
	}

	outPtr2 = outPtr;
	if (outIncr[0] < 0)
	{
		outPtr2 = outPtr2 - outIncr[0] * (dataExtent[1] - dataExtent[0]);
	}
	if (outIncr[1] < 0)
	{
		outPtr2 = outPtr2 - outIncr[1] * (dataExtent[3] - dataExtent[2]);
	}
	if (outIncr[2] < 0)
	{
		outPtr2 = outPtr2 - outIncr[2] * (dataExtent[5] - dataExtent[4]);
	}

	pixelRead = dataExtent[1] - dataExtent[0] + 1;
	streamRead = (vtkIdType)(pixelRead * self->GetDataIncrements()[0]);
	streamSkip0 = (vtkIdType)(self->GetDataIncrements()[1] - streamRead);
	streamSkip1 = (vtkIdType)(self->GetDataIncrements()[2] -
		(dataExtent[3] - dataExtent[2] + 1)* self->GetDataIncrements()[1]);
	pixelSkip = self->GetDepth() / 8;

	if (!self->GetFileLowerLeft())
	{
		streamSkip0 = (vtkIdType)(-streamRead - self->GetDataIncrements()[1]);
	}

	target = (unsigned long)((dataExtent[5] - dataExtent[4] + 1)*
		(dataExtent[3] - dataExtent[2] + 1) / 50.0);
	target++;

	if (self->GetFileDimensionality() == 3)
	{
		if (!self->OpenAndSeekFile(dataExtent, 0))
		{
			return;
		}
	}

	unsigned char *buf = new unsigned char[streamRead];

	for (idx2 = dataExtent[4]; idx2 <= dataExtent[5]; ++idx2)
	{
		if (self->GetFileDimensionality() == 2)
		{
			if (!self->OpenAndSeekFile(dataExtent, idx2))
			{
				delete[] buf;
				return;
			}
		}
		outPtr1 = outPtr2;
		for (idx1 = dataExtent[2];
			!self->AbortExecute && idx1 <= dataExtent[3]; ++idx1)
		{
			if (!(count%target))
			{
				self->UpdateProgress(count / (50.0*target));
			}
			count++;
			outPtr0 = outPtr1;

			// read the row.
			if (!self->GetFile()->read((char *)buf, streamRead))
			{
				vtkErrorWithObjectMacro(self,
					"File operation failed. row = " << idx1
					<< ", Read = " << streamRead
					<< ", Skip0 = " << streamSkip0
					<< ", Skip1 = " << streamSkip1
					<< ", FilePos = " << static_cast<vtkIdType>(self->GetFile()->tellg())
					<< ", FileName = " << self->GetInternalFileName()
				);
				self->GetFile()->close();
				delete[] buf;
				return;
			}

			inPtr = buf;
			for (idx0 = dataExtent[0]; idx0 <= dataExtent[1]; ++idx0)
			{
				if (self->GetDepth() == 8 && !Keep8bit)
				{
					outPtr0[0] = (OT)(Colors[inPtr[0] * 3]);
					outPtr0[1] = (OT)(Colors[inPtr[0] * 3 + 1]);
					outPtr0[2] = (OT)(Colors[inPtr[0] * 3 + 2]);
				}
				else if (self->GetDepth() == 8 && Keep8bit)
				{
					outPtr0[0] = (OT)(inPtr[0]);
				}
				else
				{
					outPtr0[0] = (OT)(inPtr[2]);
					outPtr0[1] = (OT)(inPtr[1]);
					outPtr0[2] = (OT)(inPtr[0]);
				}
				inPtr += pixelSkip;
				outPtr0 += outIncr[0];
			}
			self->GetFile()->seekg(static_cast<long>(self->GetFile()->tellg()) + streamSkip0, ios::beg);
			outPtr1 += outIncr[1];
		}
		self->GetFile()->seekg(static_cast<long>(self->GetFile()->tellg()) + streamSkip1, ios::beg);
		outPtr2 += outIncr[2];
	}

	self->GetFile()->close();

	delete[] buf;
}

void BMPImport::ExecuteDataWithInformation(vtkDataObject *output,
	vtkInformation* outInfo)
{
	vtkImageData *data = this->AllocateOutputData(output, outInfo);

	if (this->UpdateExtentIsEmpty(outInfo, output))
	{
		return;
	}
	if (this->InternalFileName == NULL)
	{
		vtkErrorMacro(<< "Either a FileName or FilePrefix must be specified.");
		return;
	}

	data->GetPointData()->GetScalars()->SetName("BMPImage");

	this->ComputeDataIncrements();

	void *outPtr;

	outPtr = data->GetScalarPointer();
	switch (data->GetScalarType())
	{
		vtkTemplateMacro(
			BMPImportUpdate2(this, data, static_cast<VTK_TT*>(outPtr))
		);
	default:
		vtkErrorMacro(<< "Execute: Unknown data type");
	}
}

int BMPImport::CanReadFile(const char* fname)
{
	FILE* fp = fopen(fname, "rb");
	if (!fp)
	{
		return 0;
	}

	if ((fgetc(fp) != 'B') || (fgetc(fp) != 'M'))
	{
		fclose(fp);
		return 0;
	}

	vtkTypeInt32 tmp;
	vtkTypeInt32 infoSize = 0;

	bool errorOccurred = false;

	if (fread(&tmp, 4, 1, fp) != 1)
	{
		errorOccurred = true;
	}
	else if (fread(&tmp, 4, 1, fp) != 1)
	{
		errorOccurred = true;
	}
	else if (fread(&tmp, 4, 1, fp) != 1)
	{
		errorOccurred = true;
	}
	else if (fread(&infoSize, 4, 1, fp) != 1)
	{
		infoSize = 0;
		errorOccurred = true;
	}

	vtkByteSwap::Swap4LE(&infoSize);

	if ((infoSize != 40) && (infoSize != 12))
	{
		errorOccurred = true;
	}

	fclose(fp);
	return !errorOccurred;
}
