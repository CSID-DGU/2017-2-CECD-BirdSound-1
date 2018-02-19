#include "OBJExport.h"

#include "vtkActorCollection.h"
#include "vtkAssemblyNode.h"
#include "vtkAssemblyPath.h"
#include "vtkCellArray.h"
#include "vtkDataSet.h"
#include "vtkFloatArray.h"
#include "vtkGeometryFilter.h"
#include "vtkMapper.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkTransform.h"

vtkStandardNewMacro(OBJExport);

OBJExport::OBJExport()
{
	this->FilePrefix = NULL;
}

OBJExport::~OBJExport()
{
	delete[] this->FilePrefix;
}

void OBJExport::WriteData()
{
	vtkRenderer *ren;
	FILE *fpObj, *fpMtl;
	vtkActorCollection *ac;
	vtkActor *anActor, *aPart;
	char nameObj[2048];
	char nameMtl[2048];
	int idStart = 1;

	if (this->FilePrefix == NULL)
	{
		vtkErrorMacro(<< "Please specify file prefix to use");
		return;
	}

	if (this->RenderWindow->GetRenderers()->GetNumberOfItems() > 1)
	{
		vtkErrorMacro(<< "obj files only support on renderer per window.");
		return;
	}

	ren = this->RenderWindow->GetRenderers()->GetFirstRenderer();

	if (ren->GetActors()->GetNumberOfItems() < 1)
	{
		vtkErrorMacro(<< "no actors found for writing .obj file.");
		return;
	}

	snprintf(nameObj, sizeof(nameObj), "%s.obj", this->FilePrefix);
	snprintf(nameMtl, sizeof(nameMtl), "%s.mtl", this->FilePrefix);
	fpObj = fopen(nameObj, "w");
	if (!fpObj)
	{
		vtkErrorMacro(<< "unable to open .obj files ");
		return;
	}
	fpMtl = fopen(nameMtl, "w");
	if (!fpMtl)
	{
		fclose(fpObj);
		vtkErrorMacro(<< "unable to open .mtl files ");
		return;
	}

	vtkDebugMacro("Writing wavefront files");
	fprintf(fpObj, "# wavefront obj file written by the visualization toolkit\n\n");
	fprintf(fpObj, "mtllib %s\n\n", nameMtl);
	fprintf(fpMtl, "# wavefront mtl file written by the visualization toolkit\n\n");

	ac = ren->GetActors();
	vtkAssemblyPath *apath;
	vtkCollectionSimpleIterator ait;
	for (ac->InitTraversal(ait); (anActor = ac->GetNextActor(ait)); )
	{
		for (anActor->InitPathTraversal(); (apath = anActor->GetNextPath()); )
		{
			aPart = static_cast<vtkActor *>(apath->GetLastNode()->GetViewProp());
			this->WriteAnActor(aPart, fpObj, fpMtl, idStart);
		}
	}

	fclose(fpObj);
	fclose(fpMtl);
}

