#include "device.h"

using namespace realsense;

string realsense::getFirstSerial() {
	return realsense::getSerial(0);
}

string realsense::getSerial(int devIdx) {
	if (devIdx < 0) return "None";
	rs2::context ctx;
	if (ctx.query_devices().size() < devIdx) return "None";
	rs2::device dev = ctx.query_devices()[devIdx];
	string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
	return serial_number;
}

void realsense::ReorderY16(const uint16_t* image, int width, int height) {
	auto range = width*height/2;
	for (size_t i = 0; i < range; i++) {
		uint16_t pix1 = image[i];
		uint16_t pix2 = image[range-i];
		uint16_t tmp = pix1;
		pix2 = pix1;
		pix2 = tmp;
	}
}



void realsense::ConvertYUY2ToRGBA(const uint8_t* image, int width, int height, uint8_t* output)
{
	int n = width*height;
	auto src = image;
	auto dst = output;
	for (; n; n -= 16, src += 32)
	{
		int16_t y[16] = {
			src[0], src[2], src[4], src[6],
			src[8], src[10], src[12], src[14],
			src[16], src[18], src[20], src[22],
			src[24], src[26], src[28], src[30],
		}, u[16] = {
			src[1], src[1], src[5], src[5],
			src[9], src[9], src[13], src[13],
			src[17], src[17], src[21], src[21],
			src[25], src[25], src[29], src[29],
		}, v[16] = {
			src[3], src[3], src[7], src[7],
			src[11], src[11], src[15], src[15],
			src[19], src[19], src[23], src[23],
			src[27], src[27], src[31], src[31],
		};
		uint8_t r[16], g[16], b[16];
			for (int i = 0; i < 16; i++)
			{
				int32_t c = y[i] - 16;
				int32_t d = u[i] - 128;
				int32_t e = v[i] - 128;
				int32_t t;
#define clamp(x) ((t=(x)) > 255 ? 255 : t < 0 ? 0 : t)
				r[i] = clamp((298 * c + 409 * e + 128) >> 8);
				g[i] = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
				b[i] = clamp((298 * c + 516 * d + 128) >> 8);
#undef clamp
			}
		uint8_t out[16 * 4] = {
			r[0], g[0], b[0], 255, r[1], g[1], b[1], 255,
			r[2], g[2], b[2], 255, r[3], g[3], b[3], 255,
			r[4], g[4], b[4], 255, r[5], g[5], b[5], 255,
			r[6], g[6], b[6], 255, r[7], g[7], b[7], 255,
			r[8], g[8], b[8], 255, r[9], g[9], b[9], 255,
			r[10], g[10], b[10], 255, r[11], g[11], b[11], 255,
			r[12], g[12], b[12], 255, r[13], g[13], b[13], 255,
			r[14], g[14], b[14], 255, r[15], g[15], b[15], 255,
		};
#ifdef _WIN32
		memcpy_s((void *)dst, sizeof out, out, sizeof out);
#else
		memcpy((void *)dst, out, sizeof out);
#endif
		dst += sizeof out;
	}
}

void realsense::ConvertYUY2ToLuminance8(const uint8_t* image, int width, int height, uint8_t* output)
{
	auto out = output;
	auto in = image;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j += 2)
		{
			*out++ = in[0];
			*out++ = in[2];
			in += 4;
		}
	}
}

void realsense::ConvertLuminance16ToLuminance8(const uint16_t* image, int width, int height, uint8_t* output)
{
	auto ptr = output;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			uint8_t val = (uint8_t)(image[i * width + j] >> 8);
			*ptr++ = val;
		}
	}
}



