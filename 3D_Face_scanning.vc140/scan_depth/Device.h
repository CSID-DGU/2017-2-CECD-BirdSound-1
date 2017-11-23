#pragma once
#include <librealsense/rs.hpp>
#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef enum {BMP, PNG} filetype;

using namespace std;
using namespace rs;

class Device {
	
public:
	rs::context ctx;
	rs:: device * dev;
	float depth_scale;
	std::vector<rs::device *> devices;
	rs::intrinsics color_intrin;
	rs::intrinsics depth_intrin;
	rs::extrinsics depth_to_color;
	const uint16_t * depth_image;
	const uint8_t * color_image;

	Device()
	{
		printf("There are %d connected RealSense devices.\n", ctx.get_device_count());
		dev = ctx.get_device(0);
		printf("\nUsing device 0, an %s\n", dev->get_name());
		printf("    Serial number: %s\n", dev->get_serial());
		printf("    Firmware version: %s\n", dev->get_firmware_version());
	}

	void start() 
	{
		for (int i = 0; i < ctx.get_device_count(); ++i)devices.push_back(ctx.get_device(i));
		// Configure and start our devices
		for (auto dev : devices)
		{
			std::cout << "Starting " << dev->get_name() << "... " << endl;
			dev->enable_stream(rs::stream::color, 640, 480, rs::format::rgb8, 60); cout << "color cam active complete" << endl;
			dev->enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 60); cout << "depth active complete" << endl;
			//z/dev->enable_stream(rs::stream::depth, rs::preset::best_quality);
			//dev->enable_stream(rs::stream::color, rs::preset::best_quality);
			dev->start();
		}
	}

	void capture() {
		dev->wait_for_frames();
		depth_scale = dev->get_depth_scale();
		color_intrin = dev->get_stream_intrinsics(rs::stream::color);
		depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
		depth_to_color = dev->get_extrinsics(rs::stream::depth, rs::stream::color);
		depth_image = (const uint16_t *)dev->get_frame_data(rs::stream::depth);
		color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);
	}
	
	const rs::float3 * get_depth_points_array() {
		const rs::float3 *points = reinterpret_cast<const rs::float3 *>(dev->get_frame_data(rs::stream::points));
		return points;
	}

	void save_image_file(string filename, filetype ft) {
		switch (ft) {
		case BMP: stbi_write_bmp(filename.c_str(), color_intrin.width, color_intrin.height, 3, color_image); break;
		case PNG: stbi_write_png(filename.c_str(), color_intrin.width, color_intrin.height, 3, color_image, 3 * color_intrin.width); break;
		//case JPG: stbi_write_jpg(filename.c_str(), color_intrin.width, color_intrin.height, 3, color_image); break;
		//case TGA: stbi_write_tga(filename.c_str(), color_intrin.width, color_intrin.height, 3, color_image); break;
		//case HDR: stbi_write_hdr(filename.c_str(), color_intrin.width, color_intrin.height, 3, color_image); break;
		default: break;
		}
		printf("Image File save complete!\n");
	}
};