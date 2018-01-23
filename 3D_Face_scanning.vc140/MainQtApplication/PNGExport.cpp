#include "PNGExport.h"

#include "vtk-8.1\vtkAlgorithmOutput.h"
#include "vtk-8.1\vtkErrorCode.h"
#include "vtk-8.1\vtkImageData.h"
#include "vtk-8.1\vtkObjectFactory.h"
#include "vtk-8.1\vtkStreamingDemandDrivenPipeline.h"
#include "vtk-8.1\vtkUnsignedCharArray.h"
#include "vtk-8.1\vtk_png.h"

#include <vector>

class PNGExport::vtkInternals
{
public:
	std::vector<std::pair<std::string, std::string> > TextKeyValue;
};


vtkStandardNewMacro(PNGExport);

vtkCxxSetObjectMacro(PNGExport, Result, vtkUnsignedCharArray);

const char* PNGExport::TITLE = "Title";
const char* PNGExport::AUTHOR = "Author";
const char* PNGExport::DESCRIPTION = "Description";
const char* PNGExport::COPYRIGHT = "Copyright";
const char* PNGExport::CREATION_TIME = "Creation Time";
const char* PNGExport::SOFTWARE = "Software";
const char* PNGExport::DISCLAIMER = "Disclaimer";
const char* PNGExport::WARNING = "Warning";
const char* PNGExport::SOURCE = "Source";
const char* PNGExport::COMMENT = "Comment";


PNGExport::PNGExport()
{
	this->FileLowerLeft = 1;
	this->FileDimensionality = 2;
	this->CompressionLevel = 5;
	this->Result = 0;
	this->TempFP = 0;
	this->Internals = new vtkInternals();
}

PNGExport::~PNGExport()
{
	if (this->Result)
	{
		this->Result->Delete();
		this->Result = 0;
	}
	delete this->Internals;
}

void PNGExport::Write()
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

	size_t internalFileNameSize = (this->FileName ? strlen(this->FileName) : 1) +
		(this->FilePrefix ? strlen(this->FilePrefix) : 1) +
		(this->FilePattern ? strlen(this->FilePattern) : 1) + 256;
	this->InternalFileName = new char[internalFileNameSize];
	this->InternalFileName[0] = 0;

	this->GetInputExecutive(0, 0)->UpdateInformation();
	int *wExtent;
	wExtent = vtkStreamingDemandDrivenPipeline::GetWholeExtent(
		this->GetInputInformation(0, 0));
	this->FileNumber = wExtent[4];
	this->MinimumFileNumber = this->MaximumFileNumber = this->FileNumber;
	this->FilesDeleted = 0;
	this->UpdateProgress(0.0);
	for (this->FileNumber = wExtent[4]; this->FileNumber <= wExtent[5];
		++this->FileNumber)
	{
		this->MaximumFileNumber = this->FileNumber;
		int uExt[6];
		memcpy(uExt, wExtent, 4 * sizeof(int));
		uExt[4] = uExt[5] = this->FileNumber;
		if (!this->WriteToMemory)
		{
			int bytes_printed = 0;
			if (this->FileName)
			{
				bytes_printed = snprintf(this->InternalFileName, internalFileNameSize,
					"%s", this->FileName);
			}
			else
			{
				if (this->FilePrefix)
				{
					bytes_printed = snprintf(this->InternalFileName, internalFileNameSize,
						this->FilePattern, this->FilePrefix, this->FileNumber);
				}
				else
				{
					bytes_printed = snprintf(this->InternalFileName, internalFileNameSize,
						this->FilePattern, this->FileNumber);
				}
			}
			if (static_cast<size_t>(bytes_printed) >= internalFileNameSize)
			{
				this->InternalFileName[internalFileNameSize - 1] = 0;
				vtkWarningMacro("Filename has been truncated.");
			}
		}
		this->GetInputAlgorithm()->UpdateExtent(uExt);
		this->WriteSlice(this->GetInput(), uExt);
		if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
		{
			this->DeleteFiles();
			break;
		}
		this->UpdateProgress((this->FileNumber - wExtent[4]) /
			(wExtent[5] - wExtent[4] + 1.0));
	}
	delete[] this->InternalFileName;
	this->InternalFileName = NULL;
}

