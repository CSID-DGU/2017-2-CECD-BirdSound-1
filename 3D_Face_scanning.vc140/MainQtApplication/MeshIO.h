#pragma once

#include "OBJExport.h"
#include "OBJImport.h"
#include "PLYExport.h"
#include "PLYImport.h"
#include "STLExport.h"
#include "STLImport.h"

#include <vtk-8.1\vtkSmartPointer.h>
#include <vtk-8.1\vtkPolyData.h>
#include <vtk-8.1\vtkRenderWindow.h>
#include <vtk-8.1\vtkMatrix4x4.h>


class MeshIO
{
public:
	MeshIO();
	~MeshIO();

	int ImportSTLFile(std::string meshPath, vtkPolyData* data);
	int ImportPLYFile(std::string meshPath, vtkPolyData* data);
	int ImportOBJFile(std::string meshPath, vtkPolyData* data);
	int ImportMesh(int extType, std::string meshPath, vtkPolyData* data);//0 stl, 1 ply, 2 obj

	int ExportSTLFile(vtkPolyData* data, std::string meshPath, int bAscii = 0);
	int ExportPLYFile(vtkPolyData* data, std::string meshPath, int bAscii = 0);
	int ExportOBJFile(vtkRenderWindow* renWin, std::string meshPath);
	int ExportMesh(int extType, std::string meshPath, vtkPolyData* data);//0 stl, 1 ply, 2 obj
};