Device::Device(string serialNumber) {
	#ifdef _WIN32
	InitializeCriticalSection(&m_mutex);
	#else
	if (0 != pthread_mutex_init(&m_mutex, NULL)) throw
		std::runtime_error("pthread_mutex_init failed");
	#endif
	m_stereoSensor = nullptr;
	m_colorSensor = nullptr;
	m_colorStreamCheck = false;
	m_depthStreamCheck = false;
	m_irStreamCheck = false;
	m_ir1StreamCheck = false;
	m_ir2StreamCheck = false;

	//set target device object
	m_context = new context;
	device_list devices = m_context->query_devices();
	for (size_t i = 0; i < devices.size(); i++) {
		if (devices[i].get_info(RS2_CAMERA_INFO_SERIAL_NUMBER) == serialNumber) {
			m_device = devices[i];
		}
	}
	
	//check is advanced?
	/*if (m_device.is<rs400::advanced_mode>()){
		rs400::advanced_mode advanced = m_device.as<rs400::advanced_mode>();
		if (advanced.is_enabled()) {
			advanced.toggle_advanced_mode(true);
			delete m_context;
			m_context = new context;
			devices = m_context->query_devices();
			for (size_t i = 0; i < devices.size(); i++) {
				if (devices[i].get_info(RS2_CAMERA_INFO_SERIAL_NUMBER) == serialNumber) {
					m_device = devices[i];
				}
			}
		}
	}*/

	//sensor catch
	m_sensors = m_device.query_sensors();
	m_stereoSensor = m_sensors[0];
	m_colorSensor = m_sensors[1];


	//stream initialize per sensor
	vector<rs2::stream_profile> stream_profiles = m_stereoSensor.get_stream_profiles();
	for (auto&& sp : stream_profiles)
	{
		auto streamType = m_stream2Enum(sp.stream_name()); //Infrared 1, Infrared 2, Infrared, Depth, Color
		
		if (sp.is<rs2::video_stream_profile>()) //"Is" will test if the type tested is of the type given
		{
			// "As" will try to convert the instance to the given type
			rs2::video_stream_profile video_stream_profile = sp.as<rs2::video_stream_profile>();

			string t_resolution = to_string(video_stream_profile.width()) + "x" + to_string(video_stream_profile.height());
			auto resolution = m_resolution2Enum(t_resolution);
			auto format = m_format2Enum(video_stream_profile.format());
			auto fps = m_fps2Enum(video_stream_profile.fps());
			auto code = resolution * 100 + format * 10 + fps;
			m_streoUniqueStreams[streamType][code] = pair<int, rs2::stream_profile>(sp.unique_id(), sp);
		}
		
		//m_streoUniqueStreams[std::make_pair(sp.stream_type(), sp.stream_index())]++;
	}

	stream_profiles = m_colorSensor.get_stream_profiles();
	for (auto&& sp : stream_profiles)
	{
		auto streamType = m_stream2Enum(sp.stream_name()); //Infrared 1, Infrared 2, Infrared, Depth, Color

		if (sp.is<rs2::video_stream_profile>()) //"Is" will test if the type tested is of the type given
		{
			// "As" will try to convert the instance to the given type
			rs2::video_stream_profile video_stream_profile = sp.as<rs2::video_stream_profile>();

			string t_resolution = to_string(video_stream_profile.width()) + "x" + to_string(video_stream_profile.height());
			auto resolution = m_resolution2Enum(t_resolution);
			auto format = m_format2Enum(video_stream_profile.format());
			auto fps = m_fps2Enum(video_stream_profile.fps());
			auto code = resolution * 100 + format * 10 + fps;
			m_colorUniqueStreams[streamType][code] = pair<int, rs2::stream_profile>(sp.unique_id(), sp);
		}
		//m_colorUniqueStreams[std::make_pair(sp.stream_type(), sp.stream_index())]++;
	}


	//device info record
	info.name = m_device.get_info(rs2_camera_info::RS2_CAMERA_INFO_NAME);
	info.pid = m_device.get_info(rs2_camera_info::RS2_CAMERA_INFO_PRODUCT_ID);
	info.serial = m_device.get_info(rs2_camera_info::RS2_CAMERA_INFO_SERIAL_NUMBER);
	info.fw_ver = m_device.get_info(rs2_camera_info::RS2_CAMERA_INFO_FIRMWARE_VERSION);

}

void Device::printDeviceInfo() {
	cout << " Device info: \n";
	for (auto j = 0; j < RS2_CAMERA_INFO_COUNT; ++j)
	{
		auto param = static_cast<rs2_camera_info>(j);
		if (m_device.supports(param))
			cout << "    " << left << setw(30) << rs2_camera_info_to_string(rs2_camera_info(param))
			<< ": \t" << m_device.get_info(param) << endl;
	}
	
	auto sensors = m_sensors;
	cout << "\nSensor info: \n";
	int index = 0;
	for (rs2::sensor sensor : sensors)
	{
		if (sensor.supports(RS2_CAMERA_INFO_NAME)) {
			cout << "    " << index++ << " : " << sensor.get_info(RS2_CAMERA_INFO_NAME) << endl;
		}

	}
}

