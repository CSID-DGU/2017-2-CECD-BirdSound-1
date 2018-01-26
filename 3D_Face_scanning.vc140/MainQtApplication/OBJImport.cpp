#include "OBJImport.h"

#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include <cctype>

vtkStandardNewMacro(OBJImport);

OBJImport::OBJImport()
{
	this->FileName = NULL;

	this->SetNumberOfInputPorts(0);
}

OBJImport::~OBJImport()
{
	delete[] this->FileName;
	this->FileName = NULL;
}

int OBJImport::RequestData( vtkInformation *vtkNotUsed(request), vtkInformationVector **vtkNotUsed(inputVector), vtkInformationVector *outputVector)
{
	vtkInformation *outInfo = outputVector->GetInformationObject(0);

	vtkPolyData *output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

	if (!this->FileName)
	{
		vtkErrorMacro(<< "A FileName must be specified.");
		return 0;
	}

	FILE *in = fopen(this->FileName, "r");

	if (in == NULL)
	{
		vtkErrorMacro(<< "File " << this->FileName << " not found");
		return 0;
	}

	vtkDebugMacro(<< "Reading file");

	vtkPoints *points = vtkPoints::New();
	std::vector<vtkFloatArray*> tcoords_vector;
	vtkFloatArray *normals = vtkFloatArray::New();
	normals->SetNumberOfComponents(3);
	normals->SetName("Normals");
	vtkCellArray *polys = vtkCellArray::New();
	vtkCellArray *tcoord_polys = vtkCellArray::New();

	vtkCellArray *pointElems = vtkCellArray::New();
	vtkCellArray *lineElems = vtkCellArray::New();
	vtkCellArray *normal_polys = vtkCellArray::New();

	bool hasTCoords = false;
	bool hasNormals = false;
	bool tcoords_same_as_verts = true;
	bool normals_same_as_verts = true;
	bool everything_ok = true;

	{

		const int MAX_LINE = 1024;
		char rawLine[MAX_LINE];
		char tcoordsName[100];
		float xyz[3];
		int numPoints = 0;
		int numTCoords = 0;
		int numNormals = 0;

		int lineNr = 0;
		while (everything_ok && fgets(rawLine, MAX_LINE, in) != NULL)
		{
			lineNr++;
			char *pLine = rawLine;
			char *pEnd = rawLine + strlen(rawLine);

			while (isspace(*pLine) && pLine < pEnd) { pLine++; }

			const char *cmd = pLine;

			while (!isspace(*pLine) && pLine < pEnd) { pLine++; }

			if (pLine < pEnd)
			{
				*pLine = '\0';
				pLine++;
			}

			if (strcmp(cmd, "usemtl") == 0)
			{
				if (sscanf(pLine, "%s", tcoordsName) == 1)
				{
					if (fgets(rawLine, MAX_LINE, in) != NULL)
					{
						lineNr++;
						pLine = rawLine;
						pEnd = rawLine + strlen(rawLine);
						while (isspace(*pLine) && pLine < pEnd) { pLine++; }
						cmd = pLine;
						while (!isspace(*pLine) && pLine < pEnd) { pLine++; }
						if (pLine < pEnd)
						{
							*pLine = '\0';
							pLine++;
						}
						if (strcmp(cmd, "vt") == 0)
						{
							vtkFloatArray* tcoords = vtkFloatArray::New();
							tcoords->SetNumberOfComponents(2);
							tcoords->SetName(tcoordsName);
							tcoords_vector.push_back(tcoords);
						}
					}
					else
					{
						vtkErrorMacro(<< "Error reading continuation line at line " << lineNr);
						everything_ok = false;
					}
				}
				else
				{
					vtkErrorMacro(<< "Error reading 'usemtl' at line " << lineNr);
					everything_ok = false;
				}
			}
		}

		if (tcoords_vector.size() == 0)
		{
			vtkFloatArray *tcoords = vtkFloatArray::New();
			tcoords->SetNumberOfComponents(2);
			tcoords->SetName("TCoords");
			tcoords_vector.push_back(tcoords);
			strcpy(tcoordsName, "TCoords");
		}

		lineNr = 0;
		fseek(in, 0, SEEK_SET);
		while (everything_ok && fgets(rawLine, MAX_LINE, in) != NULL)
		{
			lineNr++;
			char *pLine = rawLine;
			char *pEnd = rawLine + strlen(rawLine);

			while (isspace(*pLine) && pLine < pEnd) { pLine++; }

			const char *cmd = pLine;

			while (!isspace(*pLine) && pLine < pEnd) { pLine++; }

			if (pLine < pEnd)
			{
				*pLine = '\0';
				pLine++;
			}

			if (strcmp(cmd, "v") == 0)
			{
				if (sscanf(pLine, "%f %f %f", xyz, xyz + 1, xyz + 2) == 3)
				{
					points->InsertNextPoint(xyz);
					numPoints++;
				}
				else
				{
					vtkErrorMacro(<< "Error reading 'v' at line " << lineNr);
					everything_ok = false;
				}
			}
			else if (strcmp(cmd, "usemtl") == 0)
			{
				if (sscanf(pLine, "%s", tcoordsName) != 1)
				{
					vtkErrorMacro(<< "Error reading 'usemtl' at line " << lineNr);
					everything_ok = false;
				}
			}
			else if (strcmp(cmd, "vt") == 0)
			{
				if (sscanf(pLine, "%f %f", xyz, xyz + 1) == 2)
				{
					for (unsigned int i = 0; i < tcoords_vector.size(); ++i)
					{
						vtkFloatArray* tcoords = tcoords_vector.at(i);
						if (strcmp(tcoords->GetName(), tcoordsName) == 0)
						{
							tcoords->InsertNextTuple(xyz);
						}
						else
						{
							tcoords->InsertNextTuple2(-1.0, -1.0);
						}
					}
					numTCoords++;
				}
				else
				{
					vtkErrorMacro(<< "Error reading 'vt' at line " << lineNr);
					everything_ok = false;
				}
			}
			else if (strcmp(cmd, "vn") == 0)
			{
				if (sscanf(pLine, "%f %f %f", xyz, xyz + 1, xyz + 2) == 3)
				{
					normals->InsertNextTuple(xyz);
					hasNormals = true;
					numNormals++;
				}
				else
				{
					vtkErrorMacro(<< "Error reading 'vn' at line " << lineNr);
					everything_ok = false;
				}
			}
			else if (strcmp(cmd, "p") == 0)
			{
				pointElems->InsertNextCell(0);

				int nVerts = 0;

				while (everything_ok && pLine < pEnd)
				{
					while (isspace(*pLine) && pLine < pEnd) { pLine++; }

					if (pLine < pEnd)
					{
						int iVert;
						if (sscanf(pLine, "%d", &iVert) == 1)
						{
							if (iVert < 0)
							{
								pointElems->InsertCellPoint(numPoints + iVert);
							}
							else
							{
								pointElems->InsertCellPoint(iVert - 1);
							}
							nVerts++;
						}
						else if (strcmp(pLine, "\\\n") == 0)
						{
							if (fgets(rawLine, MAX_LINE, in) != NULL)
							{
								lineNr++;
								pLine = rawLine;
								pEnd = rawLine + strlen(rawLine);
								continue;
							}
							else
							{
								vtkErrorMacro(<< "Error reading continuation line at line " << lineNr);
								everything_ok = false;
							}
						}
						else
						{
							vtkErrorMacro(<< "Error reading 'p' at line " << lineNr);
							everything_ok = false;
						}
						while (!isspace(*pLine) && pLine < pEnd) { pLine++; }
					}
				}

				if (nVerts < 1)
				{
					vtkErrorMacro
					(
						<< "Error reading file near line " << lineNr
						<< " while processing the 'p' command"
					);
					everything_ok = false;
				}

				pointElems->UpdateCellCount(nVerts);
			}
			else if (strcmp(cmd, "l") == 0)
			{
				lineElems->InsertNextCell(0);

				int nVerts = 0;

				while (everything_ok && pLine < pEnd)
				{
					while (isspace(*pLine) && pLine < pEnd) { pLine++; }

					if (pLine < pEnd)
					{
						int iVert, dummyInt;
						if (sscanf(pLine, "%d/%d", &iVert, &dummyInt) == 2)
						{
							if (iVert < 0)
							{
								lineElems->InsertCellPoint(numPoints + iVert);
							}
							else
							{
								lineElems->InsertCellPoint(iVert - 1);
							}
							nVerts++;
						}
						else if (sscanf(pLine, "%d", &iVert) == 1)
						{
							if (iVert < 0)
							{
								lineElems->InsertCellPoint(numPoints + iVert);
							}
							else
							{
								lineElems->InsertCellPoint(iVert - 1);
							}
							nVerts++;
						}
						else if (strcmp(pLine, "\\\n") == 0)
						{
							if (fgets(rawLine, MAX_LINE, in) != NULL)
							{
								lineNr++;
								pLine = rawLine;
								pEnd = rawLine + strlen(rawLine);
								continue;
							}
							else
							{
								vtkErrorMacro(<< "Error reading continuation line at line " << lineNr);
								everything_ok = false;
							}
						}
						else
						{
							vtkErrorMacro(<< "Error reading 'l' at line " << lineNr);
							everything_ok = false;
						}
						while (!isspace(*pLine) && pLine < pEnd) { pLine++; }
					}
				}

				if (nVerts < 2)
				{
					vtkErrorMacro
					(
						<< "Error reading file near line " << lineNr
						<< " while processing the 'l' command"
					);
					everything_ok = false;
				}

				lineElems->UpdateCellCount(nVerts);
			}
			else if (strcmp(cmd, "f") == 0)
			{
				polys->InsertNextCell(0);
				tcoord_polys->InsertNextCell(0);
				normal_polys->InsertNextCell(0);

				int nVerts = 0, nTCoords = 0, nNormals = 0;

				while (everything_ok && pLine < pEnd)
				{
					while (isspace(*pLine) && pLine < pEnd) { pLine++; }

					if (pLine < pEnd)
					{
						int iVert, iTCoord, iNormal;
						if (sscanf(pLine, "%d/%d/%d", &iVert, &iTCoord, &iNormal) == 3)
						{
							if (iVert < 0)
							{
								polys->InsertCellPoint(numPoints + iVert);
							}
							else
							{
								polys->InsertCellPoint(iVert - 1);
							}
							nVerts++;

							if (iTCoord < 0)
							{
								tcoord_polys->InsertCellPoint(numTCoords + iTCoord);
							}
							else
							{
								tcoord_polys->InsertCellPoint(iTCoord - 1);
							}
							nTCoords++;

							if (iNormal < 0)
							{
								normal_polys->InsertCellPoint(numNormals + iNormal);
							}
							else
							{
								normal_polys->InsertCellPoint(iNormal - 1);
							}
							nNormals++;
							if (iTCoord != iVert)
								tcoords_same_as_verts = false;
							if (iNormal != iVert)
								normals_same_as_verts = false;
						}
						else if (sscanf(pLine, "%d//%d", &iVert, &iNormal) == 2)
						{
							if (iVert < 0)
							{
								polys->InsertCellPoint(numPoints + iVert);
							}
							else
							{
								polys->InsertCellPoint(iVert - 1);
							}
							nVerts++;

							if (iNormal < 0)
							{
								normal_polys->InsertCellPoint(numNormals + iNormal);
							}
							else
							{
								normal_polys->InsertCellPoint(iNormal - 1);
							}
							nNormals++;
							if (iNormal != iVert)
								normals_same_as_verts = false;
						}
						else if (sscanf(pLine, "%d/%d", &iVert, &iTCoord) == 2)
						{
							if (iVert < 0)
							{
								polys->InsertCellPoint(numPoints + iVert);
							}
							else
							{
								polys->InsertCellPoint(iVert - 1);
							}
							nVerts++;

							if (iTCoord < 0)
							{
								tcoord_polys->InsertCellPoint(numTCoords + iTCoord);
							}
							else
							{
								tcoord_polys->InsertCellPoint(iTCoord - 1);
							}
							nTCoords++;
							if (iTCoord != iVert)
								tcoords_same_as_verts = false;
						}
						else if (sscanf(pLine, "%d", &iVert) == 1)
						{
							if (iVert < 0)
							{
								polys->InsertCellPoint(numPoints + iVert);
							}
							else
							{
								polys->InsertCellPoint(iVert - 1);
							}
							nVerts++;
						}
						else if (strcmp(pLine, "\\\n") == 0)
						{
							if (fgets(rawLine, MAX_LINE, in) != NULL)
							{
								lineNr++;
								pLine = rawLine;
								pEnd = rawLine + strlen(rawLine);
								continue;
							}
							else
							{
								vtkErrorMacro(<< "Error reading continuation line at line " << lineNr);
								everything_ok = false;
							}
						}
						else
						{
							vtkErrorMacro(<< "Error reading 'f' at line " << lineNr);
							everything_ok = false;
						}
						while (!isspace(*pLine) && pLine < pEnd) { pLine++; }
					}
				}

				if (nVerts < 3 ||
					(nTCoords > 0 && nTCoords != nVerts) ||
					(nNormals > 0 && nNormals != nVerts)
					)
				{
					vtkErrorMacro
					(
						<< "Error reading file near line " << lineNr
						<< " while processing the 'f' command"
					);
					everything_ok = false;
				}

				polys->UpdateCellCount(nVerts);
				tcoord_polys->UpdateCellCount(nTCoords);
				normal_polys->UpdateCellCount(nNormals);

				if (nTCoords > 0) { hasTCoords = true; }
				if (nNormals > 0) { hasNormals = true; }
			}
			else
			{
				//vtkDebugMacro(<<"Ignoring line: "<<rawLine);
			}
		}
	}

	fclose(in);


	if (everything_ok)
	{
		if (
			(!hasTCoords || tcoords_same_as_verts) &&
			(!hasNormals || normals_same_as_verts)
			)
		{
			vtkDebugMacro(<< "Copying file data into the output directly");

			output->SetPoints(points);
			if (pointElems->GetNumberOfCells())
			{
				output->SetVerts(pointElems);
			}
			if (lineElems->GetNumberOfCells())
			{
				output->SetLines(lineElems);
			}
			if (polys->GetNumberOfCells())
			{
				output->SetPolys(polys);
			}

			if (hasTCoords && tcoords_same_as_verts)
			{
				for (unsigned int i = 0; i < tcoords_vector.size(); ++i)
				{
					vtkFloatArray* tcoords = tcoords_vector.at(i);
					output->GetPointData()->AddArray(tcoords);
					if (i == 0)
					{
						output->GetPointData()->SetActiveTCoords(tcoords->GetName());
					}
				}
			}

			if (hasNormals && normals_same_as_verts)
			{
				output->GetPointData()->SetNormals(normals);
			}
			output->Squeeze();
		}
		else
		{
			vtkDebugMacro(<< "Duplicating vertices so that tcoords and normals are correct");

			vtkPoints *new_points = vtkPoints::New();
			std::vector<vtkFloatArray*> new_tcoords_vector;
			for (unsigned int i = 0; i < tcoords_vector.size(); ++i)
			{
				vtkFloatArray* tcoords = tcoords_vector.at(i);
				vtkFloatArray *new_tcoords = vtkFloatArray::New();
				new_tcoords->SetName(tcoords->GetName());
				new_tcoords->SetNumberOfComponents(2);
				new_tcoords_vector.push_back(new_tcoords);
			}
			vtkFloatArray *new_normals = vtkFloatArray::New();
			new_normals->SetNumberOfComponents(3);
			new_normals->SetName("Normals");
			vtkCellArray *new_polys = vtkCellArray::New();

			polys->InitTraversal();
			tcoord_polys->InitTraversal();
			normal_polys->InitTraversal();

			vtkIdType dummy_warning_prevention_mechanism[1];
			vtkIdType n_pts = -1, *pts = dummy_warning_prevention_mechanism;
			vtkIdType n_tcoord_pts = -1, *tcoord_pts = dummy_warning_prevention_mechanism;
			vtkIdType n_normal_pts = -1, *normal_pts = dummy_warning_prevention_mechanism;
			for (int i = 0; i<polys->GetNumberOfCells(); ++i)
			{
				polys->GetNextCell(n_pts, pts);
				tcoord_polys->GetNextCell(n_tcoord_pts, tcoord_pts);
				normal_polys->GetNextCell(n_normal_pts, normal_pts);

				if ((n_pts != n_tcoord_pts && hasTCoords) || (n_pts != n_normal_pts && hasNormals))
				{
					vtkDebugMacro(<< "Skipping poly " << i + 1 << " (1-based index)");
				}
				else
				{
					for (int j = 0; j<n_pts; ++j)
					{
						if (n_tcoord_pts>0)
						{
							for (unsigned int k = 0; k < tcoords_vector.size(); ++k)
							{
								vtkFloatArray* new_tcoords = new_tcoords_vector.at(k);
								vtkFloatArray* tcoords = tcoords_vector.at(k);
								new_tcoords->InsertNextTuple(tcoords->GetTuple(tcoord_pts[j]));
							}
						}
						if (n_normal_pts>0)
						{
							new_normals->InsertNextTuple(normals->GetTuple(normal_pts[j]));
						}
						pts[j] = new_points->InsertNextPoint(points->GetPoint(pts[j]));
					}
					new_polys->InsertNextCell(n_pts, pts);
				}
			}

			output->SetPoints(new_points);
			output->SetPolys(new_polys);
			if (hasTCoords)
			{
				for (unsigned int i = 0; i < new_tcoords_vector.size(); ++i)
				{
					vtkFloatArray* new_tcoords = new_tcoords_vector.at(i);
					output->GetPointData()->AddArray(new_tcoords);
					if (i == 0)
					{
						output->GetPointData()->SetActiveTCoords(new_tcoords->GetName());
					}
				}
			}
			if (hasNormals)
			{
				output->GetPointData()->SetNormals(new_normals);
			}

			output->Squeeze();

			new_points->Delete();
			new_polys->Delete();
			for (unsigned int i = 0; i < new_tcoords_vector.size(); ++i)
			{
				vtkFloatArray* new_tcoords = new_tcoords_vector.at(i);
				new_tcoords->Delete();
			}
			new_normals->Delete();
		}
	}

	points->Delete();
	for (unsigned int i = 0; i < tcoords_vector.size(); ++i)
	{
		vtkFloatArray* tcoords = tcoords_vector.at(i);
		tcoords->Delete();
	}
	normals->Delete();
	polys->Delete();
	tcoord_polys->Delete();
	normal_polys->Delete();

	lineElems->Delete();
	pointElems->Delete();

	return 1;
}