extern "C"
{
	static void vtkPNGWriteInit(png_structp png_ptr, png_bytep data,
		png_size_t sizeToWrite)
	{
		PNGExport *self =
			PNGExport::SafeDownCast(static_cast<vtkObject *>
			(png_get_io_ptr(png_ptr)));
		if (self)
		{
			vtkUnsignedCharArray *uc = self->GetResult();
			unsigned char *ptr = uc->WritePointer(uc->GetMaxId() + 1,
				static_cast<vtkIdType>(sizeToWrite));
			memcpy(ptr, data, sizeToWrite);
		}
	}
}

extern "C"
{
	static void vtkPNGWriteFlush(png_structp vtkNotUsed(png_ptr))
	{
	}
}

extern "C"
{
	static void vtkPNGWriteWarningFunction(png_structp png_ptr,
		png_const_charp warning_msg)
	{
		PNG_CONST char *name = "UNKNOWN (ERROR!)";
		char *test;
		test = static_cast<char *>(png_get_error_ptr(png_ptr));

		if (test == NULL)
			fprintf(stderr, "%s: libpng warning: %s\n", name, warning_msg);

		else
			fprintf(stderr, "%s: libpng warning: %s\n", test, warning_msg);
	}
}

extern "C"
{
	static void vtkPNGWriteErrorFunction(png_structp png_ptr,
		png_const_charp error_msg)
	{
#if PNG_LIBPNG_VER >= 10400
		vtkPNGWriteWarningFunction(png_ptr, error_msg);
#else
		(void)error_msg;
		longjmp(png_ptr->jmpbuf, 1);
#endif
	}
}