void Device::printSensorInfo() {
	cout << "\n\nSensor detail Info" << endl;
	auto sensors = m_sensors;
	for (rs2::sensor sensor : sensors) {
		cout << "\n [" << sensor.get_info(RS2_CAMERA_INFO_NAME) << "]" << endl;
		for (int i = 0; i < static_cast<int>(RS2_OPTION_COUNT); i++)
		{
			rs2_option option_type = static_cast<rs2_option>(i);
			//SDK enum types can be streamed to get a string that represents them
			cout << "    " << i << " : " << option_type;

			// To control an option, use the following api:

			// First, verify that the sensor actually supports this option
			if (sensor.supports(option_type))
			{
				std::cout << std::endl;

				// Get a human readable description of the option
				const char* description = sensor.get_option_description(option_type);
				std::cout << "       Description   : " << description << std::endl;

				// Get the current value of the option
				float current_value = sensor.get_option(option_type);
				std::cout << "       Current Value : " << current_value << std::endl;

				//To change the value of an option, please follow the change_sensor_option() function
			}
			else
			{
				std::cout << " is not supported" << std::endl;
			}
		}
	}
	
}

//help function...
//하나의 센서에 여러 스트림이 접근할때, 임계영역문제?
void Device::selectSensorAndStreamProps() {

	
	/*size_t command_sensor;
	size_t command_stream;
	size_t command_code;
	cout << "\n카메라 센서와, 스트림을 입력하세요" << endl;
	cout << "1. 카메라 센서 \n\tSTEREO_MODULE(0)\n\tRGB_CAMERA(1)\n\t >"; cin >> command_sensor;
	cout << "2. 스트림 타입 : \n\tRS400_STREAM_DEPTH(0)\n\tRS400_STREAM_INFRARED(1)\n\tRS400_STREAM_INFRARED1(2)\n\tRS400_STREAM_INFRARED2(3)\n\tRS400_STREAM_COLOR(4)\n\t>>"; cin >> command_stream;
	cout << "3. 스트림 코드를 입력하세요 >> "; cin >> command_code;

	m_selectedSensor = static_cast<RS_400_SENSOR>(command_sensor);
		
	cout << "스트리밍을 시작합니다..";
	try {
		if (m_selectedSensor == RS_400_SENSOR::STEREO_MODULE) {
			startStreaming(m_streoUniqueStreams[command_stream][command_code].second);
			
		}
		else if (m_selectedSensor == RS_400_SENSOR::RGB_CAMERA) {
			startStreaming(m_colorUniqueStreams[command_stream][command_code].second);
		}
	}
	catch(...) {
		cout << "잘못된 접근입니다. 코드표를 참조해주세요" << endl;
	}*/
	

	m_selectedSensor = RS_400_SENSOR::STEREO_MODULE;

	startStreaming(m_streoUniqueStreams[RS400_STREAM_INFRARED1][12].second);
	startStreaming(m_streoUniqueStreams[RS400_STREAM_INFRARED2][12].second);
	
	m_selectedSensor = RS_400_SENSOR::RGB_CAMERA;
	startStreaming(m_colorUniqueStreams[RS400_STREAM_COLOR][463].second);

	//Depth #0 (640x480 / Z16 / 30Hz)
	//startStreaming(m_streoUniqueStreams[RS400_STREAM_DEPTH][493].second);

}

