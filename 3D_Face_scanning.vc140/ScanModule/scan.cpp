#include"Scan.h"


double Scan::getDistane(double *src, double *tar)
{
	double retv = 0.0;
	//if (tar[0] == 0)return INF;
	//retv += (src[0] - tar[0])*(src[0] - tar[0]);
	//retv += (src[1] - tar[1])*(src[1] - tar[1]);
	retv += (src[2] - tar[2])*(src[2] - tar[2]);
	return retv;
}

void  Scan::cellInsert(vtkCellArray *cell, int number, long long index1, long long index2, long long index3, long long disp)
{
	cell->InsertNextCell(number);
	cell->InsertCellPoint(index1 + disp); cell->InsertCellPoint(index2 + disp); cell->InsertCellPoint(index3 + disp);

}

vtkRenderer*  Scan::MeshConstructWithOMP(vtkPoints *point, int saveType, int ThreadSize)
{
	vtkRenderer *threadRenderer;
	vtkRenderWindow *win = vtkRenderWindow::New();
	vtkRenderWindowInteractor * interactor = vtkRenderWindowInteractor::New();
	interactor->SetRotation(0.1);

	//std::cout << point->GetNumberOfPoints() << "\n";

	threadRenderer = vtkRenderer::New();
	const int ThreadNum = ThreadSize;
	//omp_set_num_threads(4);

#pragma omp parallel num_threads(ThreadNum)		 
	{
		vtkPoints *threadPoint = vtkPoints::New();
		vtkCellArray *threadCell = vtkCellArray::New();
		vtkPolyData *threadPoly = vtkPolyData::New();
		vtkPolyDataMapper *threadMapper = vtkPolyDataMapper::New();
		vtkActor *threadActor = vtkActor::New();

		threadPoint->SetNumberOfPoints(width*height / ThreadNum);

#pragma omp for
		for (int i = 0; i < width*height; i++)
		{
			double temp[3];
			point->GetPoint(i, temp);
			threadPoint->SetPoint(i - (omp_get_thread_num()) * width*height / ThreadNum, temp);
			//threadPoint->InsertNextPoint(temp);		
		}
		//printf("%lf\n\n", omp_get_wtime() - _start);

		for (vtkIdType i = 0; i < threadPoint->GetNumberOfPoints(); i++)
		{
			if (i + 1 + width > threadPoint->GetNumberOfPoints())break;
			if ((i + 1) % width == 0)continue;

			double orign[3], right[3], down[3], diga[3];
			//printf("%d %d\n", i,omp_get_thread_num());	
			threadPoint->GetPoint(i, orign);
			if (orign[0] == 0)continue;

			threadPoint->GetPoint(i + 1, right);
			threadPoint->GetPoint(i + width, down);
			threadPoint->GetPoint(i + width + 1, diga);

			double _dia = getDistane(orign, diga);
			double _down = getDistane(orign, down);

			if (_down < _dia)
			{
				if (right[0] != 0 && down[0] != 0)
				{
					cellInsert(threadCell, 3, i, i + 1, i + width);
					if (diga[0] != 0)
						cellInsert(threadCell, 3, i + 1, i + width + 1, i + width);
				}
			}

			else
			{
				if (diga[0] != 0)
				{
					if (right[0] != 0)
						cellInsert(threadCell, 3, i, i + 1, i + width + 1);
					if (down[0] != 0)
						cellInsert(threadCell, 3, i, i + width + 1, i + width);
				}
			}

		}


		threadPoly->SetPoints(threadPoint);
		threadPoly->SetPolys(threadCell);

		threadMapper->SetInputData(threadPoly);
		threadActor->SetMapper(threadMapper);

#pragma omp critical
		{
			threadRenderer->AddActor(threadActor);
		}

		threadPoint->Delete();
		threadCell->Delete();
		threadPoly->Delete();
		threadMapper->Delete();
		threadActor->Delete();

	}

	//double _start = omp_get_wtime();
	vtkPoints *boundary = vtkPoints::New();
	vtkCellArray *cellBoundary = vtkCellArray::New();
	vtkPolyData *polyBoundary = vtkPolyData::New();
	vtkActor *actorBoundary = vtkActor::New();
	vtkPolyDataMapper *mapperBoundary = vtkPolyDataMapper::New();

	for (int j = 1; j <= ThreadNum - 1; j++)
	{
		for (int i = j*width * height / ThreadNum - width; i <j*width * height / ThreadNum + width * 2 - width; i++)
		{
			double temp[3];
			point->GetPoint(i, temp);
			boundary->InsertNextPoint(temp);
		}
	}


	for (int j = 0; j < ThreadNum - 1; j++)
	{
		for (vtkIdType i = 2 * j*width; i < 2 * width*j + width; i++)
		{
			double orign[3], right[3], down[3], diga[3];
			boundary->GetPoint(i, orign);
			boundary->GetPoint(i + 1, right);
			boundary->GetPoint(i + width, down);
			boundary->GetPoint(i + width + 1, diga);

			if (orign[0] == 0)continue;

			double _dia = getDistane(orign, diga);
			double _down = getDistane(orign, down);

			if (_down < _dia)
			{
				if (right[0] != 0 && down[0] != 0)
				{
					cellInsert(cellBoundary, 3, i, i + 1, i + width);
					if (diga[0] != 0)
						cellInsert(cellBoundary, 3, i + 1, i + width + 1, i + width);
				}
			}

			else
			{
				if (diga[0] != 0)
				{
					if (right[0] != 0)
						cellInsert(cellBoundary, 3, i, i + 1, i + width + 1);
					if (down[0] != 0)
						cellInsert(cellBoundary, 3, i, i + width + 1, i + width);
				}
			}

		}
	}
	polyBoundary->SetPoints(boundary);
	polyBoundary->SetPolys(cellBoundary);
	mapperBoundary->SetInputData(polyBoundary);
	actorBoundary->SetMapper(mapperBoundary);

	threadRenderer->AddActor(actorBoundary);

	threadRenderer->GetActiveCamera()->ParallelProjectionOff();
	win->AddRenderer(threadRenderer);

	interactor->SetRenderWindow(win);
	interactor->Start();

	boundary->Delete();
	cellBoundary->Delete();
	polyBoundary->Delete();
	actorBoundary->Delete();
	mapperBoundary->Delete();

	interactor->Delete();
	threadRenderer->Delete();
	win->Delete();

	//printf("%lf\n\n", omp_get_wtime() - _start);
	return threadRenderer;
}

