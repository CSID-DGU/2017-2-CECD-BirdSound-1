#ifndef STLImport_h
#define STLImport_h

#include "vtkIOGeometryModule.h"
#include "vtkAbstractPolyDataReader.h"

class vtkCellArray;
class vtkFloatArray;
class vtkIncrementalPointLocator;
class vtkPoints;

class STLImport : public vtkAbstractPolyDataReader
{
public:
	vtkTypeMacro(STLImport, vtkAbstractPolyDataReader);

	static STLImport *New();

	vtkMTimeType GetMTime() VTK_OVERRIDE;

	vtkSetMacro(Merging, int);
	vtkGetMacro(Merging, int);
	vtkBooleanMacro(Merging, int);

	vtkSetMacro(ScalarTags, int);
	vtkGetMacro(ScalarTags, int);
	vtkBooleanMacro(ScalarTags, int);

	void SetLocator(vtkIncrementalPointLocator *locator);
	vtkGetObjectMacro(Locator, vtkIncrementalPointLocator);

protected:
	STLImport();
	~STLImport() VTK_OVERRIDE;

	vtkIncrementalPointLocator* NewDefaultLocator();

	int Merging;
	int ScalarTags;
	vtkIncrementalPointLocator *Locator;

	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE;
	bool ReadBinarySTL(FILE *fp, vtkPoints*, vtkCellArray*);
	bool ReadASCIISTL(FILE *fp, vtkPoints*, vtkCellArray*,
		vtkFloatArray* scalars = 0);
	int GetSTLFileType(const char *filename);
private:
	STLImport(const STLImport&) VTK_DELETE_FUNCTION;
	void operator=(const STLImport&) VTK_DELETE_FUNCTION;
};

#endif
