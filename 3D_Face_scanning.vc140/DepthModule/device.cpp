#include "device.h"
using namespace realsense;

cv::Mat frame2Mat(const rs2::frame& f) {
	using namespace cv;
	using namespace rs2;

	auto vf = f.as<video_frame>();
	const int w = vf.get_width();
	const int h = vf.get_height();

	if (f.get_profile().format() == RS2_FORMAT_BGR8)
	{
		return Mat(Size(w, h), CV_8UC3, (void*)f.get_data(), Mat::AUTO_STEP);
	}
	else if (f.get_profile().format() == RS2_FORMAT_RGB8)
	{
		auto r = Mat(Size(w, h), CV_8UC3, (void*)f.get_data(), Mat::AUTO_STEP);
		cv::cvtColor(r, r, CV_BGR2RGB);
		return r;
	}
	else if (f.get_profile().format() == RS2_FORMAT_Z16)
	{
		return Mat(Size(w, h), CV_16UC1, (void*)f.get_data(), Mat::AUTO_STEP);
	}
	else if (f.get_profile().format() == RS2_FORMAT_Y8)
	{
		return Mat(Size(w, h), CV_8UC1, (void*)f.get_data(), Mat::AUTO_STEP);;
	}

	throw std::runtime_error("Frame format is not supported yet!");
}

vtkPoints* frame2Points(const rs2::frame& frame)
{
	rs2::pointcloud pc;
	rs2::points rsPoints;
	//cout << sizeof(frame);
	rsPoints = pc.calculate(frame);
	vtkPoints * vtkPoints = vtkPoints::New();
	auto v = rsPoints.get_vertices();

	std::cout << rsPoints.size() << " number of points exist!!\n";
	for (auto i = 0; i < rsPoints.size(); i++) {
		//if (v[i].z != 0) 
		if (v[i].z>1 || v[i].z<-1)
			vtkPoints->InsertNextPoint(0, 0, 0);
		else
		{
			vtkPoints->InsertNextPoint(v[i]);
			//cout << v << endl;
			//cout << v[i].x << " " << v[i].y << " " << v[i].z << endl;
		}
	}
	return vtkPoints;
}
//
//
//void Realsense::check_init() {
//	if (this->device_count == -1) {
//		cout << "장치 초기화 프로세스 : cams_init()이 이루어지지 않았습니다. 이를 수행합니다.." << endl;
//		this->cams_init();
//	}
//}
//
//void Realsense::cams_init() {
//	rs2::context ctx;
//	this->device_list = ctx.query_devices();
//	if (this->device_list.size() == 0) {
//		cout << "감지된 장치가 없습니다. 장치연결을 확인해주세요." << endl;
//		exit(0);
//	}
//	this->device_count = this->device_list.size();
//	cout << "장치연결을 확인하였습니다. 현재 장치의 갯수는 " << this->device_count << "개 입니다." << endl;
//}
//
//void Realsense::cam_info(int camNum) {
//	this->check_init();
//	if ((camNum < MIN_CAM_NUM - 1) || (camNum>this->device_count - 1)) {
//		string message = "연결된 장치의 Index값을 넘어섰습니다. 현재 장치의 갯수는 ";
//		message += to_string(this->device_count); message += "개 입니다. 입력된 Index 값 : ";
//		message += to_string(camNum);
//		cout << message << endl;
//		exit(0);
//	}
//
//	auto dev = this->device_list[camNum];
//	cout << " Device info: \n";
//	for (auto j = 0; j < RS2_CAMERA_INFO_COUNT; ++j)
//	{
//		auto param = static_cast<rs2_camera_info>(j);
//		if (dev.supports(param))
//			cout << "    " << left << setw(30) << rs2_camera_info_to_string(rs2_camera_info(param))
//			<< ": \t" << dev.get_info(param) << endl;
//	}
//}
//
//void Realsense::startStreaming(int devNum, Realsense::streamType streamType) {
//	this->isInit();
//	rs2::device dev = this->deviceList[devNum];
//	string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
//
//	rs2::config c;
//	c.enable_device(serial_number);
//	
//
//	rs2::sensor depth_sensor = dev.query_sensors()[0];
//	rs2::sensor color_sensor = dev.query_sensors()[1];
//
//	rs2_format format;
//
//	if (streamType == streamType::color)
//		c.enable_stream(RS2_STREAM_COLOR, RS2_FORMAT_RGB8);
//	else if (streamType == streamType::depth) {
//		//c.enable_stream(RS2_STREAM_DEPTH);
//		c.enable_stream(RS2_STREAM_DEPTH, RS2_FORMAT_Z16);
//	}
//	else if (streamType == streamType::infrared_left) {
//		
//	}
//	else if (streamType == streamType::infrared_right) {
//
//	}
//	rs2::pipeline pipe;
//	rs2::pipeline_profile profile = pipe.start(c);
//	this->camMap.emplace(devNum, camUnit{ {}, pipe, profile });
//}
//
//void Realsense::startStreaming(int devNum, rs2_format format, int streamType) {
//	this->isInit();
//	auto dev = this->deviceList[devNum];
//	string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
//
//	rs2::config c;
//	c.enable_device(serial_number);
//
//	if (streamType == color)
//		c.enable_stream(RS2_STREAM_COLOR, format);
//	else if (streamType == depth)
//		//c.enable_stream(RS2_STREAM_DEPTH);
//		c.enable_stream(RS2_STREAM_DEPTH, format);
//
//	rs2::pipeline pipe;
//	rs2::pipeline_profile profile = pipe.start(c);
//	this->pipe_map.emplace(devNum, unit{ {}, pipe, profile });
//}
//
//void Realsense::stopStreaming(int devNum, int streamType) {
//
//	this->isInit();
//	auto dev = this->deviceList[devNum];
//	string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
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
//std::string Realsense::saveImage(rs2::frame &frame, string filepath, int filetype) {
//	throw notImplemented_error();
//	rs2::colorizer color_map;
//
//	if (auto vf = frame.as<rs2::video_frame>())
//	{
//		auto stream = frame.get_profile().stream_type();
//		// Use the colorizer to get an rgb image for the depth stream
//		if (vf.is<rs2::depth_frame>()) vf = color_map(frame);
//
//		// Write images to disk
//		std::stringstream png_file;
//		png_file << "rs-save-to-disk-output-" << vf.get_profile().stream_name() << ".png";
//		//stbi_write_png(png_file.str().c_str(), vf.get_width(), vf.get_height(), vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
//		std::cout << "Saved " << png_file.str() << std::endl;
//	}
//	return "아직 미구현 입니다~";
//}
//
//
//// private function
//void Realsense::restFrame(unit &cam_unit, int num) 
//{
//	for (int i = 0; i < num; i++) {
//		cam_unit.pipe.wait_for_frames();
//	}
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
//
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


