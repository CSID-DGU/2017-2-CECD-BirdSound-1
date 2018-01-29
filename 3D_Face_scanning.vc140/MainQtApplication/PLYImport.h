#ifndef PLYImport_h
#define PLYImport_h

#include "vtkIOPLYModule.h"
#include "vtkAbstractPolyDataReader.h"

class PLYImport : public vtkAbstractPolyDataReader
{
public:
	vtkTypeMacro(PLYImport, vtkAbstractPolyDataReader);

	static PLYImport *New();

	static int CanReadFile(const char *filename);

protected:
	PLYImport();
	~PLYImport() VTK_OVERRIDE;

	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE;
private:
	PLYImport(const PLYImport&) VTK_DELETE_FUNCTION;
	void operator=(const PLYImport&) VTK_DELETE_FUNCTION;
};

#endif
