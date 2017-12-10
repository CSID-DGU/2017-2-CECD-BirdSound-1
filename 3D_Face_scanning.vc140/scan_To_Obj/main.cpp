#include "stdafx.h"
#include "ObjWriter.h"
#define WIDTH 640
#define HEIGHT 480
// First include the librealsense C++ header file
#include <librealsense/rs.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;


/*
int main() try
{
	// Turn on logging. We can separately enable logging to console or to file, and use different severity filters for each.
	rs::log_to_console(rs::log_severity::warn);
	//rs::log_to_file(rs::log_severity::debug, "librealsense.log");

	// Create a context object. This object owns the handles to all connected realsense devices.
	rs::context ctx;
	printf("There are %d connected RealSense devices.\n", ctx.get_device_count());
	if (ctx.get_device_count() == 0) return EXIT_FAILURE;

	// This tutorial will access only a single device, but it is trivial to extend to multiple devices
	rs::device * dev = ctx.get_device(0);
	printf("\nUsing device 0, an %s\n", dev->get_name());
	printf("    Serial number: %s\n", dev->get_serial());
	printf("    Firmware version: %s\n", dev->get_firmware_version());

	// Configure depth and color to run with the device's preferred settings
	dev->enable_stream(rs::stream::depth, rs::preset::best_quality);
	dev->enable_stream(rs::stream::color, rs::preset::best_quality);
	dev->start();


	PointCloud<PointXYZ> depth;
	depth.width = WIDTH;
	depth.height = HEIGHT;
	depth.is_dense = false;
	depth.points.resize(depth.width * depth.height);


	Color *color = new Color[WIDTH*HEIGHT];

	// Wait for new frame data
	dev->wait_for_frames();

	// Retrieve our images
	const uint16_t * depth_image = (const uint16_t *)dev->get_frame_data(rs::stream::depth);
	const uint8_t * color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);

	// Retrieve camera parameters for mapping between depth and color
	rs::intrinsics depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
	rs::extrinsics depth_to_color = dev->get_extrinsics(rs::stream::depth, rs::stream::color);
	rs::intrinsics color_intrin = dev->get_stream_intrinsics(rs::stream::color);
	float scale = dev->get_depth_scale();

	int I_C_point = 0;
	for (int dy = 0; dy < depth_intrin.height; ++dy)
	{
		for (int dx = 0; dx < depth_intrin.width; ++dx)
		{
			uint16_t depth_value = depth_image[dy * depth_intrin.width + dx];
			float depth_in_meters = depth_value * scale;

			// Skip over pixels with a depth value of zero, which is used to indicate no data
			//if(depth_value == 0) continue;

			// Map from pixel coordinates in the depth image to pixel coordinates in the color image
			rs::float2 depth_pixel = { (float)dx, (float)dy };	//2차원 픽셀을 구성 
			rs::float3 depth_point = depth_intrin.deproject(depth_pixel, depth_in_meters); //2차원에 실제 z값을 대입함 
			rs::float3 color_point = depth_to_color.transform(depth_point); //depth포인트를 color가 맵핑되는 포인트 좌표로 변환 
			rs::float2 color_pixel = color_intrin.project(color_point); //컬러

			//if (depth_value == 0)
			//pcd << "" << -depth_point.x << "\t" << -depth_point.y << "\t" << -depth_point.z << std::endl; //depth 
			//C_Pix << "" << color_pixel.x << "\t" << color_pixel.y << "\t" << std::endl; //color
			//I_C_point++;

			depth.points[dy*WIDTH + dx].x = -depth_point.x;
			depth.points[dy*WIDTH + dx].y = -depth_point.y;
			depth.points[dy*WIDTH + dx].z = -depth_point.z;

			color[dy*WIDTH + dx].x = (int)std::round(color_pixel.x);
			color[dy*WIDTH + dx].y = (int)std::round(color_pixel.x);
		}
	}

	char filename[FILE_LEN] = "f";
	char imgfile[FILE_LEN+5] = "";
	strcpy(imgfile, filename);
	strcat(imgfile, ".bmp");
	stbi_write_bmp(imgfile, color_intrin.width, color_intrin.height, 3, color_image);
	ObjWriter Obj("f", &depth, color);
	std::cout << I_C_point;
	exit(1);
}
*/
// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2015 Intel Corporation. All Rights Reserved.

///////////////////////////////////////////////////////
// librealsense tutorial #3 - Point cloud generation //
///////////////////////////////////////////////////////

// Also include GLFW to allow for graphical display
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


double yaw, pitch, lastX, lastY; int ml;
static void on_mouse_button(GLFWwindow * win, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) ml = action == GLFW_PRESS;
}
static double clamp(double val, double lo, double hi) { return val < lo ? lo : val > hi ? hi : val; }
static void on_cursor_pos(GLFWwindow * win, double x, double y)
{
	if (ml)
	{
		yaw = clamp(yaw - (x - lastX), -120, 120);
		pitch = clamp(pitch + (y - lastY), -80, 80);
	}
	lastX = x;
	lastY = y;
}

