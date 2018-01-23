#ifndef JPGImport_h
#define JPGImport_h

#include "vtk-8.1\vtkIOImageModule.h"
#include "vtk-8.1\vtkImageReader2.h"

class JPGImport : public vtkImageReader2
{
public:
	static JPGImport *New();
	vtkTypeMacro(JPGImport, vtkImageReader2);

	int CanReadFile(const char* fname) VTK_OVERRIDE;

	const char* GetFileExtensions() VTK_OVERRIDE
	{
		return ".jpeg .jpg";
	}

	const char* GetDescriptiveName() VTK_OVERRIDE
	{
		return "JPEG";
	}
protected:
	JPGImport() {}
	~JPGImport() VTK_OVERRIDE {}

	void ExecuteInformation() VTK_OVERRIDE;
	void ExecuteDataWithInformation(vtkDataObject *out, vtkInformation *outInfo) VTK_OVERRIDE;
private:
	JPGImport(const JPGImport&) VTK_DELETE_FUNCTION;
	void operator=(const JPGImport&) VTK_DELETE_FUNCTION;
};
#endif