void Device::startStreaming(rs2::stream_profile& stream_profile) {
	RS_400_STREAM_TYPE streamType = m_stream2Enum(stream_profile.stream_name());
	if ((streamType > 4)||(streamType<0)) {
		throw std::invalid_argument("Invalid Stream profile");
	}
	
	if ((m_selectedSensor == STEREO_MODULE)&&(m_depthStreamCheck || m_irStreamCheck || m_ir1StreamCheck || m_ir2StreamCheck)) {
		//Multiple Streaming
		vector <rs2::stream_profile> profile_set;
		m_getProfile(profile_set);
		profile_set.push_back(stream_profile);
		stopStreaming(RS_400_SENSOR::STEREO_MODULE);
		startStreaming(profile_set);
	}
	else {//Single Stream
		switch (streamType) {
		case RS400_STREAM_DEPTH: {
			m_stereoSensor.open(stream_profile);
			m_stereoSensor.start([&](rs2::frame f) {m_depthFrameQueue.enqueue(f); });
			m_depthStreamCheck = true;
			break;
		}
		case RS400_STREAM_INFRARED: {
			m_stereoSensor.open(stream_profile);
			m_stereoSensor.start([&](rs2::frame f) {m_ir_FrameQueue.enqueue(f); });
			m_irStreamCheck = true;
			break;
		}
		case RS400_STREAM_INFRARED1: {
			m_stereoSensor.open(stream_profile);
			m_stereoSensor.start([&](rs2::frame f) {m_ir1_FrameQueue.enqueue(f); });
			m_ir1StreamCheck = true;
			break;
		}
		case RS400_STREAM_INFRARED2: {
			m_stereoSensor.open(stream_profile);
			m_stereoSensor.start([&](rs2::frame f) {m_ir2_FrameQueue.enqueue(f); });
			m_ir2StreamCheck = true;
			break;
		}
		case RS400_STREAM_COLOR: {
			m_colorSensor.open(stream_profile);
			m_colorSensor.start([&](rs2::frame f) {m_colorFrameQueue.enqueue(f); });
			m_colorStreamCheck = true;
			break;
		}
		}
	}
}


void Device::startStreaming(vector<rs2::stream_profile> &stream_profile) {
	m_stereoSensor.open(stream_profile);
	for (auto sp : stream_profile) {
		RS_400_STREAM_TYPE spt = m_stream2Enum(sp.stream_name());
		switch (spt) {
		case RS400_STREAM_DEPTH: {m_depthStreamCheck = true;break;}
		case RS400_STREAM_INFRARED: {m_irStreamCheck = true;break;}
		case RS400_STREAM_INFRARED1: {m_ir1StreamCheck = true;break;}
		case RS400_STREAM_INFRARED2: {m_ir2StreamCheck = true;break;}
		}
	}

	m_stereoSensor.start([&](rs2::frame f) {
		auto sp = f.get_profile();
		RS_400_STREAM_TYPE streamType = m_stream2Enum(sp.stream_name());
		switch (streamType) {
		case RS400_STREAM_DEPTH: {
			m_depthFrameQueue.enqueue(f);
			break;
		}
		case RS400_STREAM_INFRARED: {
			m_ir_FrameQueue.enqueue(f);
			break;
		}
		case RS400_STREAM_INFRARED1: {
			m_ir1_FrameQueue.enqueue(f);
			break;
		}
		case RS400_STREAM_INFRARED2: {
			m_ir2_FrameQueue.enqueue(f);
			break;
		}
		}
	});
}

void Device::stopStreaming(rs2::stream_profile& stream_profile) {

}

void Device::stopStreaming(RS_400_SENSOR sensorName) {
	if (sensorName == STEREO_MODULE) {
		m_stereoSensor.stop();
		m_stereoSensor.close();
		m_depthStreamCheck = false;
		m_irStreamCheck = false;
		m_ir1StreamCheck = false;
		m_ir2StreamCheck = false;
	}
	else if (sensorName == RGB_CAMERA) {
		m_colorSensor.stop();
		m_colorSensor.close();
		m_colorStreamCheck = false;
	}
}

rs2::frame Device::capture(RS_400_STREAM_TYPE streamType) {
	switch (streamType) {
	case RS400_STREAM_DEPTH: {
		return m_depthFrameQueue.wait_for_frame();
	}
	case RS400_STREAM_INFRARED: {
		return m_ir_FrameQueue.wait_for_frame();
	}
	case RS400_STREAM_INFRARED1: {
		return m_ir1_FrameQueue.wait_for_frame();
	}
	case RS400_STREAM_INFRARED2: {
		return m_ir2_FrameQueue.wait_for_frame();
	}
	case RS400_STREAM_COLOR: {
		return m_colorFrameQueue.wait_for_frame();
	}
	}
}

void Device::EnableEmitter(float value) {
	if (m_stereoSensor.supports(rs2_option::RS2_OPTION_EMITTER_ENABLED))
	{
		m_stereoSensor.set_option(rs2_option::RS2_OPTION_EMITTER_ENABLED, value);
	}
}


