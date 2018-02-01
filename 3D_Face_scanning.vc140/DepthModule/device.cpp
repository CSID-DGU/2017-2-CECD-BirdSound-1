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
		auto streamType = m_streamName2Enum(sp.stream_name());
		m_streoUniqueStreams[]
		//m_streoUniqueStreams[std::make_pair(sp.stream_type(), sp.stream_index())]++;
	}

	stream_profiles = m_colorSensor.get_stream_profiles();
	for (auto&& sp : stream_profiles)
	{
		m_colorUniqueStreams[std::make_pair(sp.stream_type(), sp.stream_index())]++;
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

void Device::selectSensorAndStream() {
	m_selectedSensor = RS_400_SENSOR::RGB_CAMERA;
	m_selectedStream = RS_400_STREAM_TYPE::RS400_STREAM_COLOR;
}


void Device::startStreaming(int streamProp) {
	if (m_selectedSensor == RS_400_SENSOR::RGB_CAMERA) {

	}
	else if (m_selectedSensor == RS_400_SENSOR::STEREO_MODULE) {

	}


}


RS_400_STREAM_TYPE Device::m_streamName2Enum(string streamName) {
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