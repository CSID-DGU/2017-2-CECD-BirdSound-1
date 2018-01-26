#include "JPGExport.h"

#include "vtkErrorCode.h"
#include "vtkImageData.h"
#include "vtkInformation.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkToolkits.h"
#include "vtkUnsignedCharArray.h"

extern "C" {
#include "vtk_jpeg.h"
#include <setjmp.h>
}

vtkStandardNewMacro(JPGExport);

vtkCxxSetObjectMacro(JPGExport, Result, vtkUnsignedCharArray);

JPGExport::JPGExport()
{
	this->FileLowerLeft = 1;
	this->FileDimensionality = 2;

	this->Quality = 95;
	this->Progressive = 1;
	this->Result = 0;
	this->TempFP = 0;
}

JPGExport::~JPGExport()
{
	if (this->Result)
	{
		this->Result->Delete();
		this->Result = 0;
	}
}

void JPGExport::Write()
{
	this->SetErrorCode(vtkErrorCode::NoError);

	if (this->GetInput() == NULL)
	{
		vtkErrorMacro(<< "Write:Please specify an input!");
		return;
	}
	if (!this->WriteToMemory && !this->FileName && !this->FilePattern)
	{
		vtkErrorMacro(<< "Write:Please specify either a FileName or a file prefix and pattern");
		this->SetErrorCode(vtkErrorCode::NoFileNameError);
		return;
	}

	size_t InternalFileNameSize = (this->FileName ? strlen(this->FileName) : 1) +
		(this->FilePrefix ? strlen(this->FilePrefix) : 1) +
		(this->FilePattern ? strlen(this->FilePattern) : 1) + 10;
	this->InternalFileName = new char[InternalFileNameSize];

	vtkDemandDrivenPipeline::SafeDownCast(this->GetInputExecutive(0, 0))->UpdateInformation();
	int *wExtent;
	wExtent = this->GetInputInformation(0, 0)->Get(
		vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT());
	this->FileNumber = wExtent[4];
	this->MinimumFileNumber = this->MaximumFileNumber = this->FileNumber;
	this->FilesDeleted = 0;
	this->UpdateProgress(0.0);
	for (this->FileNumber = wExtent[4]; this->FileNumber <= wExtent[5];
		++this->FileNumber)
	{
		this->MaximumFileNumber = this->FileNumber;
		int uExtent[6];
		memcpy(uExtent, wExtent, 4 * sizeof(int));
		uExtent[4] = this->FileNumber;
		uExtent[5] = this->FileNumber;
		if (this->FileName)
		{
			sprintf(this->InternalFileName, "%s", this->FileName);
		}
		else
		{
			if (this->FilePrefix)
			{
				sprintf(this->InternalFileName, this->FilePattern,
					this->FilePrefix, this->FileNumber);
			}
			else
			{
				snprintf(this->InternalFileName, InternalFileNameSize,
					this->FilePattern, this->FileNumber);
			}
		}
		this->GetInputAlgorithm()->UpdateExtent(uExtent);
		this->WriteSlice(this->GetInput(), uExtent);
		if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
		{
			vtkErrorMacro("Ran out of disk space; deleting file(s) already written");
			this->DeleteFiles();
			return;
		}
		this->UpdateProgress((this->FileNumber - wExtent[4]) /
			(wExtent[5] - wExtent[4] + 1.0));
	}
	delete[] this->InternalFileName;
	this->InternalFileName = NULL;
}

extern "C"
{
	static void vtkJPEGWriteToMemoryInit(j_compress_ptr cinfo)
	{
		JPGExport *self = JPGExport::SafeDownCast(
			static_cast<vtkObject *>(cinfo->client_data));
		if (self)
		{
			vtkUnsignedCharArray *uc = self->GetResult();
			if (!uc || uc->GetReferenceCount() > 1)
			{
				uc = vtkUnsignedCharArray::New();
				self->SetResult(uc);
				uc->Delete();
				uc->Allocate(10000);
			}
			cinfo->dest->next_output_byte = uc->GetPointer(0);
			cinfo->dest->free_in_buffer = uc->GetSize();
		}
	}
}

extern "C"
{
	static boolean vtkJPEGWriteToMemoryEmpty(j_compress_ptr cinfo)
	{
		JPGExport *self = JPGExport::SafeDownCast(
			static_cast<vtkObject *>(cinfo->client_data));
		if (self)
		{
			vtkUnsignedCharArray *uc = self->GetResult();
			vtkIdType oldSize = uc->GetSize();
			uc->Resize(static_cast<vtkIdType>(oldSize + oldSize / 2));
			vtkIdType newSize = uc->GetSize();
			cinfo->dest->next_output_byte = uc->GetPointer(oldSize);
			cinfo->dest->free_in_buffer = static_cast<size_t>(newSize - oldSize);
		}
		return TRUE;
	}
}

