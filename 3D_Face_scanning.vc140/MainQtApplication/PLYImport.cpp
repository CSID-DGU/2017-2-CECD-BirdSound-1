#include "PLYImport.h"

#include "vtk-8.1\vtkCellArray.h"
#include "vtk-8.1\vtkCellData.h"
#include "vtk-8.1\vtkPointData.h"
#include "vtk-8.1\vtkFloatArray.h"
#include "vtk-8.1\vtkInformation.h"
#include "vtk-8.1\vtkInformationVector.h"
#include "vtk-8.1\vtkObjectFactory.h"
#include "vtk-8.1\vtkPLY.h"
#include "vtk-8.1\vtkPolyData.h"
#include "vtk-8.1\vtkSmartPointer.h"

#include <cctype>
#include <cstddef>

vtkStandardNewMacro(PLYImport);


PLYImport::PLYImport()
{
	this->FileName = NULL;

	this->SetNumberOfInputPorts(0);
}

PLYImport::~PLYImport()
{
	delete[] this->FileName;
}

namespace
{
	typedef struct _plyVertex
	{
		float x[3];
		float tex[2];
		float normal[3];
		unsigned char red;
		unsigned char green;
		unsigned char blue;
	} plyVertex;

	typedef struct _plyFace
	{
		unsigned char intensity;
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char nverts;
		int *verts;
	} plyFace;
}

