#ifndef OBJExport_h
#define OBJExport_h

#include "vtkIOExportModule.h"
#include "vtkExporter.h"

class vtkActor;

class OBJExport : public vtkExporter
{
public:
	static OBJExport *New();
	vtkTypeMacro(OBJExport, vtkExporter);

	vtkSetStringMacro(FilePrefix);
	vtkGetStringMacro(FilePrefix);

protected:
	OBJExport();
	~OBJExport() VTK_OVERRIDE;

	void WriteData() VTK_OVERRIDE;
	void WriteAnActor(vtkActor *anActor, FILE *fpObj, FILE *fpMat, int &id);
	char *FilePrefix;
private:
	OBJExport(const OBJExport&) VTK_DELETE_FUNCTION;
	void operator=(const OBJExport&) VTK_DELETE_FUNCTION;
};

#endif

