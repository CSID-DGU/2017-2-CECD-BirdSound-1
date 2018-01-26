#ifndef PNGExport_h
#define PNGExport_h

#include "vtkIOImageModule.h"
#include "vtkImageWriter.h"

class vtkImageData;
class vtkUnsignedCharArray;

class PNGExport : public vtkImageWriter
{
public:
	static PNGExport *New();
	vtkTypeMacro(PNGExport, vtkImageWriter);

	void Write() VTK_OVERRIDE;

	vtkSetClampMacro(CompressionLevel, int, 0, 9);
	vtkGetMacro(CompressionLevel, int);

	vtkSetMacro(WriteToMemory, unsigned int);
	vtkGetMacro(WriteToMemory, unsigned int);
	vtkBooleanMacro(WriteToMemory, unsigned int);

	virtual void SetResult(vtkUnsignedCharArray*);
	vtkGetObjectMacro(Result, vtkUnsignedCharArray);

	void AddText(const char* key, const char* value);

	static const char* TITLE;
	static const char* AUTHOR;
	static const char* DESCRIPTION;
	static const char* COPYRIGHT;
	static const char* CREATION_TIME;
	static const char* SOFTWARE;
	static const char* DISCLAIMER;
	static const char* WARNING;
	static const char* SOURCE;
	static const char* COMMENT;

protected:
	PNGExport();
	~PNGExport() VTK_OVERRIDE;

	void WriteSlice(vtkImageData *data, int* uExtent);
	int CompressionLevel;
	vtkUnsignedCharArray *Result;
	FILE *TempFP;
	class vtkInternals;
	vtkInternals* Internals;


private:
	PNGExport(const PNGExport&) VTK_DELETE_FUNCTION;
	void operator=(const PNGExport&) VTK_DELETE_FUNCTION;
};

#endif