#if defined(_MSC_VER) && !defined(VTK_DISPLAY_WIN32_WARNINGS)
#pragma warning ( disable : 4611 )
#endif
void PNGExport::WriteSlice(vtkImageData *data, int* uExtent)
{
	vtkInternals* impl = this->Internals;
	unsigned int ui;

	if (data->GetScalarType() != VTK_UNSIGNED_SHORT &&
		data->GetScalarType() != VTK_UNSIGNED_CHAR)
	{
		vtkWarningMacro("PNGWriter only supports unsigned char and unsigned short inputs");
		return;
	}

	png_structp png_ptr = png_create_write_struct
	(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
	if (!png_ptr)
	{
		vtkErrorMacro(<< "Unable to write PNG file!");
		return;
	}

	png_set_compression_level(png_ptr, this->CompressionLevel);

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_write_struct(&png_ptr,
			(png_infopp)NULL);
		vtkErrorMacro(<< "Unable to write PNG file!");
		return;
	}


	this->TempFP = 0;
	png_byte **row_pointers = 0;
	if (this->WriteToMemory)
	{
		vtkUnsignedCharArray *uc = this->GetResult();
		if (!uc || uc->GetReferenceCount() > 1)
		{
			uc = vtkUnsignedCharArray::New();
			this->SetResult(uc);
			uc->Delete();
		}
		uc->Allocate(10000);
		png_set_write_fn(png_ptr, static_cast<png_voidp>(this),
			vtkPNGWriteInit, vtkPNGWriteFlush);
	}
	else
	{
		this->TempFP = fopen(this->InternalFileName, "wb");
		if (!this->TempFP)
		{
			vtkErrorMacro("Unable to open file " << this->InternalFileName);
			this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
			return;
		}
		png_init_io(png_ptr, this->TempFP);
		png_set_error_fn(png_ptr, png_ptr,
			vtkPNGWriteErrorFunction, vtkPNGWriteWarningFunction);
		if (setjmp(png_jmpbuf((png_ptr))))
		{
			fclose(this->TempFP);
			delete[] row_pointers;
			png_destroy_write_struct(&png_ptr, &info_ptr);
			this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
			return;
		}
	}


	void *outPtr;
	outPtr = data->GetScalarPointer(uExtent[0], uExtent[2], uExtent[4]);
	png_uint_32 width, height;
	width = uExtent[1] - uExtent[0] + 1;
	height = uExtent[3] - uExtent[2] + 1;
	int bit_depth = 8;
	if (data->GetScalarType() == VTK_UNSIGNED_SHORT)
	{
		bit_depth = 16;
	}
	int color_type;
	switch (data->GetNumberOfScalarComponents())
	{
	case 1: color_type = PNG_COLOR_TYPE_GRAY;
		break;
	case 2: color_type = PNG_COLOR_TYPE_GRAY_ALPHA;
		break;
	case 3: color_type = PNG_COLOR_TYPE_RGB;
		break;
	default: color_type = PNG_COLOR_TYPE_RGB_ALPHA;
		break;
	}

	png_set_IHDR(png_ptr, info_ptr, width, height,
		bit_depth, color_type, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);

	if (impl->TextKeyValue.size() > 0)
	{
		std::vector<png_text> pngText(impl->TextKeyValue.size());
		for (size_t i = 0; i < pngText.size(); ++i)
		{
			pngText[i].compression = PNG_TEXT_COMPRESSION_NONE;
			pngText[i].key = const_cast<char*>(impl->TextKeyValue[i].first.c_str());
			pngText[i].text = const_cast<char*>(impl->TextKeyValue[i].second.c_str());
			pngText[i].text_length = impl->TextKeyValue[i].second.length();
#ifdef PNG_iTXt_SUPPORTED
			pngText[i].itxt_length = 0;
			pngText[i].lang = NULL;
			pngText[i].lang_key = NULL;
#endif
		}
		png_set_text(png_ptr, info_ptr, &pngText[0], static_cast<int>(pngText.size()));
	}

	png_write_info(png_ptr, info_ptr);
	if (bit_depth > 8)
	{
#ifndef VTK_WORDS_BIGENDIAN
		png_set_swap(png_ptr);
#endif
	}
	row_pointers = new png_byte *[height];
	vtkIdType *outInc = data->GetIncrements();
	vtkIdType rowInc = outInc[1] * bit_depth / 8;
	for (ui = 0; ui < height; ui++)
	{
		unsigned int offset = height - ui - 1;
		row_pointers[offset] = (png_byte *)outPtr;
		outPtr = (unsigned char *)outPtr + rowInc;
	}
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	delete[] row_pointers;
	png_destroy_write_struct(&png_ptr, &info_ptr);

	if (this->TempFP)
	{
		fflush(this->TempFP);
		if (ferror(this->TempFP))
		{
			this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
		}
	}

	if (this->TempFP)
	{
		fclose(this->TempFP);
	}
}

void PNGExport::AddText(const char* key, const char* value)
{
	vtkInternals* impl = this->Internals;
	const size_t MAX_KEY_LENGTH = 79;
	if (!key || key[0] == '\0')
	{
		vtkWarningMacro("Trying to add PNG text chunk with a null or empty key");
		return;
	}
	size_t keyLength = strlen(key);
	if (keyLength > MAX_KEY_LENGTH)
	{
		vtkWarningMacro("Trying to add a PNG text chunk with a key longer than "
			<< MAX_KEY_LENGTH
			<< " characters: " << key << " Truncating ...");
		keyLength = MAX_KEY_LENGTH;
	}
	size_t index = impl->TextKeyValue.size();
	impl->TextKeyValue.resize(index + 1);
	impl->TextKeyValue[index].first.assign(key, keyLength);
	impl->TextKeyValue[index].second.assign(value);
	this->Modified();
}
