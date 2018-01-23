#ifndef STLExport_h
#define STLExport_h

#include "vtk-8.1\vtkIOGeometryModule.h"
#include "vtk-8.1\vtkWriter.h"

class vtkCellArray;
class vtkPoints;
class vtkPolyData;

class STLExport : public vtkWriter
{
public:
	static STLExport *New();
	vtkTypeMacro(STLExport, vtkWriter);

	vtkPolyData* GetInput();
	vtkPolyData* GetInput(int port);

	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);

	vtkSetStringMacro(Header);
	vtkGetStringMacro(Header);

	vtkSetClampMacro(FileType, int, VTK_ASCII, VTK_BINARY);
	vtkGetMacro(FileType, int);
	void SetFileTypeToASCII() { this->SetFileType(VTK_ASCII); };
	void SetFileTypeToBinary() { this->SetFileType(VTK_BINARY); };

protected:
	STLExport();
	~STLExport() VTK_OVERRIDE
	{
		delete[] this->FileName;
		delete[] this->Header;
	}

	void WriteData() VTK_OVERRIDE;

	void WriteBinarySTL(vtkPoints *pts, vtkCellArray *polys, vtkCellArray *strips);
	void WriteAsciiSTL(vtkPoints *pts, vtkCellArray *polys, vtkCellArray *strips);

	char* FileName;
	char *Header;
	int   FileType;

	int FillInputPortInformation(int port, vtkInformation *info) VTK_OVERRIDE;

private:
	STLExport(const STLExport&) VTK_DELETE_FUNCTION;
	void operator=(const STLExport&) VTK_DELETE_FUNCTION;
};

#endif