/*보완 필요*/
vtkRenderer*  Scan::MeshConstructWithOMPnSIMD(vtkPoints *point, int saveType, int ThreadSize)
{
	vtkRenderer *threadRenderer = vtkRenderer::New();
	vtkRenderWindow *win = vtkRenderWindow::New();
	vtkRenderWindowInteractor * interactor = vtkRenderWindowInteractor::New();
	interactor->SetRotation(0.1);

	//std::cout << point->GetNumberOfPoints() << "\n";

	const int ThreadNum = ThreadSize;

#pragma omp parallel num_threads(ThreadNum)	shared(threadRenderer) 
	{
		vtkPoints *threadPoint = vtkPoints::New();
		vtkCellArray *threadCell = vtkCellArray::New();
		vtkPolyData *threadPoly = vtkPolyData::New();
		vtkPolyDataMapper *threadMapper = vtkPolyDataMapper::New();
		vtkActor *threadActor = vtkActor::New();

		__declspec(align(64)) double _orign[4] = { 0, };
		__declspec(align(64)) double _right[4] = { 0, };
		__declspec(align(64)) double _down[4] = { 0, };
		__declspec(align(64)) double _diga[4] = { 0, };
		__declspec(align(64)) double result[4] = { 0, };

#pragma omp for
		for (int i = 0; i < width*height; i++)
		{
			double temp[3];
			point->GetPoint(i, temp);
			threadPoint->InsertNextPoint(temp);
		}

		for (int j = 0; j<threadPoint->GetNumberOfPoints() - width; j += 4)
		{
			/*seting*/
			int index = 0;
			double orign[3], right[3], down[3], diga[3];
			for (int k = j; k < j + 4; k++)
			{
				threadPoint->GetPoint(k, orign);
				threadPoint->GetPoint(k + 1, right);
				threadPoint->GetPoint(k + width, down);
				threadPoint->GetPoint(k + width + 1, diga);

				_orign[index] = orign[2];
				_right[index] = right[2];
				_down[index] = down[2];
				_diga[index] = diga[2];
				index++;
			}

			/*chunk calculate*/
			__m256d __m256d_orign = _mm256_loadu_pd(_orign);
			__m256d __m256d_down = _mm256_loadu_pd(_down);
			__m256d __m256d_diga = _mm256_loadu_pd(_diga);
			__m256d __m256d_result = _mm256_sub_pd(_mm256_sub_pd(__m256d_orign, __m256d_down), \
				_mm256_sub_pd(__m256d_orign, __m256d_diga));

			__m256d_result = _mm256_mul_pd(__m256d_result, __m256d_result);//거리를 제곱으로 구함.
			_mm256_store_pd(result, __m256d_result);

			/*make poly*/
			for (int i = 0; i < 4; i++)
			{
				if (_orign[i] == 0)continue;

				if (result[i] > 0)//아래랑 연결
				{
					if (_right[i] != 0 && _down[i] != 0)
					{
						cellInsert(threadCell, 3, i, i + 1, i + width, j);
						if (_diga[i] != 0)
							cellInsert(threadCell, 3, i + 1, i + width + 1, i + width, j);
					}
				}

				else //if (result[i] < 0)//대각선연결
				{
					if (_diga[i] != 0)
					{
						if (_right[i] != 0)
							cellInsert(threadCell, 3, i, i + 1, i + width + 1, j);
						if (_down[i] != 0)
							cellInsert(threadCell, 3, i, i + width + 1, i + width, j);
					}
				}
			}
		}

		//_start = omp_get_wtime();

		threadPoly->SetPoints(threadPoint);
		threadPoly->SetPolys(threadCell);

		threadMapper->SetInputData(threadPoly);
		threadActor->SetMapper(threadMapper);

#pragma omp critical
		{
			threadRenderer->AddActor(threadActor);
		}
		threadPoint->Delete();
		threadCell->Delete();
		threadPoly->Delete();
		threadMapper->Delete();
		threadActor->Delete();

		//printf("%lf\n\n", omp_get_wtime() - _start);
	}


	vtkPoints *boundary = vtkPoints::New();
	vtkCellArray *cellBoundary = vtkCellArray::New();
	vtkPolyData *polyBoundary = vtkPolyData::New();
	vtkActor *actorBoundary = vtkActor::New();
	vtkPolyDataMapper *mapperBoundary = vtkPolyDataMapper::New();

	for (int j = 1; j <= ThreadNum - 1; j++)
	{
		for (int i = j*width * height / ThreadNum - width; i <j*width * height / ThreadNum + width * 2 - width; i++)
		{
			double temp[3];
			point->GetPoint(i, temp);
			boundary->InsertNextPoint(temp);
		}
	}

	/*여기도 simd적용해볼 것.*/
	for (int j = 0; j < ThreadNum - 1; j++)
	{
		double orign[3], right[3], down[3], diga[3];
		for (vtkIdType i = 2 * j*width; i < 2 * width*j + width; i++)
		{
			boundary->GetPoint(i, orign);
			boundary->GetPoint(i + 1, right);
			boundary->GetPoint(i + width, down);
			boundary->GetPoint(i + width + 1, diga);


			if (orign[0] == 0)continue;

			double _dia = getDistane(orign, diga);
			double _down = getDistane(orign, down);

			if (_down < _dia)
			{
				if (right[0] != 0 && down[0] != 0)
				{
					cellInsert(cellBoundary, 3, i, i + 1, i + width);
					if (diga[0] != 0)
						cellInsert(cellBoundary, 3, i + 1, i + width + 1, i + width);
				}
			}

			else
			{
				if (diga[0] != 0)
				{
					if (right[0] != 0)
						cellInsert(cellBoundary, 3, i, i + 1, i + width + 1);
					if (down[0] != 0)
						cellInsert(cellBoundary, 3, i, i + width + 1, i + width);
				}
			}

		}
	}
	polyBoundary->SetPoints(boundary);
	polyBoundary->SetPolys(cellBoundary);
	mapperBoundary->SetInputData(polyBoundary);
	actorBoundary->SetMapper(mapperBoundary);

	threadRenderer->AddActor(actorBoundary);

	threadRenderer->GetActiveCamera()->ParallelProjectionOff();
	win->AddRenderer(threadRenderer);
	//win->Render();


	interactor->SetRenderWindow(win);
	//interactor->Start();

	boundary->Delete();
	cellBoundary->Delete();
	polyBoundary->Delete();
	actorBoundary->Delete();
	mapperBoundary->Delete();

	interactor->Delete();
	threadRenderer->Delete();
	win->Delete();

	return threadRenderer;
	//printf("%lf\n\n", omp_get_wtime() - _start);
}