/****************************************************************/

Device::Device(string serialNumber, RS_400_MODE) {

	this->context = new rs2::context;
	this->captureStarted = false;
	this->stopProcessFrame = true;
	depthSensor = nullptr;
	colorSensor = nullptr;
	#ifdef _WIN32
		InitializeCriticalSection(&m_mutex);
	#else
		if (0 != pthread_mutex_init(&m_mutex, NULL)) throw
			std::runtime_error("pthread_mutex_init failed");
	#endif
}

camera_info RS400Device::InitializeCamera(string serial_number)
{
	camera_info info{};
	rs2::device_list devices = this->context->query_devices();
	
	for (size_t i = 0; i < devices.size(); i++) {
		if (devices[i].get_info(RS2_CAMERA_INFO_SERIAL_NUMBER) == serial_number) {
			this->device = devices[i];
		}
	}

	if (this->device.is<rs400::advanced_mode>())
	{
		rs400::advanced_mode advanced = this->device.as<rs400::advanced_mode>();
		if (!advanced.is_enabled())
		{
			advanced.toggle_advanced_mode(true);
			//Remove context recreation after libRs fix
			delete this->context;
			this->context = new rs2::context();
			devices = this->context->query_devices();
			for (size_t i = 0; i < devices.size(); i++) {
				if (devices[i].get_info(RS2_CAMERA_INFO_SERIAL_NUMBER) == serial_number) {
					this->device = devices[i];
				}
			}
		}
	}

	auto sensors = devices[0].query_sensors();
	this->depthSensor = sensors[0];
	info.name = this->device.get_info(rs2_camera_info::RS2_CAMERA_INFO_NAME);
	// filter out non RS400 camera
	if (info.name.find("RealSense") == string::npos || info.name.find("4") == string::npos) return info;
	info.pid = this->device.get_info(rs2_camera_info::RS2_CAMERA_INFO_PRODUCT_ID);
	info.serial = this->device.get_info(rs2_camera_info::RS2_CAMERA_INFO_SERIAL_NUMBER);
	info.fw_ver = this->device.get_info(rs2_camera_info::RS2_CAMERA_INFO_FIRMWARE_VERSION);
	std::vector<uint8_t> RawBuffer = { 0x14, 0, 0xab, 0xcd, 0x10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<uint8_t> rcvBuf;
	auto debug = this->device.as<rs2::debug_protocol>();;
	rcvBuf = debug.send_and_receive_raw_data(RawBuffer);
	if ((rcvBuf[SKU_COMPONENT] & 0x03) == 2)
		info.isWide = true;
	if (rcvBuf[RGB_MODE] & 0x01)
	{
		info.isRGB = true;
		if (sensors.size() > 1)
		{
			this->colorSensor = sensors[1];
		}
	}
	return info;
}

bool RS400Device::SetMediaMode(int width, int height, int frameRate, int colorWidth, int colorHeight, bool enableColor)
{
	this->bColorEnabled = enableColor;
	this->depthProfiles.clear();
	this->colorProfile.clear();
	//Enable Y16 format for Left
	rs2::stream_profile infraredProfile;
	if (!GetProfile(infraredProfile, rs2_stream::RS2_STREAM_INFRARED, width, height,
		frameRate, 1)) return false;
	this->depthProfiles.push_back(infraredProfile);
	//Enable Y16 format for Right
	rs2::stream_profile infraredProfile2;
	if (!GetProfile(infraredProfile2, rs2_stream::RS2_STREAM_INFRARED, width, height,
		frameRate, 2)) return false;
	this->depthProfiles.push_back(infraredProfile2);
	if (enableColor)
	{
		rs2::stream_profile profile;
		if (!GetProfile(profile, rs2_stream::RS2_STREAM_COLOR, colorWidth, colorHeight,
			frameRate, 0)) return false;
		this->colorProfile.push_back(profile);
	}
	this->lrImage[0] = std::unique_ptr<uint16_t[]>(new uint16_t[width*(height + 1)]);
	this->lrImage[1] = std::unique_ptr<uint16_t[]>(new uint16_t[width*(height + 1)]);
	return true;
}

bool RS400Device::GetProfile(rs2::stream_profile& profile, rs2_stream stream, int width, int height,int fps, int index)
{
	rs2::sensor sensor;
	rs2_format format;
	if (stream == rs2_stream::RS2_STREAM_INFRARED)
	{
		sensor = this->depthSensor;
		format = rs2_format::RS2_FORMAT_Y16;
	}
	else
	{
		sensor = this->colorSensor;
		format = rs2_format::RS2_FORMAT_YUYV;
	}
	vector<rs2::stream_profile> pfs = sensor.get_stream_profiles();
	for (int i = 0; i < (int)pfs.size(); i++)
	{
		auto video = pfs[i].as<rs2::video_stream_profile>();
		if ((pfs[i].format() == format)
			&& (video.width() == width)
			&& (video.height() == height)
			&& (video.fps() == fps)
			&& (video.stream_index() == index)
			)
		{
			profile = pfs[i];
			return true;
		}
	}
	return false;
}

void RS400Device::EnableAutoExposure(float value)
{
	this->depthSensor.set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, value);
}

