#include"Scan.h"
#include"vtkImageMapper.h"
#include"vtkActor2D.h"


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
void Scan::frames2PointsCutOutlier()
{
	if (points == nullptr)
	{
		points = vtkPoints::New();
	}

	rs2::pointcloud pc;
	rs2::points rsPoints;
	std::vector<const rs2::vertex*> ver;

	for (int i = 0; i < frames.size(); i++)
	{
		rsPoints = pc.calculate(frames[i]);
		ver.push_back(rsPoints.get_vertices());
	}

	for (int j = 0; j < 1280 * 720; j++)
	{

		std::vector<double> X, Y, Z;
		for (int i = 0; i < frames.size(); i++)
		{
			if (ver[i][j].z != 0 && ver[i][j].z < 1 && ver[i][j].z > -1)
			{
				X.push_back(ver[i][j].x);
				Y.push_back(ver[i][j].y);
				Z.push_back(ver[i][j].z);
			}
		}

		double _X, _Y, _Z;
		_X = _Y = _Z = 0;

		std::sort(X.begin(), X.end());
		std::sort(Y.begin(), Y.end());
		std::sort(Z.begin(), Z.end());

		int cnt = 0;
		for (int i = X.size()*0.3; i < X.size()*0.7; i++)
		{
			_X += X[i];
			_Y += Y[i];
			_Z += Z[i];
			cnt++;
		}
		if (cnt <= 1)
			points->InsertNextPoint(0, 0, 0);
		else
		{
			_X /= cnt; _Y /= cnt; _Z /= cnt;
			points->InsertNextPoint(_X, _Y, _Z);
		}

		X.clear(); Y.clear(); Z.clear();

		//std::cout << j << " ";
	}

	ver.clear();
	frames.clear();

}
void Scan::frames2Points()
{
	if (points == nullptr)
	{
		points = vtkPoints::New();
	}

	rs2::pointcloud pc;
	rs2::points rsPoints;
	std::vector<const rs2::vertex*> ver;

	for (int i = 0; i < frames.size(); i++)
	{
		rsPoints = pc.calculate(frames[i]);
		ver.push_back(rsPoints.get_vertices());
	}

	for (int j = 0; j < 1280 * 720; j++)
	{
		int cnt = 0;
		double X, Y, Z;
		X = Y = Z = 0;

		for (int i = 0; i < frames.size(); i++)
		{
			if (ver[i][j].z != 0 && ver[i][j].z < 1 && ver[i][j].z > -1)
			{
				X += ver[i][j].x;
				Y += ver[i][j].y;
				Z += ver[i][j].z;
				cnt++;
			}
		}

		if (cnt == 0)
			points->InsertNextPoint(0, 0, 0);
		else
		{
			X /= cnt; Y /= cnt; Z /= cnt;
			points->InsertNextPoint(X, Y, Z);
		}
	}

	ver.clear();
	frames.clear();

}
void  Scan::MeshConstructWithOMP(vtkPoints *point, int saveType, int ThreadSize)
{
	std::cout <<" "<< point->GetNumberOfPoints() << "\n";


	#pragma omp parallel num_threads(ThreadSize)		 
	{
		vtkPoints *threadPoint = vtkPoints::New();
		vtkCellArray *threadCell = vtkCellArray::New();
	


		threadPoint->SetNumberOfPoints(width*height / ThreadSize);

		#pragma omp for
		for (int i = 0; i < width*height; i++)
		{
			double temp[3];
			point->GetPoint(i, temp);
			threadPoint->SetPoint(i - (omp_get_thread_num()) * width*height / ThreadSize, temp);	
		}

		for (vtkIdType i = 0; i < threadPoint->GetNumberOfPoints(); i++)
		{
			if (i + 1 + width > threadPoint->GetNumberOfPoints())continue;
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

		Viewer->m_PolyData[omp_get_thread_num()]->SetPoints(threadPoint);
		Viewer->m_PolyData[omp_get_thread_num()]->SetPolys(threadCell);

		Viewer->m_Mapper[omp_get_thread_num()]->SetInputData(Viewer->m_PolyData[omp_get_thread_num()]);
		Viewer->m_Actor[omp_get_thread_num()]->SetMapper(Viewer->m_Mapper[omp_get_thread_num()]);


		
		threadPoint->Delete();
		threadCell->Delete();
	}

	vtkPoints *boundary = vtkPoints::New();
	vtkCellArray *cellBoundary = vtkCellArray::New();

	for (int j = 1; j <= ThreadSize - 1; j++)
	{
		for (int i = j*width * height / ThreadSize - width; i <j*width * height / ThreadSize + width * 2 - width; i++)
		{
			double temp[3];
			point->GetPoint(i, temp);
			boundary->InsertNextPoint(temp);
		}
	}


	for (int j = 0; j < ThreadSize - 1; j++)
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

	Viewer->m_PolyData[4]->SetPoints(boundary);
	polyBoundary->SetPolys(cellBoundary);
	mapperBoundary->SetInputData(polyBoundary);
	actorBoundary->SetMapper(mapperBoundary);

	
	Viewer->m_PolyData[ThreadSize] = polyBoundary;
	Viewer->m_Mapper[ThreadSize] = mapperBoundary;
	Viewer->m_Actor[ThreadSize] = actorBoundary;

	//act[4] = actorBoundary;
	/*vtkOBJExporter *objWriter = vtkOBJExporter::New();
	objWriter->SetFilePrefix("my");
	objWriter->SetInput(win);
	objWriter->Write();*/

	boundary->Delete();
	cellBoundary->Delete();
	
	Viewer->GetRenderWindow()->Modified();
	Viewer->GetRenderWindow()->Render();

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


	for (vtkIdType i = 0; i < point->GetNumberOfPoints() - width; i++)
	{
		double orign[3], right[3], down[3], diga[3];
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


	Viewer->GetPolyDataAt(0)->SetPoints(point);
	Viewer->GetPolyDataAt(0)->SetPolys(cell);
	Viewer->GetMapperAt(0)->SetInputData(Viewer->GetPolyDataAt(0));

	Viewer->GetActorAt(0)->SetMapper(Viewer->GetMapperAt(0));
	
	Viewer->GetRenderer()->AddActor(Viewer->GetActorAt(0));

	Viewer->GetRenderer()->GetActiveCamera()->ParallelProjectionOff();


	//std::cout << Viewer->GetPolyDataAt(0)->GetNumberOfPolys() << "@!#!@#!@#";
	if (saveType == 1)
	{
		vtkSTLWriter* stlWriter = vtkSTLWriter::New();
		stlWriter->SetFileName("my.stl");
		stlWriter->SetInputData(Viewer->GetPolyDataAt(0));
		stlWriter->Write();
		stlWriter->Delete();
	}

	else if (saveType == 2) {
		vtkOBJExporter *obj = vtkOBJExporter::New();
		obj->SetInput(Viewer->GetRenderWindow());
		obj->SetFilePrefix("mine");
		obj->Write();
		obj->Delete();
	}

	cell->Delete();

	Viewer->GetRenderWindow()->Modified();
	Viewer->GetRenderWindow()->Render();
	return Viewer->GetRenderer();
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
		break;
	case 1:
		MeshConstructWithOMPnSIMD(this->points, saveType, ThreadSize);
		break;
	default:
		MeshConstruct(this->points, saveType);
		break;
	}
}

void Scan::ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize)
{

	Viewer->GetRenderWindow()->SetParentId(uiCtrl);
	Viewer->GetRenderWindow()->SetSize(xCtrlSize, yCtrlSize);
}

/*
이 부분 omp적용하는거 고려해볼 것.
*/
void Scan::frame2Points(const rs2::frame& frame)
{
	rs2::pointcloud pc;
	rs2::points rsPoints;
	rsPoints = pc.calculate(frame);

	//insert Next Point부분이 critical section일것이니까
	//4부분으로 나눈다음에 다시 points에 넣는 구조로 만드는게 더 좋을거 같다.
	//*/

	if (points == nullptr)
		points = vtkPoints::New();
	
	auto v = rsPoints.get_vertices();

	////std::ofstream str("test.txt");
	for (auto i = 0; i < width*height; i++)
	{
		if (v[i].z > 1 || v[i].z < -1)
			points->InsertNextPoint(0, 0, 0);
		
		else
			points->InsertNextPoint(v[i]);
		
	}

}