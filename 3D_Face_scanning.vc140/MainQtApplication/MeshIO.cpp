#include "MeshIO.h"

MeshIO::MeshIO()
{
}

MeshIO::~MeshIO()
{
}


int MeshIO::ImportSTLFile(std::string meshPath, vtkPolyData* data)
{
	vtkSmartPointer<STLImport> reader = vtkSmartPointer<STLImport>::New();
	reader->SetFileName(meshPath.c_str());
	reader->Update();

	if (data->GetNumberOfPoints())
		data->ReleaseData();

	data->DeepCopy(reader->GetOutput());
	data->Modified();

	int n = data->GetNumberOfPoints();

	return 1;
}

int MeshIO::ImportPLYFile(std::string meshPath, vtkPolyData* data)
{
	vtkSmartPointer<PLYImport> reader = vtkSmartPointer<PLYImport>::New();
	reader->SetFileName(meshPath.c_str());
	reader->Update();

	if (data->GetNumberOfPoints())
		data->ReleaseData();

	data->DeepCopy(reader->GetOutput());
	data->Modified();

	return 1;
}

int MeshIO::ImportOBJFile(std::string meshPath, vtkPolyData* data)
{
	vtkSmartPointer<OBJImport> reader = vtkSmartPointer<OBJImport>::New();
	reader->SetFileName(meshPath.c_str());
	reader->Update();

	if (data->GetNumberOfPoints())
		data->ReleaseData();

	data->DeepCopy(reader->GetOutput());
	data->Modified();

	return 1;
}

int MeshIO::ImportMesh(int extType, std::string meshPath, vtkPolyData* data)
{
	if (!data)
		return 0;

	if (extType == 0)
		ImportSTLFile(meshPath, data);
	else if (extType == 1)
		ImportPLYFile(meshPath, data);
	else if (extType == 2)
		ImportOBJFile(meshPath, data);
	else
		return 0;

	return 1;
}



int MeshIO::ExportSTLFile(vtkPolyData* data, std::string meshPath, int bAscii)
{
	vtkSmartPointer<STLExport> writer = vtkSmartPointer<STLExport>::New();
	writer->SetInputData(data);
	writer->SetFileName(meshPath.c_str());

	if (bAscii)
		writer->SetFileTypeToASCII();
	else
		writer->SetFileTypeToBinary();

	writer->Write();

	return 1;
}

int MeshIO::ExportPLYFile(vtkPolyData* data, std::string meshPath, int bAscii)
{
	vtkSmartPointer<PLYExport> writer = vtkSmartPointer<PLYExport>::New();
	writer->SetInputData(data);
	writer->SetFileName(meshPath.c_str());

	if (bAscii)
		writer->SetFileTypeToASCII();
	else
		writer->SetFileTypeToBinary();

	writer->Write();

	return 1;
}

int MeshIO::ExportOBJFile(vtkRenderWindow* renWin, std::string meshPath)
{
	vtkSmartPointer<OBJExport> writer = vtkSmartPointer<OBJExport>::New();
	writer->SetInput(renWin);
	writer->SetFilePrefix(meshPath.c_str());
	writer->Write();

	return 1;
}

int MeshIO::ExportMesh(int extType, std::string meshPath, vtkPolyData* data)
{
	if (!data)
		return 0;

	if (extType == 0)
		ExportSTLFile(data, meshPath);
	else if (extType == 1)
		ExportPLYFile(data, meshPath);
	else
		return 0;

	return 1;
}