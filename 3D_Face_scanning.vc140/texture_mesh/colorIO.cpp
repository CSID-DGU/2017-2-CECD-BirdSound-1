#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stdafx.h"


using namespace std;
using namespace rs;


//https://github.com/IntelRealSense/librealsense/issues/156
//https://github.com/IntelRealSense/librealsense/issues/78


int colorIO() try {
	//PointCloud<PointXYZ> cloud;

	rs::context ctx;
	printf("There are %d connected RealSense devices.\n", ctx.get_device_count());
	if (ctx.get_device_count() == 0) return EXIT_FAILURE;

	rs::device * dev = ctx.get_device(0);
	printf("\nUsing device 0, an %s\n", dev->get_name());
	printf("    Serial number: %s\n", dev->get_serial());
	printf("    Firmware version: %s\n", dev->get_firmware_version());


	//dev->enable_stream(rs::stream::color, rs::preset::best_quality); cout << "color cam active complete" << endl;
	dev->enable_stream(rs::stream::color, 640, 480, rs::format::rgb8, 60); cout << "color cam active complete" << endl;
	dev->enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 60); cout << "depth active complete" << endl;
	dev->start();
	dev->wait_for_frames();

	const uint16_t * depth_image = (const uint16_t *)dev->get_frame_data(rs::stream::depth);
	const uint8_t * color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);

	rs::intrinsics color_intrin = dev->get_stream_intrinsics(rs::stream::color);
	rs::intrinsics depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
	rs::extrinsics depth_to_color = dev->get_extrinsics(rs::stream::depth, rs::stream::color);

	float scale = dev->get_depth_scale();


	stbi_write_png("nj_snapshot.png", color_intrin.width, color_intrin.height, 3, color_image, 3 * color_intrin.width);

	for (int dy = 0; dy<depth_intrin.height; ++dy)
	{
		for (int dx = 0; dx<depth_intrin.width; ++dx)
		{
			int depthIndex = dy*depth_intrin.width + dx;
			uint16_t depth_value = depth_image[depthIndex];
			float depth_in_meters = depth_value * scale;

			// Map from pixel coordinates in the depth image to pixel coordinates in the color image
			rs::float2 depth_pixel = { (float)dx, (float)dy };
			rs::float3 depth_point = depth_intrin.deproject(depth_pixel, depth_in_meters);
			rs::float3 color_point = depth_to_color.transform(depth_point);
			rs::float2 color_pixel = color_intrin.project(color_point);


			// Use the color from the nearest color pixel, or pure white if this point falls outside the color image
			int cx = (int)std::round(color_pixel.x), cy = (int)std::round(color_pixel.y);
			int colorIndex = (cy * color_intrin.width + cx) * 3;
			// A pointer to an array that contains red, green, and blue values.
			int pixelR = color_image[colorIndex];
			int pixelG = color_image[colorIndex + 1];
			int pixelB = color_image[colorIndex + 2];
			cout << pixelR << "/" << pixelG << "/" << pixelB << endl;
		}
	}

	int a = 0;

	return EXIT_SUCCESS;
}
catch (const rs::error & e)
{
	// Method calls against librealsense objects may throw exceptions of type rs::error
	printf("rs::error was thrown when calling %s(%s):\n", e.get_failed_function().c_str(), e.get_failed_args().c_str());
	printf("    %s\n", e.what());
	return EXIT_FAILURE;
}
