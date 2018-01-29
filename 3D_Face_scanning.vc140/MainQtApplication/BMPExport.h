#ifndef BMPExport_h
#define BMPExport_h


#include "vtkIOImageModule.h"
#include "vtkImageWriter.h"

class BMPExport : public vtkImageWriter
{
public:
	static BMPExport *New();
	vtkTypeMacro(BMPExport, vtkImageWriter);

protected:
	BMPExport();
	~BMPExport() VTK_OVERRIDE {}

	void WriteFile(ofstream *file, vtkImageData *data, int ext[6], int wExt[6]) ;
	void WriteFileHeader(ofstream *, vtkImageData *, int wExt[6]) ;
private:
	BMPExport(const BMPExport&) VTK_DELETE_FUNCTION;
	void operator=(const BMPExport&) VTK_DELETE_FUNCTION;
};

#endif


