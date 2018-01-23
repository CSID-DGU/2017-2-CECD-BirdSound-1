#ifndef JPGExport_h
#define JPGExport_h

#include "vtk-8.1\vtkIOImageModule.h"
#include "vtk-8.1\vtkImageWriter.h"

class vtkUnsignedCharArray;
class vtkImageData;

class JPGExport : public vtkImageWriter
{
public:
	static JPGExport *New();
	vtkTypeMacro(JPGExport, vtkImageWriter);

	void Write() VTK_OVERRIDE;

	vtkSetClampMacro(Quality, int, 0, 100);
	vtkGetMacro(Quality, int);

	vtkSetMacro(Progressive, unsigned int);
	vtkGetMacro(Progressive, unsigned int);
	vtkBooleanMacro(Progressive, unsigned int);

	vtkSetMacro(WriteToMemory, unsigned int);
	vtkGetMacro(WriteToMemory, unsigned int);
	vtkBooleanMacro(WriteToMemory, unsigned int);

	virtual void SetResult(vtkUnsignedCharArray*);
	vtkGetObjectMacro(Result, vtkUnsignedCharArray);

protected:
	JPGExport();
	~JPGExport() VTK_OVERRIDE;

	void WriteSlice(vtkImageData *data, int* uExtent);

private:
	int Quality;
	unsigned int Progressive;
	vtkUnsignedCharArray *Result;
	FILE *TempFP;

private:
	JPGExport(const JPGExport&) VTK_DELETE_FUNCTION;
	void operator=(const JPGExport&) VTK_DELETE_FUNCTION;
};

#endif


