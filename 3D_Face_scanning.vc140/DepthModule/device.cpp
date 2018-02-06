#include "device.h"

void Realsense::init() {
	rs2::context ctx;
	this->deviceList = ctx.query_devices();
	if (this->deviceList.size() == 0) {
		//throw runtime_error("감지된 장치가 없습니다. 장치연결을 확인해주세요.");
		cout << "감지된 장치가 없습니다. 장치연결을 확인해주세요." << endl;
		exit(0);
	}
	this->deviceNum = this->deviceList.size();
	cout << "장치연결을 확인하였습니다. 현재 장치의 갯수는 " << this->deviceNum << "개 입니다." << endl;
}

void Realsense::info(int devNum) {
	this->isInit();
	if ((devNum < MIN_CAM_NUM - 1) || (devNum>this->deviceNum - 1)) {
		string message = "연결된 장치의 Index값을 넘어섰습니다. 현재 장치의 갯수는 ";
		message += to_string(this->deviceNum); message += "개 입니다. 입력된 index 값 : ";
		message += to_string(devNum);
		//throw runtime_error(message);
		cout << message << endl;
		exit(0);
	}

	auto dev = this->deviceList[devNum];
	cout << " Device info: \n";
	for (auto j = 0; j < RS2_CAMERA_INFO_COUNT; ++j)
	{
		auto param = static_cast<rs2_camera_info>(j);
		if (dev.supports(param))
			cout << "    " << left << setw(30) << rs2_camera_info_to_string(rs2_camera_info(param))
			<< ": \t" << dev.get_info(param) << endl;
	}
	//스트리밍 확인 



}

void Realsense::startStreaming(int devNum, int streamType) {
	this->isInit();
	auto dev = this->deviceList[devNum];
	string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);

	//config를 통해 해당 카메라만 제어함.
	//https://github.com/IntelRealSense/librealsense/blob/master/include/librealsense2/hpp/rs_pipeline.hpp#L118 참조
	rs2::config c;
	c.enable_device(serial_number);

	//stream 의 종류 : RS2_STREAM_ANY, RS2_STREAM_DEPTH, RS2_STREAM_COLOR , RS2_STREAM_GPIO, RS2_STREAM_COUNT 등
	//https://github.com/IntelRealSense/librealsense/blob/c8ee8fa1912b9297df13bfe097d527667fe0afba/include/librealsense2/h/rs_sensor.h#L37
	if (streamType == color)
		c.enable_stream(RS2_STREAM_COLOR);
	else if (streamType == depth)
		//c.enable_stream(RS2_STREAM_DEPTH);
		c.enable_stream(RS2_STREAM_DEPTH, RS2_FORMAT_Z16);


	rs2::pipeline pipe;
	rs2::pipeline_profile profile = pipe.start(c);
	this->pipe_map.emplace(devNum, unit{ {}, pipe, profile });

	//throw notImplemented_error();
}

void Realsense::stopStreaming(int devNum, int streamType) {

	this->isInit();
	auto dev = this->deviceList[devNum];
	string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);

	rs2::config c;
	c.enable_device(serial_number);

	if (streamType == color)
		c.disable_stream(RS2_STREAM_COLOR);
	else if (streamType == depth)
		c.disable_stream(RS2_STREAM_DEPTH);
}

rs2::frame Realsense::capture(int devNum, int streamType, int restNum) {
	unit cam_unit = this->pipe_map[devNum];
	this->restFrame(cam_unit, restNum);
	rs2::frameset data = cam_unit.pipe.wait_for_frames();
	rs2::frame frameData;
	if (streamType == color) {
		frameData = data.get_color_frame();
	}
	else if (streamType == depth) {
		frameData = data.get_depth_frame();
		//frameData = data.first(RS2_STREAM_DEPTH);
	}
	else return NULL;
	return frameData;
}

std::vector<rs2::frame> Realsense::capture(int devNum, int streamType, int frameNum, int restNum) {
	unit cam_unit = this->pipe_map[devNum];
	this->restFrame(cam_unit, restNum);
	rs2::frameset data = cam_unit.pipe.wait_for_frames();
	std::vector<rs2::frame> frameData;
	for (int i = 0; i < frameNum; i++) {
		if (streamType == color) {
			frameData.push_back(data.get_color_frame());
		}
		else if (streamType == depth) {
			frameData.push_back(data.get_depth_frame());
		}
		else return frameData;
		data = cam_unit.pipe.wait_for_frames();
	}
	return frameData;
}

