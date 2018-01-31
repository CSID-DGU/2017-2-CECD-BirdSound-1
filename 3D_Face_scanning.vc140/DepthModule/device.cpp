#include "device.h"

using namespace realsense;

Device::Device(string serialNumber) {

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
	auto sensors = m_device.query_sensors();
	m_depthSensor = sensors[0];

	//device info record
	info.name = m_device.get_info(rs2_camera_info::RS2_CAMERA_INFO_NAME);
	info.pid = m_device.get_info(rs2_camera_info::RS2_CAMERA_INFO_PRODUCT_ID);
	info.serial = m_device.get_info(rs2_camera_info::RS2_CAMERA_INFO_SERIAL_NUMBER);
	info.fw_ver = m_device.get_info(rs2_camera_info::RS2_CAMERA_INFO_FIRMWARE_VERSION);

}