extern "C"
{
	static void vtkJPEGWriteToMemoryTerm(j_compress_ptr cinfo)
	{
		JPGExport *self = JPGExport::SafeDownCast(
			static_cast<vtkObject *>(cinfo->client_data));
		if (self)
		{
			vtkUnsignedCharArray *uc = self->GetResult();
			vtkIdType realSize = uc->GetSize() - static_cast<vtkIdType>(cinfo->dest->free_in_buffer);
			uc->SetNumberOfTuples(realSize);
		}
	}
}

#if defined ( _MSC_VER )
#if defined ( _WIN64 )
#pragma warning ( disable : 4324 ) 
#endif
#endif

struct VTK_JPEG_ERROR_MANAGER
{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
};

typedef struct VTK_JPEG_ERROR_MANAGER* VTK_JPEG_ERROR_PTR;

extern "C"
{
	void
		VTK_JPEG_ERROR_EXIT(j_common_ptr cinfo)
	{
		VTK_JPEG_ERROR_PTR jpegErr = reinterpret_cast<VTK_JPEG_ERROR_PTR>(cinfo->err);
		longjmp(jpegErr->setjmp_buffer, 1);
	}
}


#if defined(_MSC_VER) && !defined(VTK_DISPLAY_WIN32_WARNINGS)
#pragma warning ( disable : 4611 )
#endif
void JPGExport::WriteSlice(vtkImageData *data, int* uExtent)
{
	unsigned int ui;

	if (data->GetScalarType() != VTK_UNSIGNED_CHAR)
	{
		vtkWarningMacro("JPEGWriter only supports unsigned char input");
		return;
	}

	if (data->GetNumberOfScalarComponents() > MAX_COMPONENTS)
	{
		vtkErrorMacro("Exceed JPEG limits for number of components (" << data->GetNumberOfScalarComponents() << " > " << MAX_COMPONENTS << ")");
		return;
	}

	struct jpeg_compress_struct cinfo;
	struct VTK_JPEG_ERROR_MANAGER jerr;
	this->TempFP = 0;
	if (!this->WriteToMemory)
	{
		this->TempFP = fopen(this->InternalFileName, "wb");
		if (!this->TempFP)
		{
			vtkErrorMacro("Unable to open file " << this->InternalFileName);
			this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
			return;
		}
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = VTK_JPEG_ERROR_EXIT;
	if (setjmp(jerr.setjmp_buffer))
	{
		jpeg_destroy_compress(&cinfo);
		if (!this->WriteToMemory)
		{
			fclose(this->TempFP);
		}
		this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
		return;
	}

	jpeg_create_compress(&cinfo);

	struct jpeg_destination_mgr compressionDestination;
	if (this->WriteToMemory)
	{
		compressionDestination.init_destination = vtkJPEGWriteToMemoryInit;
		compressionDestination.empty_output_buffer = vtkJPEGWriteToMemoryEmpty;
		compressionDestination.term_destination = vtkJPEGWriteToMemoryTerm;
		cinfo.dest = &compressionDestination;
		cinfo.client_data = static_cast<void *>(this);
	}
	else
	{
		jpeg_stdio_dest(&cinfo, this->TempFP);
	}

	unsigned int width, height;
	width = uExtent[1] - uExtent[0] + 1;
	height = uExtent[3] - uExtent[2] + 1;

	cinfo.image_width = width;
	cinfo.image_height = height;

	cinfo.input_components = data->GetNumberOfScalarComponents();
	switch (cinfo.input_components)
	{
	case 1: cinfo.in_color_space = JCS_GRAYSCALE;
		break;
	case 3: cinfo.in_color_space = JCS_RGB;
		break;
	default: cinfo.in_color_space = JCS_UNKNOWN;
		break;
	}

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, this->Quality, TRUE);
	if (this->Progressive)
	{
		jpeg_simple_progression(&cinfo);
	}

	jpeg_start_compress(&cinfo, TRUE);

	void *outPtr;
	outPtr = data->GetScalarPointer(uExtent[0], uExtent[2], uExtent[4]);
	JSAMPROW *row_pointers = new JSAMPROW[height];
	vtkIdType *outInc = data->GetIncrements();
	vtkIdType rowInc = outInc[1];
	for (ui = 0; ui < height; ui++)
	{
		row_pointers[height - ui - 1] = (JSAMPROW)outPtr;
		outPtr = (unsigned char *)outPtr + rowInc;
	}
	jpeg_write_scanlines(&cinfo, row_pointers, height);

	if (!this->WriteToMemory)
	{
		if (fflush(this->TempFP) == EOF)
		{
			this->ErrorCode = vtkErrorCode::OutOfDiskSpaceError;
			fclose(this->TempFP);
			return;
		}
	}

	jpeg_finish_compress(&cinfo);

	delete[] row_pointers;
	jpeg_destroy_compress(&cinfo);

	if (!this->WriteToMemory)
	{
		fclose(this->TempFP);
	}
}
