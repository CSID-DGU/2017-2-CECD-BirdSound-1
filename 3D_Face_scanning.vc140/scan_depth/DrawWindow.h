#include<iostream>
#include <sstream>
#include<vector>
#include <librealsense/rs.hpp>
#include<GLFW\glfw3.h>

#include"example.hpp"
class DrawWindows
{
public:
	
	GLFWwindow *win;
	int windowWidth=1280, windowHeight=960;
	std::vector<texture_buffer> buffers;

	DrawWindows(int _width, int _height, char* title, int devCount)
	{
		windowWidth = _width;
		windowHeight = _height;
		glfwInit();
		win = glfwCreateWindow(windowWidth, windowHeight, title, 0, 0);
		buffers.resize(devCount * 2);
	}
	
	void init(rs::device *dev, std::vector<rs::device *> &devices)
	{
		
		glfwMakeContextCurrent(win);
		glfwGetWindowSize(win, &windowWidth, &windowHeight);
		auto perTextureWidth = int(windowWidth / devices.size());
		auto perTextureHeight = 480;

		while (!glfwWindowShouldClose(win))
		{
			// Wait for new images
			glfwPollEvents();

			// Draw the images
			int w, h;
			glfwGetFramebufferSize(win, &w, &h);
			glViewport(0, 0, w, h);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwGetWindowSize(win, &w, &h);
			glPushMatrix();
			glOrtho(0, w, h, 0, -1, +1);
			glPixelZoom(1, -1);
			int i = 0, x = 0;
			for (auto dev : devices)
			{
				dev->poll_for_frames();
				const auto c = dev->get_stream_intrinsics(rs::stream::color), d = dev->get_stream_intrinsics(rs::stream::depth);
				buffers[i++].show(*dev, rs::stream::color, x, 0, perTextureWidth, perTextureHeight);
				buffers[i++].show(*dev, rs::stream::depth, x, perTextureHeight, perTextureWidth, perTextureHeight);
				x += perTextureWidth;
			}

			glPopMatrix();
			glfwSwapBuffers(win);
		}

		glfwDestroyWindow(win);
		glfwTerminate();

	}
};