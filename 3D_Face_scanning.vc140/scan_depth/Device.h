#pragma once

#include <librealsense/rs.hpp>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>


using namespace std;
using namespace io;
using namespace rs;
class Device {
	
public:
	context ctx;
	device * dev = ctx.get_device(0);

	////////////////////////////////////////////////////////////////////////
	std::vector<rs::device *> devices;

	Device()
	{
		init();
	}
	void init() 
	{
		for (int i = 0; i < ctx.get_device_count(); ++i)devices.push_back(ctx.get_device(i));
		// Configure and start our devices
		for (auto dev : devices)
		{
			std::cout << "Starting " << dev->get_name() << "... ";
			dev->enable_stream(rs::stream::depth, rs::preset::best_quality);
			dev->enable_stream(rs::stream::color, rs::preset::best_quality);
			dev->start();
		}
	}
};