std::string Realsense::saveImage(rs2::frame &frame, string filepath, int filetype) {
	throw notImplemented_error();
	rs2::colorizer color_map;

	if (auto vf = frame.as<rs2::video_frame>())
	{
		auto stream = frame.get_profile().stream_type();
		// Use the colorizer to get an rgb image for the depth stream
		if (vf.is<rs2::depth_frame>()) vf = color_map(frame);

		// Write images to disk
		std::stringstream png_file;
		png_file << "rs-save-to-disk-output-" << vf.get_profile().stream_name() << ".png";
		//stbi_write_png(png_file.str().c_str(), vf.get_width(), vf.get_height(), vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
		std::cout << "Saved " << png_file.str() << std::endl;
	}
	return "아직 미구현 입니다~";
}

vtkPoints* Realsense::frameToVtkPoints(rs2::frame &frame)
{
	rs2::pointcloud pc;
	rs2::points rsPoints;
	//cout << sizeof(frame);
	rsPoints = pc.calculate(frame);
	vtkPoints * vtkPoints = vtkPoints::New();
	auto v = rsPoints.get_vertices();

	std::cout << rsPoints.size() << " number of points exist!!\n";
	for (auto i = 0; i < rsPoints.size(); i++)
	{
		//if (v[i].z != 0) 
		if (v[i].z>1 || v[i].z<-1)
			vtkPoints->InsertNextPoint(0, 0, 0);
		else
		{
			vtkPoints->InsertNextPoint(v[i]);
		}
	}
	return vtkPoints;
}

// private function
void Realsense::restFrame(unit &cam_unit, int num)
{
	for (int i = 0; i < num; i++) {
		cam_unit.pipe.wait_for_frames();
	}
}

bool Realsense::isInit() {
	if (this->deviceNum == NULL) {
		//throw runtime_error("장치 초기화 프로세스 : init()이 이루어지지 않았습니다. 이를 먼저 수행해 주세요.");
		cout << "장치 초기화 프로세스 : init()이 이루어지지 않았습니다. 이를 먼저 수행해 주세요." << endl;
		return false;
	}
	return true;
}


double Realsense::getDistane(double *src, double *tar)
{
	double retv = 0.0;
	//if (tar[0] == 0)return INF;
	//retv += (src[0] - tar[0])*(src[0] - tar[0]);
	//retv += (src[1] - tar[1])*(src[1] - tar[1]);
	retv += (src[2] - tar[2])*(src[2] - tar[2]);
	return retv;
}

void Realsense::cellInsert(vtkCellArray *cell, int number, long long index1, long long index2, long long index3, long long disp)
{
	cell->InsertNextCell(number);
	cell->InsertCellPoint(index1 + disp); cell->InsertCellPoint(index2 + disp); cell->InsertCellPoint(index3 + disp);
	
}

void Realsense::MeshConstructWithOMP(vtkPoints *point, int saveType, int ThreadSize)
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
			threadPoint->SetPoint(i-(omp_get_thread_num()) * width*height / ThreadNum, temp);
			//threadPoint->InsertNextPoint(temp);		
		}
		//printf("%lf\n\n", omp_get_wtime() - _start);

		for (vtkIdType i = 0; i < threadPoint->GetNumberOfPoints(); i++)
		{
			if (i + 1 + width > threadPoint->GetNumberOfPoints())break;
			if ((i + 1) % width == 0)continue;

			double orign[3],right[3],down[3],diga[3];
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
	//interactor->Start();

	boundary->Delete();
	cellBoundary->Delete();
	polyBoundary->Delete();
	actorBoundary->Delete();
	mapperBoundary->Delete();

	interactor->Delete();
	threadRenderer->Delete();
	win->Delete();

	//printf("%lf\n\n", omp_get_wtime() - _start);
}



/*보완 필요*/
void Realsense::MeshConstructWithOMPnSIMD(vtkPoints *point, int saveType, int ThreadSize)
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

	//printf("%lf\n\n", omp_get_wtime() - _start);
}

void Realsense::MeshConstruct(vtkPoints *point, int saveType)
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
}


/*
stramData를 vector을 통해 넘겨주도록 구현할 것
현재는 프로토타입으로 파일 입출력을 통해 raw stream을 출력하는 것으로 구현하였음.
넘기는 방식만 변경하면 됨.
*/
void Realsense::viewRawStream()
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