/** 
 * Private Function area.
 */
void Device::m_getProfile(vector<stream_profile> &profile_set) {
	if (m_depthStreamCheck) {
		profile_set.push_back(m_depthFrameQueue.wait_for_frame().get_profile());
	}
	if (m_irStreamCheck) {
		profile_set.push_back(m_ir_FrameQueue.wait_for_frame().get_profile());
	}
	if (m_ir1StreamCheck) {
		profile_set.push_back(m_ir1_FrameQueue.wait_for_frame().get_profile());
	}
	if (m_ir2StreamCheck) {
		profile_set.push_back(m_ir2_FrameQueue.wait_for_frame().get_profile());
	}
}

RS_400_STREAM_TYPE Device::m_stream2Enum(string streamName) {
	if (streamName == "Infrared") {
		return RS_400_STREAM_TYPE::RS400_STREAM_INFRARED;
	}
	else if (streamName == "Infrared 1") {
		return RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1;
	}
	else if (streamName == "Infrared 2") {
		return RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2;
	}
	else if (streamName == "Depth") {
		return RS_400_STREAM_TYPE::RS400_STREAM_DEPTH;
	}
	else if (streamName == "Color") {
		return RS_400_STREAM_TYPE::RS400_STREAM_COLOR;
	}
}

RS_400_FORMAT Device::m_format2Enum(rs2_format format) {
	if (format == RS2_FORMAT_RAW16) {
		return RS_400_FORMAT::RAW16;
	}
	else if (format == RS2_FORMAT_Y16) {
		return RS_400_FORMAT::Y16;
	}
	else if (format == RS2_FORMAT_Y8) {
		return RS_400_FORMAT::Y8;
	}
	else if (format == RS2_FORMAT_BGRA8) {
		return RS_400_FORMAT::BGRA8;
	}
	else if (format == RS2_FORMAT_RGBA8) {
		return RS_400_FORMAT::RGBA8;
	}
	else if (format == RS2_FORMAT_BGR8) {
		return RS_400_FORMAT::BGR8;
	}
	else if (format == RS2_FORMAT_RGB8) {
		return RS_400_FORMAT::RGB8;
	}
	else if (format == RS2_FORMAT_YUYV) {
		return RS_400_FORMAT::YUYV;
	}
	else if (format == RS2_FORMAT_UYVY) {
		return RS_400_FORMAT::UYVY;
	}
	else if (format == RS2_FORMAT_Z16) {
		return RS_400_FORMAT::Z16;
	}

}

RS_400_RESOLUTION Device::m_resolution2Enum(string resolution) {
	if (resolution == "1920x1080") {
		return RS_400_RESOLUTION::R1920_1080;
	}
	else if (resolution == "1280x720") {
		return RS_400_RESOLUTION::R1280_720;
	}
	else if (resolution == "960x540") {
		return RS_400_RESOLUTION::R960_540;
	}
	else if (resolution == "848x480") {
		return RS_400_RESOLUTION::R848_480;
	}
	else if (resolution == "640x480") {
		return RS_400_RESOLUTION::R640_480;
	}
	else if (resolution == "640x360") {
		return RS_400_RESOLUTION::R640_360;
	}
	else if (resolution == "480x270") {
		return RS_400_RESOLUTION::R480_270;
	}
	else if (resolution == "424x240") {
		return RS_400_RESOLUTION::R424_240;
	}
	else if (resolution == "320x240") {
		return RS_400_RESOLUTION::R320_240;
	}
	else if (resolution == "320x180") {
		return RS_400_RESOLUTION::R320_180;
	}
}

RS_400_FPS Device::m_fps2Enum(int fps) {
	if (fps == 90) {
		return RS_400_FPS::HZ90;
	}
	else if (fps == 60) {
		return RS_400_FPS::HZ60;
	}
	else if (fps == 30) {
		return RS_400_FPS::HZ30;
	}
	else if (fps == 25) {
		return RS_400_FPS::HZ25;
	}
	else if (fps == 15) {
		return RS_400_FPS::HZ15;
	}
	else if (fps == 6) {
		return RS_400_FPS::HZ6;
	}
}
