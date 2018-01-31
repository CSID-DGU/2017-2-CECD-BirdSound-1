void Realsense::MeshConstruct(vtkPoints *point, int saveType)
{
	vtkCellArray *cell = vtkCellArray::New();
	double *ptr;

	std::cout << point->GetNumberOfPoints() << "\n";

	for (vtkIdType i = 0; i < point->GetNumberOfPoints() - width; i++)
	{
		ptr = point->GetPoint(i);
		double orign[3] = { ptr[0],ptr[1],ptr[2] };

		ptr = point->GetPoint(i + 1);
		double right[3] = { ptr[0],ptr[1],ptr[2] };

		ptr = point->GetPoint(i + width);
		double down[3] = { ptr[0],ptr[1],ptr[2] };

		ptr = point->GetPoint(i + width + 1);
		double diga[3] = { ptr[0],ptr[1],ptr[2] };

		if ((i + 1) % width == 0)continue;
		if (orign[0] == 0)continue;

		double _dia = getDistane(orign, diga);
		double _down = getDistane(orign, down);

		if (_down < _dia)
		{
			if (right[0] != 0 && down[0] != 0)
			{
				cell->InsertNextCell(3);
				cell->InsertCellPoint(i); cell->InsertCellPoint(i + 1); cell->InsertCellPoint(i + width);
			}

			if (right[0] != 0 && diga[0] != 0)
			{
				cell->InsertNextCell(3);
				cell->InsertCellPoint(i + 1); cell->InsertCellPoint(i + width + 1); cell->InsertCellPoint(i + width);
			}
		}

		else
		{
			if (right[0] != 0 && diga[0] != 0)
			{
				cell->InsertNextCell(3);
				cell->InsertCellPoint(i); cell->InsertCellPoint(i + 1); cell->InsertCellPoint(i + width + 1);
			}

			if (diga[0] != 0 && down[0] != 0)
			{
				cell->InsertNextCell(3);
				cell->InsertCellPoint(i); cell->InsertCellPoint(i + width + 1); cell->InsertCellPoint(i + width);
			}
		}
	}


	vtkPolyData *poly = vtkPolyData::New();
	poly->SetPoints(point);
	poly->SetPolys(cell);

	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputData(poly);

	vtkRenderer *renderer = vtkRenderer::New();
	renderer->GetActiveCamera()->ParallelProjectionOff();

	vtkActor *actor = vtkActor::New();
	actor->SetMapper(mapper);
	renderer->AddActor(actor);

	vtkRenderWindow *win = vtkRenderWindow::New();
	vtkRenderWindowInteractor * interactor = vtkRenderWindowInteractor::New();
	interactor->SetRotation(0.1);
	win->AddRenderer(renderer);


	if (saveType == 1)
	{
		vtkSTLWriter* stlWriter = vtkSTLWriter::New();
		stlWriter->SetFileName("my.stl");

		stlWriter->SetInputData(poly);
		stlWriter->Write();
		stlWriter->Delete();
	}

	else if (saveType == 2) {
		vtkOBJExporter *obj = vtkOBJExporter::New();
		obj->SetInput(win);
		obj->SetFilePrefix("mine");
		obj->Write();
		obj->Delete();
	}

	interactor->SetRenderWindow(win);
	interactor->Start();



	poly->Delete();
	mapper->Delete();
	renderer->Delete();
	actor->Delete();
	win->Delete();
	interactor->Delete();
	cell->Delete();
}