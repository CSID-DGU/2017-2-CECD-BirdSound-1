#ifndef OBJImport_h
#define OBJImport_h

#include "vtk-8.1\vtkIOGeometryModule.h"
#include "vtk-8.1\vtkAbstractPolyDataReader.h"


//v <x> <y> <z>
//vertex
//
//vn <x> <y> <z>
//vertex normal
//
//vt <x> <y>
//texture coordinate
//
//f <v_a> <v_b> <v_c>...
//face
//
//f <v_a>/<t_a> <v_b>/<t_b>...
//face/texture
//
//f <v_a>/<t_a>/<n_a> <v_b>/<t_b>/<n_b>...
//face/texture/normal
//
//f <v_a>//<n_a> <v_b>//<n_b> ...
//face/normal


class OBJImport : public vtkAbstractPolyDataReader
{
public:
	static OBJImport *New();
	vtkTypeMacro(OBJImport, vtkAbstractPolyDataReader);

protected:
	OBJImport();
	~OBJImport() VTK_OVERRIDE;

	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE;
private:
	OBJImport(const OBJImport&) VTK_DELETE_FUNCTION;
	void operator=(const OBJImport&) VTK_DELETE_FUNCTION;
};

#endif

