#include "JPGImport.h"

#include "vtk-8.1\vtkDataArray.h"
#include "vtk-8.1\vtkImageData.h"
#include "vtk-8.1\vtkObjectFactory.h"
#include "vtk-8.1\vtkPointData.h"
#include "vtk-8.1\vtkToolkits.h"

extern "C" {
#include "vtk-8.1\vtk_jpeg.h"
#include <setjmp.h>
}


vtkStandardNewMacro(JPGImport);


#if defined ( _MSC_VER )
#if defined ( _WIN64 )
#pragma warning ( disable : 4324 )
#endif
#endif

struct vtk_jpeg_error_mgr
{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
	JPGImport* JPEGReader;
	FILE *fp;
};

extern "C" void vtk_jpeg_error_exit(j_common_ptr cinfo)
{
	vtk_jpeg_error_mgr * err = reinterpret_cast<vtk_jpeg_error_mgr*>(cinfo->err);

	longjmp(err->setjmp_buffer, 1);
}

extern "C" void vtk_jpeg_output_message(j_common_ptr cinfo)
{
	char buffer[JMSG_LENGTH_MAX];

	(*cinfo->err->format_message) (cinfo, buffer);
	vtk_jpeg_error_mgr * err = reinterpret_cast<vtk_jpeg_error_mgr*>(cinfo->err);
	vtkWarningWithObjectMacro(err->JPEGReader,
		"libjpeg error: " << buffer);
}

extern "C" void jpg_null(j_decompress_ptr vtkNotUsed(cinfo))
{
}

extern "C" boolean fill_input_buffer(j_decompress_ptr vtkNotUsed(cinfo))
{
	vtkGenericWarningMacro(<< "libjpeg error: unexpected end of JPEG data!");
	return TRUE;
}

extern "C" void skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
	struct jpeg_source_mgr* src = (struct jpeg_source_mgr*) cinfo->src;

	if (num_bytes > 0)
	{
		src->next_input_byte += (size_t)num_bytes;
		src->bytes_in_buffer -= (size_t)num_bytes;
	}
}

#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
extern "C" void jMemSrc(j_decompress_ptr cinfo, void* buffer, long nbytes)
#else
extern "C" void jpeg_mem_src(j_decompress_ptr cinfo, void* buffer, long nbytes)
#endif
{
	cinfo->src = (struct jpeg_source_mgr *)
		(*cinfo->mem->alloc_small) ((j_common_ptr)cinfo, JPOOL_PERMANENT,
			sizeof(struct jpeg_source_mgr));
	cinfo->src = (struct jpeg_source_mgr*) cinfo->src;
	cinfo->src->init_source = jpg_null;
	cinfo->src->fill_input_buffer = fill_input_buffer;
	cinfo->src->skip_input_data = skip_input_data;
	cinfo->src->resync_to_restart = jpeg_resync_to_restart;
	cinfo->src->term_source = jpg_null;
	cinfo->src->bytes_in_buffer = nbytes;
	cinfo->src->next_input_byte = (const JOCTET*)buffer;
}

#ifdef _MSC_VER
#pragma warning( disable : 4611 )
#endif

void JPGImport::ExecuteInformation()
{
	struct vtk_jpeg_error_mgr jerr;
	jerr.JPEGReader = this;
	jerr.fp = NULL;

	this->ComputeInternalFileName(this->DataExtent[4]);
	if (this->InternalFileName == NULL && this->MemoryBuffer == NULL)
	{
		return;
	}

	if (!this->MemoryBuffer)
	{
		jerr.fp = fopen(this->InternalFileName, "rb");
		if (!jerr.fp)
		{
			vtkErrorWithObjectMacro(this,
				"Unable to open file "
				<< this->InternalFileName);
			return;
		}
	}
	else
	{
		if (this->MemoryBufferLength == 0)
		{
			vtkErrorWithObjectMacro(this,
				"Trying to read a JPEG image from "
				"a zero-length memory buffer!");
			return;
		}
	}

	struct jpeg_decompress_struct cinfo;
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = vtk_jpeg_error_exit;
	jerr.pub.output_message = vtk_jpeg_output_message;
	if (setjmp(jerr.setjmp_buffer))
	{
		jpeg_destroy_decompress(&cinfo);
		if (jerr.fp)
		{
			fclose(jerr.fp);
			vtkErrorWithObjectMacro(this, "libjpeg could not read file: "
				<< this->InternalFileName);
		}
		else
		{
			vtkErrorWithObjectMacro(this, "libjpeg could not read file from memory buffer: "
				<< static_cast<void*>(this->MemoryBuffer));
		}
		return;
	}
	jpeg_create_decompress(&cinfo);

	if (jerr.fp)
	{
		jpeg_stdio_src(&cinfo, jerr.fp);
	}
	else
	{
#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
		jMemSrc(&cinfo, this->MemoryBuffer, this->MemoryBufferLength);
#else
		jpeg_mem_src(&cinfo, this->MemoryBuffer, this->MemoryBufferLength);
#endif
	}

	jpeg_read_header(&cinfo, TRUE);

	jpeg_calc_output_dimensions(&cinfo);

	this->DataExtent[0] = 0;
	this->DataExtent[1] = cinfo.output_width - 1;
	this->DataExtent[2] = 0;
	this->DataExtent[3] = cinfo.output_height - 1;

	this->SetDataScalarTypeToUnsignedChar();
	this->SetNumberOfScalarComponents(cinfo.output_components);

	this->vtkImageReader2::ExecuteInformation();

	jpeg_destroy_decompress(&cinfo);

	if (jerr.fp)
	{
		fclose(jerr.fp);
	}
}

