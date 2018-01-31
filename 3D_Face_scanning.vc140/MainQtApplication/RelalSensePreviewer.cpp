//#include"RelalSensePreviewer.h"
//
//RelalSensePreviewer::RelalSensePreviewer()
//{
//	InitializeVariables();
//}
//
//RelalSensePreviewer::~RelalSensePreviewer()
//{
//	DestroyVariables();
//}
//
//void RelalSensePreviewer::ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize)
//{
//	m_RenWin->SetParentId(uiCtrl);
//	m_RenWin->SetSize(xCtrlSize, yCtrlSize);
//}
//
//int RelalSensePreviewer::CreateModel(std::string meshPath, int extType)
//{
//	if (!m_PolyData)
//		return 0;
//
//	m_MeshIO->ImportMesh(extType, meshPath, m_PolyData);
//	m_PolyData->Modified();
//
//	int n = m_PolyData->GetNumberOfPoints();
//
//	m_Mapper->SetInputData(m_PolyData);
//	m_Mapper->Update();
//
//	m_Actor->SetMapper(m_Mapper);//actor에 mapper을 set함. 
//
//	if (m_IsTexture)
//		m_Actor->SetTexture(m_Texture);
//	m_Actor->GetProperty()->SetInterpolationToGouraud();
//	m_Actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
//	m_Actor->GetProperty()->BackfaceCullingOn();
//
//	m_Actor->Modified();
//
//	m_Renderer->AddActor(m_Actor);
//	m_Renderer->ResetCamera();
//	m_Renderer->Modified();
//
//	return 1;
//}
//
//int RelalSensePreviewer::CreateTexture(std::string imgPath, int extType)
//{
//	m_ImageIO->ImportImage(extType, imgPath, m_ImageData);
//	m_ImageData->Modified();
//
//	m_Texture->SetInputData(m_ImageData);
//	m_Texture->Update();
//
//	m_IsTexture = 1;
//
//	return 1;
//}
//
//int RelalSensePreviewer::ReleaseModel()
//{
//	m_Renderer->RemoveActor(m_Actor);
//
//	if (m_Actor)
//	{
//		m_Actor->Delete();
//		m_Actor = NULL;
//		m_Actor = vtkActor::New();
//	}
//	if (m_Mapper)
//	{
//		m_Mapper->Delete();
//		m_Mapper = NULL;
//		m_Mapper = vtkPolyDataMapper::New();
//	}
//	if (m_PolyData)
//	{
//		m_PolyData->ReleaseData();
//		m_PolyData->Delete();
//		m_PolyData = NULL;
//		m_PolyData = vtkPolyData::New();
//	}
//	if (m_Texture)
//	{
//		m_Texture->Delete();
//		m_Texture = NULL;
//		m_Texture = vtkTexture::New();
//		m_IsTexture = 0;
//	}
//	if (m_ImageData)
//	{
//		m_ImageData->ReleaseData();
//		m_ImageData->Delete();
//		m_ImageData = NULL;
//		m_ImageData = vtkImageData::New();
//	}
//
//
//
//	return 1;
//}
//
//
//int RelalSensePreviewer::InitializeVariables()
//{
//	m_MeshIO = NULL;
//	m_ImageIO = NULL;
//	m_PolyData = NULL;
//	m_ImageData = NULL;
//	m_Mapper = NULL;
//	m_Texture = NULL;
//	m_Actor = NULL;
//	m_Renderer = NULL;
//	m_RenWin = NULL;
//
//	m_MeshIO = new MeshIO;
//	m_ImageIO = new ImageIO;
//
//	m_PolyData = vtkPolyData::New();
//	m_ImageData = vtkImageData::New();
//	m_Mapper = vtkPolyDataMapper::New();
//	m_Texture = vtkTexture::New();
//	m_IsTexture = 0;
//	m_Actor = vtkActor::New();
//	m_Renderer = vtkRenderer::New();
//	m_RenWin = vtkRenderWindow::New();
//	return 1;
//}
//
//int RelalSensePreviewer::Create2DScene()
//{
//	m_Renderer->GetActiveCamera()->ParallelProjectionOff();
//	m_RenWin->AddRenderer(m_Renderer);
//	m_RenWin->Modified();
//	return 1;
//}
//
//int RelalSensePreviewer::DestroyVariables()
//{
//	if (m_MeshIO)
//	{
//		delete m_MeshIO;
//		m_MeshIO = NULL;
//	}
//	if (m_ImageIO)
//	{
//		delete m_ImageIO;
//		m_ImageIO = NULL;
//	}
//	if (m_PolyData)
//	{
//		m_PolyData->ReleaseData();
//		m_PolyData->Delete();
//		m_PolyData = NULL;
//	}
//	if (m_ImageData)
//	{
//		m_ImageData->ReleaseData();
//		m_ImageData->Delete();
//		m_ImageData = NULL;
//	}
//	if (m_Mapper)
//	{
//		m_Mapper->Delete();
//		m_Mapper = NULL;
//	}
//	if (m_Texture)
//	{
//		m_Texture->Delete();
//		m_Texture = NULL;
//	}
//	if (m_Actor)
//	{
//		m_Actor->Delete();
//		m_Actor = NULL;
//	}
//	if (m_Renderer)
//	{
//		m_Renderer->Delete();
//		m_Renderer = NULL;
//	}
//	if (m_RenWin)
//	{
//		m_RenWin->Delete();
//		m_RenWin = NULL;
//	}
//	return 1;
//}
//
//int RelalSensePreviewer::CaptureSave(std::string imagePath, int extType, int sizeRatio)
//{
//	m_ImageIO->CaptureSaveImageFile(m_RenWin, extType, sizeRatio, imagePath);
//	m_RenWin->Render();
//
//	return 1;
//}
//
//int RelalSensePreviewer::MeshSave(std::string meshPath, int extType)
//{
//	m_MeshIO->ExportMesh(extType, meshPath, m_PolyData);
//
//	return 1;
//}
//
//int RelalSensePreviewer::TextureMeshSave(std::string meshPath, int meshExtType, std::string imagePath, int imgExtType)
//{
//	m_MeshIO->ExportOBJFile(m_RenWin, meshPath);
//	m_ImageIO->ExportImageFile(imgExtType, m_ImageData, imagePath);
//
//	return 1;
//}
//
//int RelalSensePreviewer::NonTextureMeshSave(std::string meshPath, int meshExtType)
//{
//	m_MeshIO->ExportOBJFile(m_RenWin, meshPath);
//
//	return 1;
//}
//
//void RelalSensePreviewer::Rendering()
//{
//	m_RenWin->Render();
//}
//
//
//
//
//
//
//
//
//
//
//void Realsense::init() {
//	rs2::context ctx;
//	this->deviceList = ctx.query_devices();
//	if (this->deviceList.size() == 0) {
//		//throw runtime_error("감지된 장치가 없습니다. 장치연결을 확인해주세요.");
//		cout << "감지된 장치가 없습니다. 장치연결을 확인해주세요." << endl;
//		exit(0);
//	}
//	this->deviceNum = this->deviceList.size();
//	cout << "장치연결을 확인하였습니다. 현재 장치의 갯수는 " << this->deviceNum << "개 입니다." << endl;
//}
//
//void Realsense::info(int devNum) {
//	this->isInit();
//	if ((devNum < MIN_CAM_NUM - 1) || (devNum>this->deviceNum - 1)) {
//		std::string message = "연결된 장치의 Index값을 넘어섰습니다. 현재 장치의 갯수는 ";
//		message += std::to_string(this->deviceNum); message += "개 입니다. 입력된 index 값 : ";
//		message += std::to_string(devNum);
//		//throw runtime_error(message);
//		cout << message << endl;
//		exit(0);
//	}
//
//	auto dev = this->deviceList[devNum];
//	cout << " Device info: \n";
//	for (auto j = 0; j < RS2_CAMERA_INFO_COUNT; ++j)
//	{
//		auto param = static_cast<rs2_camera_info>(j);
//		if (dev.supports(param))
//			cout << "    " << std::left << setw(30) << rs2_camera_info_to_string(rs2_camera_info(param))
//			<< ": \t" << dev.get_info(param) << endl;
//	}
//	//스트리밍 확인 
//
//
//
//}
//
//void Realsense::startStreaming(int devNum, int streamType) {
//	this->isInit();
//	auto dev = this->deviceList[devNum];
//	std::string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
//
//	//config를 통해 해당 카메라만 제어함.
//	//https://github.com/IntelRealSense/librealsense/blob/master/include/librealsense2/hpp/rs_pipeline.hpp#L118 참조
//	rs2::config c;
//	c.enable_device(serial_number);
//
//	//stream 의 종류 : RS2_STREAM_ANY, RS2_STREAM_DEPTH, RS2_STREAM_COLOR , RS2_STREAM_GPIO, RS2_STREAM_COUNT 등
//	//https://github.com/IntelRealSense/librealsense/blob/c8ee8fa1912b9297df13bfe097d527667fe0afba/include/librealsense2/h/rs_sensor.h#L37
//	if (streamType == color)
//		c.enable_stream(RS2_STREAM_COLOR);
//	else if (streamType == depth)
//		//c.enable_stream(RS2_STREAM_DEPTH);
//		c.enable_stream(RS2_STREAM_DEPTH, RS2_FORMAT_Z16);
//
//
//	rs2::pipeline pipe;
//	rs2::pipeline_profile profile = pipe.start(c);
//	this->pipe_map.emplace(devNum, unit{ {}, pipe, profile });
//
//	//throw notImplemented_error();
//}
//
//void Realsense::stopStreaming(int devNum, int streamType) {
//
//	this->isInit();
//	auto dev = this->deviceList[devNum];
//	std::string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
//
//	rs2::config c;
//	c.enable_device(serial_number);
//
//	if (streamType == color)
//		c.disable_stream(RS2_STREAM_COLOR);
//	else if (streamType == depth)
//		c.disable_stream(RS2_STREAM_DEPTH);
//}
//
//rs2::frame Realsense::capture(int devNum, int streamType, int restNum) {
//	unit cam_unit = this->pipe_map[devNum];
//	this->restFrame(cam_unit, restNum);
//	rs2::frameset data = cam_unit.pipe.wait_for_frames();
//	rs2::frame frameData;
//	if (streamType == color) {
//		frameData = data.get_color_frame();
//	}
//	else if (streamType == depth) {
//		frameData = data.get_depth_frame();
//		//frameData = data.first(RS2_STREAM_DEPTH);
//	}
//	else return NULL;
//	return frameData;
//}
//
//std::vector<rs2::frame> Realsense::capture(int devNum, int streamType, int frameNum, int restNum) {
//	unit cam_unit = this->pipe_map[devNum];
//	this->restFrame(cam_unit, restNum);
//	rs2::frameset data = cam_unit.pipe.wait_for_frames();
//	std::vector<rs2::frame> frameData;
//	for (int i = 0; i < frameNum; i++) {
//		if (streamType == color) {
//			frameData.push_back(data.get_color_frame());
//		}
//		else if (streamType == depth) {
//			frameData.push_back(data.get_depth_frame());
//		}
//		else return frameData;
//		data = cam_unit.pipe.wait_for_frames();
//	}
//	return frameData;
//}
//
//std::string Realsense::saveImage(rs2::frame &frame, std::string filepath, int filetype) 
//{
//	return "Not Yet";
//}
//
//vtkPoints* Realsense::frameToVtkPoints(rs2::frame &frame)
//{
//	rs2::pointcloud pc;
//	rs2::points rsPoints;
//	//cout << sizeof(frame);
//	rsPoints = pc.calculate(frame);
//	vtkPoints * vtkPoints = vtkPoints::New();
//	auto v = rsPoints.get_vertices();
//
//	std::cout << rsPoints.size() << " number of points exist!!\n";
//	for (auto i = 0; i < rsPoints.size(); i++) {
//		//if (v[i].z != 0) 
//		if (v[i].z>1 || v[i].z<-1)
//			vtkPoints->InsertNextPoint(0, 0, 0);
//		else
//		{
//			vtkPoints->InsertNextPoint(v[i]);
//			//cout << v << endl;
//			//cout << v[i].x << " " << v[i].y << " " << v[i].z << endl;
//		}
//	}
//	return vtkPoints;
//}
//
//// private function
//void Realsense::restFrame(unit &cam_unit, int num)
//{
//	for (int i = 0; i < num; i++) {
//		cam_unit.pipe.wait_for_frames();
//	}
//}
//
//bool Realsense::isInit() {
//	if (this->deviceNum == NULL) {
//		//throw runtime_error("장치 초기화 프로세스 : init()이 이루어지지 않았습니다. 이를 먼저 수행해 주세요.");
//		cout << "장치 초기화 프로세스 : init()이 이루어지지 않았습니다. 이를 먼저 수행해 주세요." << endl;
//		return false;
//	}
//	return true;
//}
//
//
//double Realsense::getDistane(double *src, double *tar)
//{
//	double retv = 0.0;
//	if (tar[0] == 0)return INF;
//	//retv += (src[0] - tar[0])*(src[0] - tar[0]);
//	//retv += (src[1] - tar[1])*(src[1] - tar[1]);
//	retv += (src[2] - tar[2])*(src[2] - tar[2]);
//	return retv;
//}
//void Realsense::MeshConstruct(vtkPoints *point, int saveType)
//{
//	vtkCellArray *cell = vtkCellArray::New();
//	double *ptr;
//
//	std::cout << point->GetNumberOfPoints() << "\n";
//
//	for (vtkIdType i = 0; i < point->GetNumberOfPoints() - width; i++)
//	{
//		ptr = point->GetPoint(i);
//		double orign[3] = { ptr[0],ptr[1],ptr[2] };
//
//		ptr = point->GetPoint(i + 1);
//		double right[3] = { ptr[0],ptr[1],ptr[2] };
//
//		ptr = point->GetPoint(i + width);
//		double down[3] = { ptr[0],ptr[1],ptr[2] };
//
//		ptr = point->GetPoint(i + width + 1);
//		double diga[3] = { ptr[0],ptr[1],ptr[2] };
//
//		if ((i + 1) % width == 0)continue;
//		if (orign[0] == 0)continue;
//
//		double _dia = getDistane(orign, diga);
//		double _down = getDistane(orign, down);
//
//		if (_down < _dia)
//		{
//			if (right[0] != 0 && down[0] != 0)
//			{
//				cell->InsertNextCell(3);
//				cell->InsertCellPoint(i); cell->InsertCellPoint(i + 1); cell->InsertCellPoint(i + width);
//			}
//
//			if (right[0] != 0 && diga[0] != 0)
//			{
//				cell->InsertNextCell(3);
//				cell->InsertCellPoint(i + 1); cell->InsertCellPoint(i + width + 1); cell->InsertCellPoint(i + width);
//			}
//		}
//
//		else
//		{
//			if (right[0] != 0 && diga[0] != 0)
//			{
//				cell->InsertNextCell(3);
//				cell->InsertCellPoint(i); cell->InsertCellPoint(i + 1); cell->InsertCellPoint(i + width + 1);
//			}
//
//			if (diga[0] != 0 && down[0] != 0)
//			{
//				cell->InsertNextCell(3);
//				cell->InsertCellPoint(i); cell->InsertCellPoint(i + width + 1); cell->InsertCellPoint(i + width);
//			}
//		}
//	}
//
//
//	vtkPolyData *poly = vtkPolyData::New();
//	poly->SetPoints(point);
//	poly->SetPolys(cell);
//
//	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
//	mapper->SetInputData(poly);
//
//	vtkRenderer *renderer = vtkRenderer::New();
//	renderer->GetActiveCamera()->ParallelProjectionOff();
//
//	vtkActor *actor = vtkActor::New();
//	actor->SetMapper(mapper);
//	renderer->AddActor(actor);
//
//	vtkRenderWindow *win = vtkRenderWindow::New();
//	vtkRenderWindowInteractor * interactor = vtkRenderWindowInteractor::New();
//	interactor->SetRotation(0.1);
//	win->AddRenderer(renderer);
//
//
//	if (saveType == 1)
//	{
//		vtkSTLWriter* stlWriter = vtkSTLWriter::New();
//		stlWriter->SetFileName("my.stl");
//
//		stlWriter->SetInputData(poly);
//		stlWriter->Write();
//		stlWriter->Delete();
//	}
//
//	else if (saveType == 2) {
//		vtkOBJExporter *obj = vtkOBJExporter::New();
//		obj->SetInput(win);
//		obj->SetFilePrefix("mine");
//		obj->Write();
//		obj->Delete();
//	}
//
//	interactor->SetRenderWindow(win);
//	interactor->Start();
//
//
//
//	poly->Delete();
//	mapper->Delete();
//	renderer->Delete();
//	actor->Delete();
//	win->Delete();
//	interactor->Delete();
//	cell->Delete();
//}
//