vtkRenderer* Scan::MeshConstruct(vtkPoints *point, int saveType)
{
	vtkCellArray *cell = vtkCellArray::New();

	//std::cout << point->GetNumberOfPoints() << "\n";

	for (vtkIdType i = 0; i < point->GetNumberOfPoints() - width; i++)
	{
		double orign[3], right[3], down[3], diga[3];
		//printf("%d %d\n", i,omp_get_thread_num());	
		point->GetPoint(i, orign);
		if (orign[0] == 0)continue;

		point->GetPoint(i + 1, right);
		point->GetPoint(i + width, down);
		point->GetPoint(i + width + 1, diga);

		if ((i + 1) % width == 0)continue;
		if (orign[0] == 0)continue;

		double _dia = getDistane(orign, diga);
		double _down = getDistane(orign, down);

		if (_down < _dia)
		{
			if (right[0] != 0 && down[0] != 0)
			{
				cellInsert(cell, 3, i, i + 1, i + width);
				if (diga[0] != 0)
					cellInsert(cell, 3, i + 1, i + width + 1, i + width);
			}
		}

		else
		{
			if (diga[0] != 0)
			{
				if (right[0] != 0)
					cellInsert(cell, 3, i, i + 1, i + width + 1);
				if (down[0] != 0)
					cellInsert(cell, 3, i, i + width + 1, i + width);
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
	//interactor->Start();//window를 띄우려면 이 부분의 주석을 해제하세요.

	poly->Delete();
	mapper->Delete();
	renderer->Delete();
	actor->Delete();
	win->Delete();
	interactor->Delete();
	cell->Delete();

	return renderer;
}

void  Scan::viewRawStream()
{
	std::ifstream iff("1lefthex.txt");
	std::vector<unsigned short> rawData;

	while (!iff.eof())
	{
		unsigned short value;
		std::string stream;
		iff >> stream;

		int pos = std::string::npos;

		std::stringstream str;

		while ((pos = stream.find("0x", 1)) != std::string::npos)
		{
			std::string hexInString = stream.substr(0, pos);
			stream = stream.substr(pos, stream.size());

			str << hexInString;
			str >> std::hex >> value;
			rawData.push_back(value);
			//	std::cout << value << "\n";
			str.clear();
		}

		pos = stream.find("0x");
		if (pos != std::string::npos)
		{
			str.clear();
			str << stream;
			str >> std::hex >> value;
			rawData.push_back(value);
		}
	}

	double dimensions[3] = { 1920, 1080, 1 };
	const int nComponents = 1;//(unsigned short), scalarType = 4(short)

	vtkImageData*imageData = vtkImageData::New();
	imageData->SetDimensions(dimensions[0], dimensions[1], dimensions[2]);

	imageData->AllocateScalars(VTK_UNSIGNED_SHORT, 1);
	imageData->Modified();

	//	int nScalar = dimensions[2] * dimensions[1] * dimensions[0];
	//	auto scalarPointer = imageData->GetScalarPointer(0, 0, 0);


	for (int i = 0; i<dimensions[0]; i++)
	{
		for (int j = 0; j<dimensions[1]; j++)
		{
			unsigned short* pixel = static_cast<unsigned short*>(imageData->GetScalarPointer(i, j, 0));
			*pixel = rawData[i + j * dimensions[0]];
		}
	}
	vtkImageViewer2 *viewer = vtkImageViewer2::New();
	viewer->SetInputData(imageData);

	vtkRenderer *renderer = vtkRenderer::New();
	vtkRenderWindow *renderWindow = vtkRenderWindow::New();
	renderWindow->AddRenderer(renderer);

	vtkRenderWindowInteractor* interactor = vtkRenderWindowInteractor::New();
	interactor->SetRenderWindow(renderWindow);

	viewer->SetupInteractor(interactor);

	interactor->Initialize();
	viewer->GetRenderer()->ResetCamera();
	viewer->Render();
	interactor->Start();
}
void Scan::MeshConstruction(int mode, int saveType, int ThreadSize)
{
	if (this->points == nullptr)
	{
		std::cout << "Points are not setted";
		return;
	}
	switch (mode)
	{
	case 0:
			MeshConstructWithOMP(this->points, saveType, ThreadSize);
	case 1:
		MeshConstructWithOMPnSIMD(this->points, saveType, ThreadSize);
	default:
		MeshConstruct(this->points, saveType);
	}
}
void Scan::frame2Points(const rs2::frame& frame)
{
	rs2::pointcloud pc;
	rs2::points rsPoints;
	cout << sizeof(frame);
	rsPoints = pc.calculate(frame);
	
	if (points == nullptr)
	{
		points = vtkPoints::New();
	}
	auto v = rsPoints.get_vertices();

	std::cout <<" "<< rsPoints.size() << " number of points exist!!\n";

	/*
	insert Next Point부분이 critical section일것이니까
	4부분으로 나눈다음에 다시 points에 넣는 구조로 만드는게 더 좋을거 같다.
	*/

	for (auto i = 0; i < width*height; i++)
	{

		if (v[i].z > 1 || v[i].z < -1)
		{
			points->InsertNextPoint(0, 0, 0);
		}
		else
		{
			points->InsertNextPoint(v[i]);
			//cout << v << endl;
			//cout << v[i].x << " " << v[i].y << " " << v[i].z << endl;
		}
		

		//else points->InsertNextPoint(0, 0, 0);
	}

	
}