void OBJExport::WriteAnActor(vtkActor *anActor, FILE *fpObj, FILE *fpMtl,
	int &idStart)
{
	vtkDataSet *ds;
	vtkNew<vtkPolyData> pd;
	vtkPointData *pntData;
	vtkPoints *points;
	vtkDataArray *tcoords;
	int i, i1, i2, idNext;
	vtkProperty *prop;
	double *tempd;
	double *p;
	vtkCellArray *cells;
	vtkNew<vtkTransform> trans;
	vtkIdType npts = 0;
	vtkIdType *indx = 0;

	if (anActor->GetMapper() == NULL)
	{
		return;
	}
	prop = anActor->GetProperty();
	if (anActor->GetVisibility() == 0)
	{
		return;
	}
	fprintf(fpMtl, "newmtl mtl%i\n", idStart);
	tempd = prop->GetAmbientColor();
	fprintf(fpMtl, "Ka %g %g %g\n", tempd[0], tempd[1], tempd[2]);
	tempd = prop->GetDiffuseColor();
	fprintf(fpMtl, "Kd %g %g %g\n", tempd[0], tempd[1], tempd[2]);
	tempd = prop->GetSpecularColor();
	fprintf(fpMtl, "Ks %g %g %g\n", tempd[0], tempd[1], tempd[2]);
	fprintf(fpMtl, "Ns %g\n", prop->GetSpecularPower());
	fprintf(fpMtl, "Tr %g ", prop->GetOpacity());
	fprintf(fpMtl, "illum 3\n\n");

	ds = anActor->GetMapper()->GetInput();
	if (ds == NULL)
	{
		return;
	}
	anActor->GetMapper()->GetInputAlgorithm()->Update();
	trans->SetMatrix(anActor->vtkProp3D::GetMatrix());

	if (ds->GetDataObjectType() != VTK_POLY_DATA)
	{
		vtkNew<vtkGeometryFilter> gf;
		gf->SetInputConnection(
			anActor->GetMapper()->GetInputConnection(0, 0));
		gf->Update();
		pd->DeepCopy(gf->GetOutput());
	}
	else
	{
		pd->DeepCopy(ds);
	}

	points = vtkPoints::New();
	trans->TransformPoints(pd->GetPoints(), points);
	for (i = 0; i < points->GetNumberOfPoints(); i++)
	{
		p = points->GetPoint(i);
		fprintf(fpObj, "v %g %g %g\n", p[0], p[1], p[2]);
	}
	idNext = idStart + static_cast<int>(points->GetNumberOfPoints());
	points->Delete();

	pntData = pd->GetPointData();
	if (pntData->GetNormals())
	{
		vtkNew<vtkFloatArray> normals;
		normals->SetNumberOfComponents(3);
		trans->TransformNormals(pntData->GetNormals(), normals.Get());
		for (i = 0; i < normals->GetNumberOfTuples(); i++)
		{
			p = normals->GetTuple(i);
			fprintf(fpObj, "vn %g %g %g\n", p[0], p[1], p[2]);
		}
	}

	tcoords = pntData->GetTCoords();
	if (tcoords)
	{
		for (i = 0; i < tcoords->GetNumberOfTuples(); i++)
		{
			p = tcoords->GetTuple(i);
			fprintf(fpObj, "vt %g %g\n", p[0], p[1]);
		}
	}

	fprintf(fpObj, "\ng grp%i\n", idStart);
	fprintf(fpObj, "usemtl mtl%i\n", idStart);

	if (pd->GetNumberOfVerts() > 0)
	{
		cells = pd->GetVerts();
		for (cells->InitTraversal(); cells->GetNextCell(npts, indx); )
		{
			fprintf(fpObj, "p ");
			for (i = 0; i < npts; i++)
			{
				fprintf(fpObj, "%i ", static_cast<int>(indx[i]) + idStart);
			}
			fprintf(fpObj, "\n");
		}
	}

	if (pd->GetNumberOfLines() > 0)
	{
		cells = pd->GetLines();
		for (cells->InitTraversal(); cells->GetNextCell(npts, indx); )
		{
			fprintf(fpObj, "l ");
			if (tcoords)
			{
				for (i = 0; i < npts; i++)
				{
					fprintf(fpObj, "%i/%i ", static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart);
				}
			}
			else
			{
				for (i = 0; i < npts; i++)
				{
					fprintf(fpObj, "%i ", static_cast<int>(indx[i]) + idStart);
				}
			}
			fprintf(fpObj, "\n");
		}
	}

	if (pd->GetNumberOfPolys() > 0)
	{
		cells = pd->GetPolys();
		for (cells->InitTraversal(); cells->GetNextCell(npts, indx); )
		{
			fprintf(fpObj, "f ");
			for (i = 0; i < npts; i++)
			{
				if (pntData->GetNormals())
				{
					if (tcoords)
					{
						fprintf(fpObj, "%i/%i/%i ", static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart);
					}
					else
					{
						fprintf(fpObj, "%i//%i ", static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart);
					}
				}
				else
				{
					if (tcoords)
					{
						fprintf(fpObj, "%i/%i ", static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart);
					}
					else
					{
						fprintf(fpObj, "%i ", static_cast<int>(indx[i]) + idStart);
					}
				}
			}
			fprintf(fpObj, "\n");
		}
	}

	if (pd->GetNumberOfStrips() > 0)
	{
		cells = pd->GetStrips();
		for (cells->InitTraversal(); cells->GetNextCell(npts, indx); )
		{
			for (i = 2; i < npts; i++)
			{
				if (i % 2 == 0)
				{
					i1 = i - 2;
					i2 = i - 1;
				}
				else
				{
					i1 = i - 1;
					i2 = i - 2;
				}
				if (pntData->GetNormals())
				{
					if (tcoords)
					{
						fprintf(fpObj, "f %i/%i/%i ", static_cast<int>(indx[i1]) + idStart, static_cast<int>(indx[i1]) + idStart, static_cast<int>(indx[i1]) + idStart);
						fprintf(fpObj, "%i/%i/%i ", static_cast<int>(indx[i2]) + idStart, static_cast<int>(indx[i2]) + idStart, static_cast<int>(indx[i2]) + idStart);
						fprintf(fpObj, "%i/%i/%i\n", static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart);
					}
					else
					{
						fprintf(fpObj, "f %i//%i ", static_cast<int>(indx[i1]) + idStart, static_cast<int>(indx[i1]) + idStart);
						fprintf(fpObj, "%i//%i ", static_cast<int>(indx[i2]) + idStart, static_cast<int>(indx[i2]) + idStart);
						fprintf(fpObj, "%i//%i\n", static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart);
					}
				}
				else
				{
					if (tcoords)
					{
						fprintf(fpObj, "f %i/%i ", static_cast<int>(indx[i1]) + idStart, static_cast<int>(indx[i1]) + idStart);
						fprintf(fpObj, "%i/%i ", static_cast<int>(indx[i2]) + idStart, static_cast<int>(indx[i2]) + idStart);
						fprintf(fpObj, "%i/%i\n", static_cast<int>(indx[i]) + idStart, static_cast<int>(indx[i]) + idStart);
					}
					else
					{
						fprintf(fpObj, "f %i %i %i\n", static_cast<int>(indx[i1]) + idStart, static_cast<int>(indx[i2]) + idStart, static_cast<int>(indx[i]) + idStart);
					}
				}
			}
		}
	}

	idStart = idNext;
}
