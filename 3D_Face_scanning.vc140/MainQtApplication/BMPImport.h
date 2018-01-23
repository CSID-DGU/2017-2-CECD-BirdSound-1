#ifndef BMPImport_h
#define BMPImport_h

#include "vtk-8.1\vtkIOImageModule.h"
#include "vtk-8.1\vtkImageReader.h"

class vtkLookupTable;

class BMPImport : public vtkImageReader
{
public:
	static BMPImport *New();
	vtkTypeMacro(BMPImport, vtkImageReader);

	vtkGetMacro(Depth, int);

	int CanReadFile(const char* fname) VTK_OVERRIDE;

	const char* GetFileExtensions() VTK_OVERRIDE
	{
		return ".bmp";
	}

	const char* GetDescriptiveName() VTK_OVERRIDE
	{
		return "Windows BMP";
	}

	vtkSetMacro(Allow8BitBMP, int);
	vtkGetMacro(Allow8BitBMP, int);
	vtkBooleanMacro(Allow8BitBMP, int);

	vtkGetObjectMacro(LookupTable, vtkLookupTable);

	vtkGetMacro(Colors, unsigned char *);

protected:
	BMPImport();
	~BMPImport() VTK_OVERRIDE;

	unsigned char *Colors;
	short Depth;
	int Allow8BitBMP;
	vtkLookupTable *LookupTable;

	void ComputeDataIncrements() VTK_OVERRIDE;
	void ExecuteInformation() VTK_OVERRIDE;
	void ExecuteDataWithInformation(vtkDataObject *out, vtkInformation* outInfo) VTK_OVERRIDE;
private:
	BMPImport(const BMPImport&) VTK_DELETE_FUNCTION;
	void operator=(const BMPImport&) VTK_DELETE_FUNCTION;
};
#endif