template <class OT>
int JPGImportUpdate2(JPGImport *self, OT *outPtr,
	int *outExt, vtkIdType *outInc, long)
{
	struct vtk_jpeg_error_mgr jerr;
	jerr.JPEGReader = self;
	jerr.fp = NULL;

	if (!self->GetMemoryBuffer())
	{
		jerr.fp = fopen(self->GetInternalFileName(), "rb");
		if (!jerr.fp)
		{
			return 1;
		}
	}

	struct jpeg_decompress_struct cinfo;
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = vtk_jpeg_error_exit;
	jerr.pub.output_message = vtk_jpeg_output_message;
	if (setjmp(jerr.setjmp_buffer))
	{
		jpeg_destroy_decompress(&cinfo);
		if (jerr.fp)
		{
			fclose(jerr.fp);
		}

		return 2;
	}
	jpeg_create_decompress(&cinfo);

	if (jerr.fp)
	{
		jpeg_stdio_src(&cinfo, jerr.fp);
	}
	else
	{
#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
		jMemSrc(&cinfo, self->GetMemoryBuffer(), self->GetMemoryBufferLength());
#else
		jpeg_mem_src(&cinfo, self->GetMemoryBuffer(), self->GetMemoryBufferLength());
#endif
	}

	jpeg_read_header(&cinfo, TRUE);

	jpeg_start_decompress(&cinfo);


	int rowbytes = cinfo.output_components * cinfo.output_width;
	unsigned char *tempImage = new unsigned char[rowbytes*cinfo.output_height];
	JSAMPROW *row_pointers = new JSAMPROW[cinfo.output_height];
	for (unsigned int ui = 0; ui < cinfo.output_height; ++ui)
	{
		row_pointers[ui] = tempImage + rowbytes*ui;
	}

	unsigned int remainingRows;
	while (cinfo.output_scanline < cinfo.output_height)
	{
		remainingRows = cinfo.output_height - cinfo.output_scanline;
		jpeg_read_scanlines(&cinfo, &row_pointers[cinfo.output_scanline],
			remainingRows);
	}

	jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	OT *outPtr2 = outPtr;
	long outSize = cinfo.output_components*(outExt[1] - outExt[0] + 1);
	for (int i = outExt[2]; i <= outExt[3]; ++i)
	{
		memcpy(outPtr2,
			row_pointers[cinfo.output_height - i - 1]
			+ outExt[0] * cinfo.output_components,
			outSize);
		outPtr2 += outInc[1];
	}
	delete[] tempImage;
	delete[] row_pointers;

	if (jerr.fp)
	{
		fclose(jerr.fp);
	}
	return 0;
}

template <class OT>
void JPGImportUpdate(JPGImport *self, vtkImageData *data, OT *outPtr)
{
	vtkIdType outIncr[3];
	int outExtent[6];
	OT *outPtr2;

	data->GetExtent(outExtent);
	data->GetIncrements(outIncr);

	long pixSize = data->GetNumberOfScalarComponents() * sizeof(OT);

	outPtr2 = outPtr;
	int idx2;
	for (idx2 = outExtent[4]; idx2 <= outExtent[5]; ++idx2)
	{
		self->ComputeInternalFileName(idx2);
		if (JPGImportUpdate2(self, outPtr2, outExtent, outIncr, pixSize) == 2)
		{
			const char* fn = self->GetInternalFileName();
			vtkErrorWithObjectMacro(self, "libjpeg could not read file: " << fn);
		}

		self->UpdateProgress((idx2 - outExtent[4]) /
			(outExtent[5] - outExtent[4] + 1.0));
		outPtr2 += outIncr[2];
	}
}


void JPGImport::ExecuteDataWithInformation(vtkDataObject *output,
	vtkInformation *outInfo)
{
	vtkImageData *data = this->AllocateOutputData(output, outInfo);

	if (this->InternalFileName == NULL)
	{
		vtkErrorMacro(<< "Either a FileName or FilePrefix must be specified.");
		return;
	}

	this->ComputeDataIncrements();

	data->GetPointData()->GetScalars()->SetName("JPEGImage");

	void *outPtr;

	outPtr = data->GetScalarPointer();
	switch (data->GetScalarType())
	{
		vtkTemplateMacro(JPGImportUpdate(this, data, (VTK_TT *)(outPtr)));
	default:
		vtkErrorMacro(<< "UpdateFromFile: Unknown data type");
	}
}



int JPGImport::CanReadFile(const char* fname)
{
	struct vtk_jpeg_error_mgr jerr;
	jerr.JPEGReader = this;
	jerr.fp = NULL;

	jerr.fp = fopen(fname, "rb");
	if (!jerr.fp)
	{
		return 0;
	}
	char magic[2];
	int n = static_cast<int>(fread(magic, sizeof(magic), 1, jerr.fp));
	if (n != 1)
	{
		fclose(jerr.fp);
		return 0;
	}
	if (((static_cast<unsigned char>(magic[0]) != 0xFF) ||
		(static_cast<unsigned char>(magic[1]) != 0xD8)))
	{
		fclose(jerr.fp);
		return 0;
	}
	fseek(jerr.fp, 0, SEEK_SET);
	struct jpeg_decompress_struct cinfo;
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = vtk_jpeg_error_exit;
	jerr.pub.output_message = vtk_jpeg_error_exit;
	if (setjmp(jerr.setjmp_buffer))
	{
		jpeg_destroy_decompress(&cinfo);
		fclose(jerr.fp);
		return 0;
	}
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, jerr.fp);
	jpeg_read_header(&cinfo, TRUE);

	jpeg_destroy_decompress(&cinfo);
	fclose(jerr.fp);
	return 3;
}
#ifdef _MSC_VER
#pragma warning( default : 4611 )
#endif
