#pragma once

#include "device.h"

using namespace realsense;
int main(void) {
	string devSerialNumber = getFirstSerial();
	Device* device = new Device(devSerialNumber);
	device->printDeviceInfo();
	device->printSensorInfo();
	
}