int main() try
{
	// Turn on logging. We can separately enable logging to console or to file, and use different severity filters for each.
	rs::log_to_console(rs::log_severity::warn);
	//rs::log_to_file(rs::log_severity::debug, "librealsense.log");

	// Create a context object. This object owns the handles to all connected realsense devices.
	rs::context ctx;
	printf("There are %d connected RealSense devices.\n", ctx.get_device_count());
	if (ctx.get_device_count() == 0) return EXIT_FAILURE;

	// This tutorial will access only a single device, but it is trivial to extend to multiple devices
	rs::device * dev = ctx.get_device(0);
	printf("\nUsing device 0, an %s\n", dev->get_name());
	printf("    Serial number: %s\n", dev->get_serial());
	printf("    Firmware version: %s\n", dev->get_firmware_version());

	// Configure depth and color to run with the device's preferred settings
	dev->enable_stream(rs::stream::depth, rs::preset::best_quality);
	dev->enable_stream(rs::stream::color, rs::preset::best_quality);
	dev->start();

	// Open a GLFW window to display our output
	glfwInit();
	GLFWwindow * win = glfwCreateWindow(1280, 960, "librealsense tutorial #3", nullptr, nullptr);
	glfwSetCursorPosCallback(win, on_cursor_pos);
	glfwSetMouseButtonCallback(win, on_mouse_button);
	glfwMakeContextCurrent(win);
	while (!glfwWindowShouldClose(win))
	{
		// Wait for new frame data
		glfwPollEvents();
		dev->wait_for_frames();

		// Retrieve our images
		const uint16_t * depth_image = (const uint16_t *)dev->get_frame_data(rs::stream::depth);
		const uint8_t * color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);

		// Retrieve camera parameters for mapping between depth and color
		rs::intrinsics depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
		rs::extrinsics depth_to_color = dev->get_extrinsics(rs::stream::depth, rs::stream::color);
		rs::intrinsics color_intrin = dev->get_stream_intrinsics(rs::stream::color);
		float scale = dev->get_depth_scale();

		// Set up a perspective transform in a space that we can rotate by clicking and dragging the mouse
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (float)1280 / 960, 0.01f, 20.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 0, 0, 0, 1, 0, -1, 0);
		glTranslatef(0, 0, +0.5f);
		glRotated(pitch, 1, 0, 0);
		glRotated(yaw, 0, 1, 0);
		glTranslatef(0, 0, -0.5f);

		// We will render our depth data as a set of points in 3D space
		glPointSize(2);
		glEnable(GL_DEPTH_TEST);
		glBegin(GL_POINTS);

		//std::ofstream C_Point("C_Point.txt");
		std::ofstream C_Pix("f.txt");
		std::ofstream pcd("f.pcd");
		int I_C_point = 0;
		pcd << "# .PCD v0.7 - Point Cloud Data file format\n" <<
			"VERSION 0.7\n" <<
			"FIELDS x y z\n" <<
			"SIZE 4 4 4\n" <<
			"TYPE F F F\n" <<
			"COUNT 1 1 1\n" <<
			"WIDTH " << depth_intrin.width << "\n" <<
			"HEIGHT " << depth_intrin.height << "\n" <<
			"VIEWPOINT 0 0 0 1 0 0 0\n" <<
			"POINTS 307200\n" <<
			"DATA ascii\n";
		for (int dy = 0; dy<depth_intrin.height; ++dy)
		{
			for (int dx = 0; dx<depth_intrin.width; ++dx)
			{
				//if (dx == 240)//480 640
				//	if (dy == 320)
				//		printf("1");
				// Retrieve the 16-bit depth value and map it into a depth in meters
				uint16_t depth_value = depth_image[dy * depth_intrin.width + dx];
				float depth_in_meters = depth_value * scale;

				// Skip over pixels with a depth value of zero, which is used to indicate no data
				//if(depth_value == 0) continue;

				// Map from pixel coordinates in the depth image to pixel coordinates in the color image
				rs::float2 depth_pixel = { (float)dx, (float)dy };	//2차원 픽셀을 구성 
				rs::float3 depth_point = depth_intrin.deproject(depth_pixel, depth_in_meters); //2차원에 실제 z값을 대입함 
				rs::float3 color_point = depth_to_color.transform(depth_point); //depth포인트를 color가 맵핑되는 포인트 좌표로 변환 
				rs::float2 color_pixel = color_intrin.project(color_point); //컬러

																			//if (depth_value == 0)
				pcd << "" << -depth_point.x << "\t" << -depth_point.y << "\t" << -depth_point.z << std::endl; //depth 
				C_Pix << "" << color_pixel.x << "\t" << color_pixel.y << "\t" << std::endl; //color
																							//I_C_point++;

																							// Use the color from the nearest color pixel, or pure white if this point falls outside the color image
				const int cx = (int)std::round(color_pixel.x), cy = (int)std::round(color_pixel.y);
				if (cx < 0 || cy < 0 || cx >= color_intrin.width || cy >= color_intrin.height)
				{
					glColor3ub(255, 255, 255);
				}
				else
				{
					glColor3ubv(color_image + (cy * color_intrin.width + cx) * 3);
				}

				// Emit a vertex at the 3D location of this depth pixel
				glVertex3f(depth_point.x, depth_point.y, depth_point.z);
			}
		}

		stbi_write_bmp("f.bmp", color_intrin.width, color_intrin.height, 3, color_image);
		std::cout << I_C_point;

		glEnd();

		glfwSwapBuffers(win);
	}

	return EXIT_SUCCESS;
}
catch (const rs::error & e)
{
	// Method calls against librealsense objects may throw exceptions of type rs::error
	printf("rs::error was thrown when calling %s(%s):\n", e.get_failed_function().c_str(), e.get_failed_args().c_str());
	printf("    %s\n", e.what());
	return EXIT_FAILURE;
}

catch (const rs::error & e)
{
	// Method calls against librealsense objects may throw exceptions of type rs::error
	printf("rs::error was thrown when calling %s(%s):\n", e.get_failed_function().c_str(), e.get_failed_args().c_str());
	printf("    %s\n", e.what());
	return EXIT_FAILURE;
}
