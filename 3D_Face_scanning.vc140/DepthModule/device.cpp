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

Device::Device(string serialNumber) {
	#ifdef _WIN32
	InitializeCriticalSection(&m_mutex);
	#else
	if (0 != pthread_mutex_init(&m_mutex, NULL)) throw
		std::runtime_error("pthread_mutex_init failed");
	#endif
	m_stereoSensor = nullptr;
	m_colorSensor = nullptr;

	//set target device object
	m_context = new context;
	device_list devices = m_context->query_devices();
	for (size_t i = 0; i < devices.size(); i++) {
		if (devices[i].get_info(RS2_CAMERA_INFO_SERIAL_NUMBER) == serialNumber) {
			m_device = devices[i];
		}
	}
	
	//check is advanced?
	if (m_device.is<rs400::advanced_mode>()){
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
	}

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
			cout << "    " << left << setw(30) << index++
				<< ": \t" << sensor.get_info(RS2_CAMERA_INFO_NAME) << endl;
		}

	}
}

void Device::printSensorInfo() {
	cout << "\n\nSensor detail Info" << endl;
	auto sensors = m_sensors;
	for (rs2::sensor sensor : sensors) {
		for (int i = 0; i < static_cast<int>(RS2_OPTION_COUNT); i++)
		{
			rs2_option option_type = static_cast<rs2_option>(i);
			//SDK enum types can be streamed to get a string that represents them
			cout << "    " << left << setw(30) << i << ": \t" << option_type;

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

void Device::selectSensorAndStreamProps() {
	// Select "RGB Camera" Sensor
	m_selectedSensor = RS_400_SENSOR::RGB_CAMERA;

	// Select "StreamType" and "Resolution - Format - FPS"
	// ex: [RS400_STREAM_COLOR][1920x1080-BGR8-30Hz]
	startStreaming(m_colorUniqueStreams[RS400_STREAM_COLOR][53].second);

}

/**
 * 짜다 만거지만, Open CV 로 스트림 뽑아내는거

*/
void Device::startStreaming(rs2::stream_profile& stream_profile) {

	if (m_selectedSensor == RS_400_SENSOR::RGB_CAMERA) {
		m_colorSensor.open(stream_profile);
		m_colorSensor.start([&](rs2::frame f) {
			MUTEX_LOCK(&m_mutex);
			std::cout << "This line be printed every frame!" << std::endl;
			m_depthFrameQueue.enqueue(move(f));
			MUTEX_UNLOCK(&m_mutex);
		});

		while (1) {
			std::cout << "frame emit" << endl;
			rs2::frame f = m_depthFrameQueue.wait_for_frame();
			cv::Mat image(cv::Size(1920, 1080), CV_8UC3, (void*)f.get_data(), cv::Mat::AUTO_STEP);
			cv::imshow("CV Video Client", image);

		};
	}
	else if (m_selectedSensor == RS_400_SENSOR::STEREO_MODULE) {

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