int PLYImport::RequestData(vtkInformation *vtkNotUsed(request), vtkInformationVector **vtkNotUsed(inputVector), vtkInformationVector *outputVector)
{
	vtkInformation *outInfo = outputVector->GetInformationObject(0);

	vtkPolyData *output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

	PlyProperty vertProps[] =
	{
		{ "x", PLY_FLOAT, PLY_FLOAT, static_cast<int>(offsetof(plyVertex,x)), 0, 0, 0, 0 },
		{ "y", PLY_FLOAT, PLY_FLOAT, static_cast<int>(offsetof(plyVertex,x) + sizeof(float)), 0, 0, 0, 0 },
		{ "z", PLY_FLOAT, PLY_FLOAT, static_cast<int>(offsetof(plyVertex,x) + sizeof(float) + sizeof(float)), 0, 0, 0, 0 },
		{ "u", PLY_FLOAT, PLY_FLOAT, static_cast<int>(offsetof(plyVertex,tex)), 0, 0, 0, 0 },
		{ "v", PLY_FLOAT, PLY_FLOAT, static_cast<int>(offsetof(plyVertex,tex) + sizeof(float)), 0, 0, 0, 0 },
		{ "nx", PLY_FLOAT, PLY_FLOAT, static_cast<int>(offsetof(plyVertex,normal)), 0, 0, 0, 0 },
		{ "ny", PLY_FLOAT, PLY_FLOAT, static_cast<int>(offsetof(plyVertex,normal) + sizeof(float)), 0, 0, 0, 0 },
		{ "nz", PLY_FLOAT, PLY_FLOAT, static_cast<int>(offsetof(plyVertex,normal) + 2 * sizeof(float)), 0, 0, 0, 0 },
		{ "red", PLY_UCHAR, PLY_UCHAR, static_cast<int>(offsetof(plyVertex,red)), 0, 0, 0, 0 },
		{ "green", PLY_UCHAR, PLY_UCHAR, static_cast<int>(offsetof(plyVertex,green)), 0, 0, 0, 0 },
		{ "blue", PLY_UCHAR, PLY_UCHAR, static_cast<int>(offsetof(plyVertex,blue)), 0, 0, 0, 0 },
	};
	PlyProperty faceProps[] =
	{
		{ "vertex_indices", PLY_INT, PLY_INT, static_cast<int>(offsetof(plyFace,verts)),
		1, PLY_UCHAR, PLY_UCHAR, static_cast<int>(offsetof(plyFace,nverts)) },
		{ "intensity", PLY_UCHAR, PLY_UCHAR, static_cast<int>(offsetof(plyFace,intensity)), 0, 0, 0, 0 },
		{ "red", PLY_UCHAR, PLY_UCHAR, static_cast<int>(offsetof(plyFace,red)), 0, 0, 0, 0 },
		{ "green", PLY_UCHAR, PLY_UCHAR, static_cast<int>(offsetof(plyFace,green)), 0, 0, 0, 0 },
		{ "blue", PLY_UCHAR, PLY_UCHAR, static_cast<int>(offsetof(plyFace,blue)), 0, 0, 0, 0 },
	};

	if (!this->FileName)
	{
		vtkErrorMacro(<< "A File Name must be specified.");
		return 0;
	}

	PlyFile *ply;
	int nelems, fileType, numElems, nprops;
	char **elist, *elemName;
	float version;

	if (!(ply = vtkPLY::ply_open_for_reading(this->FileName, &nelems, &elist, &fileType, &version)))
	{
		vtkWarningMacro(<< "Could not open PLY file");
		return 0;
	}

	PlyElement *elem;
	int index;
	if ((elem = vtkPLY::find_element(ply, "vertex")) == NULL ||
				vtkPLY::find_property(elem, "x", &index) == NULL ||
				vtkPLY::find_property(elem, "y", &index) == NULL ||
				vtkPLY::find_property(elem, "z", &index) == NULL)
	{
		vtkErrorMacro(<< "Cannot read geometry");
		vtkPLY::ply_close(ply);
	}

	bool intensityAvailable = false;
	vtkSmartPointer<vtkUnsignedCharArray> intensity = NULL;
	if ((elem = vtkPLY::find_element(ply, "face")) != NULL && vtkPLY::find_property(elem, "intensity", &index) != NULL)
	{
		intensity = vtkSmartPointer<vtkUnsignedCharArray>::New();
		intensity->SetName("intensity");
		intensityAvailable = true;
		output->GetCellData()->AddArray(intensity);
		output->GetCellData()->SetActiveScalars("intensity");
	}

	bool RGBCellsAvailable = false;
	vtkSmartPointer<vtkUnsignedCharArray> RGBCells = NULL;
	if ((elem = vtkPLY::find_element(ply, "face")) != NULL &&
				vtkPLY::find_property(elem, "red", &index) != NULL &&
				vtkPLY::find_property(elem, "green", &index) != NULL &&
				vtkPLY::find_property(elem, "blue", &index) != NULL)
	{
		RGBCells = vtkSmartPointer<vtkUnsignedCharArray>::New();
		RGBCells->SetName("RGB");
		RGBCellsAvailable = true;
		output->GetCellData()->AddArray(RGBCells);
		output->GetCellData()->SetActiveScalars("RGB");
	}

	bool RGBPointsAvailable = false;
	vtkSmartPointer<vtkUnsignedCharArray> RGBPoints = NULL;
	if ((elem = vtkPLY::find_element(ply, "vertex")) != NULL &&
				vtkPLY::find_property(elem, "red", &index) != NULL &&
				vtkPLY::find_property(elem, "green", &index) != NULL &&
				vtkPLY::find_property(elem, "blue", &index) != NULL)
	{
		RGBPoints = vtkSmartPointer<vtkUnsignedCharArray>::New();
		RGBPointsAvailable = true;
		RGBPoints->SetName("RGB");
		RGBPoints->SetNumberOfComponents(3);
		output->GetPointData()->SetScalars(RGBPoints);
	}

	bool NormalPointsAvailable = false;
	vtkSmartPointer<vtkFloatArray> Normals = NULL;
	if ((elem = vtkPLY::find_element(ply, "vertex")) != NULL &&
				vtkPLY::find_property(elem, "nx", &index) != NULL &&
				vtkPLY::find_property(elem, "ny", &index) != NULL &&
				vtkPLY::find_property(elem, "nz", &index) != NULL)
	{
		Normals = vtkSmartPointer<vtkFloatArray>::New();
		NormalPointsAvailable = true;
		Normals->SetName("Normals");
		Normals->SetNumberOfComponents(3);
		output->GetPointData()->SetNormals(Normals);
	}

	bool TexCoordsPointsAvailable = false;
	vtkSmartPointer<vtkFloatArray> TexCoordsPoints = NULL;
	if ((elem = vtkPLY::find_element(ply, "vertex")) != NULL)
	{
		if (vtkPLY::find_property(elem, "u", &index) != NULL && vtkPLY::find_property(elem, "v", &index) != NULL)
		{
			TexCoordsPointsAvailable = true;
		}
		else if (vtkPLY::find_property(elem, "texture_u", &index) != NULL && vtkPLY::find_property(elem, "texture_v", &index) != NULL)
		{
			TexCoordsPointsAvailable = true;
			vertProps[3].name = "texture_u";
			vertProps[4].name = "texture_v";
		}

		if (TexCoordsPointsAvailable)
		{
			TexCoordsPoints = vtkSmartPointer<vtkFloatArray>::New();
			TexCoordsPoints->SetName("TCoords");
			TexCoordsPoints->SetNumberOfComponents(2);
			output->GetPointData()->SetTCoords(TexCoordsPoints);
		}
	}

	int numPts = 0, numPolys = 0;
	for (int i = 0; i < nelems; i++)
	{
		elemName = elist[i];
		vtkPLY::ply_get_element_description(ply, elemName, &numElems, &nprops);

		if (elemName && !strcmp("vertex", elemName))
		{
			numPts = numElems;
			vtkPoints *pts = vtkPoints::New();
			pts->SetDataTypeToFloat();
			pts->SetNumberOfPoints(numPts);

			vtkPLY::ply_get_property(ply, elemName, &vertProps[0]);
			vtkPLY::ply_get_property(ply, elemName, &vertProps[1]);
			vtkPLY::ply_get_property(ply, elemName, &vertProps[2]);

			if (TexCoordsPointsAvailable)
			{
				vtkPLY::ply_get_property(ply, elemName, &vertProps[3]);
				vtkPLY::ply_get_property(ply, elemName, &vertProps[4]);
				TexCoordsPoints->SetNumberOfTuples(numPts);
			}

			if (NormalPointsAvailable)
			{
				vtkPLY::ply_get_property(ply, elemName, &vertProps[5]);
				vtkPLY::ply_get_property(ply, elemName, &vertProps[6]);
				vtkPLY::ply_get_property(ply, elemName, &vertProps[7]);
				Normals->SetNumberOfTuples(numPts);
			}

			if (RGBPointsAvailable)
			{
				vtkPLY::ply_get_property(ply, elemName, &vertProps[8]);
				vtkPLY::ply_get_property(ply, elemName, &vertProps[9]);
				vtkPLY::ply_get_property(ply, elemName, &vertProps[10]);
				RGBPoints->SetNumberOfTuples(numPts);
			}

			plyVertex vertex;
			for (int j = 0; j < numPts; j++)
			{
				vtkPLY::ply_get_element(ply, (void *)&vertex);
				pts->SetPoint(j, vertex.x);
				if (TexCoordsPointsAvailable)
				{
					TexCoordsPoints->SetTuple2(j, vertex.tex[0], vertex.tex[1]);
				}
				if (NormalPointsAvailable)
				{
					Normals->SetTuple3(j, vertex.normal[0], vertex.normal[1], vertex.normal[2]);
				}
				if (RGBPointsAvailable)
				{
					RGBPoints->SetTuple3(j, vertex.red, vertex.green, vertex.blue);
				}
			}
			output->SetPoints(pts);
			pts->Delete();
		}

		else if (elemName && !strcmp("face", elemName))
		{
			numPolys = numElems;
			vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
			polys->Allocate(polys->EstimateSize(numPolys, 3), numPolys / 2);
			plyFace face;
			vtkIdType vtkVerts[256];

			vtkPLY::ply_get_property(ply, elemName, &faceProps[0]);
			if (intensityAvailable)
			{
				vtkPLY::ply_get_property(ply, elemName, &faceProps[1]);
				intensity->SetNumberOfComponents(1);
				intensity->SetNumberOfTuples(numPolys);
			}
			if (RGBCellsAvailable)
			{
				vtkPLY::ply_get_property(ply, elemName, &faceProps[2]);
				vtkPLY::ply_get_property(ply, elemName, &faceProps[3]);
				vtkPLY::ply_get_property(ply, elemName, &faceProps[4]);
				RGBCells->SetNumberOfComponents(3);
				RGBCells->SetNumberOfTuples(numPolys);
			}

			for (int j = 0; j < numPolys; j++)
			{
				vtkPLY::ply_get_element(ply, (void *)&face);
				for (int k = 0; k < face.nverts; k++)
				{
					vtkVerts[k] = face.verts[k];
				}
				free(face.verts);

				polys->InsertNextCell(face.nverts, vtkVerts);
				if (intensityAvailable)
				{
					intensity->SetValue(j, face.intensity);
				}
				if (RGBCellsAvailable)
				{
					RGBCells->SetValue(3 * j, face.red);
					RGBCells->SetValue(3 * j + 1, face.green);
					RGBCells->SetValue(3 * j + 2, face.blue);
				}
			}
			output->SetPolys(polys);
		}

		free(elist[i]);
		elist[i] = NULL;

	}
	free(elist);

	vtkDebugMacro(<< "Read: " << numPts << " points, "
		<< numPolys << " polygons");

	vtkPLY::ply_close(ply);

	return 1;
}

int PLYImport::CanReadFile(const char *filename)
{
	FILE *fd = fopen(filename, "rb");
	if (!fd) return 0;

	char line[4] = {};
	const char *result = fgets(line, sizeof(line), fd);
	fclose(fd);
	return (result && strncmp(result, "ply", 3) == 0);
}