void RS400Device::EnableEmitter(float value)
{
	if (this->depthSensor.supports(rs2_option::RS2_OPTION_EMITTER_ENABLED))
	{
		this->depthSensor.set_option(rs2_option::RS2_OPTION_EMITTER_ENABLED, value);
	}
}

void RS400Device::SetAeControl(unsigned int point)
{
	rs400::advanced_mode advanced = this->device.as<rs400::advanced_mode>();
	STAEControl aeControl = { point };
	advanced.set_ae_control(aeControl);
}

//void RS400Device::StartCapture(std::function<void(const void *leftImage, const void *rightImage, const void *depthImage, const uint64_t timeStamp)> callback)
void RS400Device::StartCapture()
{
	//this->callback = callback;
	//if (!this->callback)
//		throw std::runtime_error("SetCallback() must be called before StartCapture()!");
	if (this->depthProfiles.size() == 0)
		throw std::runtime_error("SetMediaMode() must be called before StartCapture()!");
	if (this->captureStarted) return;
	this->depthSensor.open(this->depthProfiles);
	try
	{
		this->depthSensor.start([&](rs2::frame f) {
			auto profile = f.get_profile();
			auto stream_type = profile.stream_type();
			auto video = profile.as < rs2::video_stream_profile > ();
			if (stream_type != rs2_stream::RS2_STREAM_INFRARED)
				return;
			RS_400_STREAM_TYPE rs400StreamType;
			rs400StreamType = (profile.stream_index() == 1) ? RS400_STREAM_INFRARED : RS400_STREAM_INFRARED2;
			MUTEX_LOCK(&m_mutex);
			//시스템 클록에 맞춰서 전송하는 time arrival
			this->timestamp[(int)rs400StreamType] = (uint64_t)f.get_frame_metadata(rs2_frame_metadata_value::RS2_FRAME_METADATA_TIME_OF_ARRIVAL);
			this->ts = this->timestamp[(int)rs400StreamType];
			this->pData[(int)rs400StreamType] = (void *)f.get_data();
			int size = 2 * video.width() * video.height();
			uint16_t *lr = this->lrImage[(int)rs400StreamType].get();
			#ifdef _WIN32
				memcpy_s((void *)lr, size, this->pData[(int)rs400StreamType], size);
			#else
				memcpy((void *)lr, m_pData[(int)rs400StreamType], size);
			#endif
			if (this->timestamp[RS400_STREAM_INFRARED] != this->timestamp[RS400_STREAM_INFRARED2]
				|| this->bColorEnabled)
			{
				MUTEX_UNLOCK(&m_mutex);
				return;
			}
			//process
			uint8_t *left = (uint8_t *)this->lrImage[0].get();
			uint8_t *right = (uint8_t *)this->lrImage[1].get();
			uint8_t *color = nullptr;
			//this->callback(left, right, color, this->ts);
			MUTEX_UNLOCK(&m_mutex);
		});
	}
	catch (...)
	{
		this->depthSensor.close();
		throw;
	}
	if (this->colorProfile.size() > 0)
	{
		this->colorSensor.open(this->colorProfile);
		try
		{
			this->colorSensor.start([&](rs2::frame f) {
				auto profile = f.get_profile();
				auto stream_type = profile.stream_type();
				auto video = profile.as<rs2::video_stream_profile>();
				if (stream_type != rs2_stream::RS2_STREAM_COLOR) return;
				MUTEX_LOCK(&m_mutex);
				this->timestamp[(int)RS400_STREAM_COLOR] =
					(uint64_t)f.get_frame_metadata(rs2_frame_metadata_value::RS2_FRAME_METADATA_TIME_OF_ARRIVAL);
				this->pData[(int)RS400_STREAM_COLOR] = (void *)f.get_data();
				if (this->timestamp[(int)RS400_STREAM_COLOR] < this->ts)
				{
					MUTEX_UNLOCK(&m_mutex);
					return;
				}
				//process
				uint8_t *left = (uint8_t *)this->lrImage[0].get();
				uint8_t *right = (uint8_t *)this->lrImage[1].get();
				uint8_t* color = (uint8_t *)this->pData[(int)RS400_STREAM_COLOR];
				//this->callback(left, right, color, this->ts);
				this->ts = this->timestamp[(int)RS400_STREAM_COLOR];
				MUTEX_UNLOCK(&m_mutex);
			});
		}
		catch (...)
		{
			this->colorSensor.close();
			throw;
		}
	}
	this->leftImage = (uint8_t *)this->lrImage[0].get();
	this->rightImage = (uint8_t*)this->lrImage[1].get();
	this->colorImage = (uint8_t*)this->pData[(int)RS400_STREAM_COLOR];
	this->captureStarted = true;
}

auto RS400Device::GetRawImage(RS_400_STREAM_TYPE straemType, rs2_format format) {
	
}