/*
* INTEL CORPORATION PROPRIETARY INFORMATION
* This software is supplied under the terms of a license agreement
* or nondisclosure agreement with Intel Corporation and may not be
* copied or disclosed except in accordance with the terms of that
* agreement.
* Copyright(c) 2016-2017 Intel Corporation. All Rights Reserved.
*/
#pragma once
#include <iostream>
#include <string>
#include "GL/freeglut.h"
#include "CalibrationManager.h"
#include "CustomCalibration.h"
using namespace std;
using namespace CustomCalibrator;
using namespace RsCamera;
using namespace CustomCalibWrapper;
CustomCalibration::CustomCalibration()
{
	m_rsDevice = new Rs400Device();
	m_captureStarted = false;
	m_numShot = 0;
	m_imagesCapture = false;
	m_inProcessing = false;
	m_inUpdating = false;
	m_shotFailed = false;
	m_watch = new Stopwatch();
}
CustomCalibration::~CustomCalibration()
{
	if (m_captureStarted)
		m_rsDevice->StopCapture();
}
bool CustomCalibration::Initialize()
{
	int numCameras = 2;
	InitializeGL((void *)this);
	m_cameraInfo = m_rsDevice->InitializeCamera();
	if (m_cameraInfo.name.empty()) return false;
	if (m_cameraInfo.isWide)
	{
		m_width = 1280;
		m_height = 800;
	}
	else
	{
		m_width = 1920;
		m_height = 1080;
	}
	m_fps = 15;
	m_rgbWidth = 1920;
	m_rgbHeight = 1080;
	m_leftImage = std::unique_ptr<uint8_t[]>(new uint8_t[m_width*(m_height + 1)]);
	* Copyright(c) 2016-2017 Intel Corporation. All Rights Reserved.
*/
#pragma once
#include <iostream>
#include <string>
#include "GL/freeglut.h"
#include "CalibrationManager.h"
#include "CustomCalibration.h"
using namespace std;
using namespace CustomCalibrator;
using namespace RsCamera;
using namespace CustomCalibWrapper;
CustomCalibration::CustomCalibration()
{
m_rsDevice = new Rs400Device();
m_captureStarted = false;
m_numShot = 0;
m_imagesCapture = false;
m_inProcessing = false;
m_inUpdating = false;
m_shotFailed = false;
m_watch = new Stopwatch();
}
CustomCalibration::~CustomCalibration()
{
if (m_captureStarted)
m_rsDevice->StopCapture();
}
bool CustomCalibration::Initialize()
{
int numCameras = 2;
InitializeGL((void *)this);
m_cameraInfo = m_rsDevice->InitializeCamera();
if (m_cameraInfo.name.empty()) return false;
if (m_cameraInfo.isWide)
{
m_width = 1280;
m_height = 800;
}
else
{
m_width = 1920;
m_height = 1080;
}
m_fps = 15;
m_rgbWidth = 1920;
m_rgbHeight = 1080;
m_leftImage = std::unique_ptr<uint8_t[]>(new uint8_t[m_width*(m_height + 1)]);
m_rightImage = std::unique_ptr<uint8_t[]>(new uint8_t[m_width*(m_height + 1)]);
if (m_cameraInfo.isRGB)
{
	m_colorImage = std::unique_ptr<uint32_t[]>(new
		uint32_t[m_rgbWidth*(m_rgbHeight + 1)]);
	m_grayImage = std::unique_ptr<uint8_t[]>(new
		uint8_t[m_rgbWidth*(m_rgbHeight + 1)]);
	numCameras += 1;
}
m_calibWrapper = new CustomCalibrationWrapper(m_rsDevice->GetDeviceHandle(),
	CHESSBOARD_WIDTH, CHESSBOARD_HEIGHT, CHESSBOARD_SQUARE_SIZE, numCameras,
	NUM_SHOTS);
return true;
}
void CustomCalibration::InitializeGL(void *parentClass)
{
	int c = 0;
	// Open a GLUT window to display point cloud
	glutInit(&c, nullptr);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Intel RealSense Custom Calibrator");
	glutSetWindowData(parentClass);
	glutDisplayFunc([]() {
		CustomCalibration *pCalib = reinterpret_cast<CustomCalibration
			*>(glutGetWindowData());
		pCalib->OnDisplay();
	});
	glutIdleFunc([]() {
		CustomCalibration *pCalib = reinterpret_cast<CustomCalibration
			*>(glutGetWindowData());
		pCalib->OnIdle();
	});
	glutReshapeFunc([](int width, int height) {
		glViewport(0, 0, width, height);
	});
	glutCloseFunc([]() {
		CustomCalibration *pCalib = reinterpret_cast<CustomCalibration
			*>(glutGetWindowData());
		pCalib->OnClose();
	});
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		CustomCalibration *pCalib = reinterpret_cast<CustomCalibration
			*>(glutGetWindowData());
		pCalib->OnKeyBoard(key, x, y);
	});
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	int winWidth = glutGet(GLUT_WINDOW_WIDTH);
	int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, winWidth, winHeight);
	glGenTextures(3, m_textures);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void CustomCalibration::Start(void)
{
	if (m_captureStarted) return;
	m_captureStarted = true;
	m_rsDevice->EnableEmitter(0.0f);
	m_rsDevice->EnableAutoExposure(1.0f);
	if (m_cameraInfo.isWide)
		m_rsDevice->SetAeControl(800);
	else
		m_rsDevice->SetAeControl(500);
	m_rsDevice->SetMediaMode(m_width, m_height, m_fps, m_rgbWidth, m_rgbHeight,.isRGB);
	m_rsDevice->StartCapture([&](const void *leftImage, const void *rightImage, void *colorImage, const uint64_t timeStamp)
	{
		uint8_t *left = m_leftImage.get();
		ConvertLuminance16ToLuminance8((uint16_t *)leftImage, m_width, m_height,);
		uint8_t *right = m_rightImage.get();
		ConvertLuminance16ToLuminance8((uint16_t *)rightImage, m_width, m_height,);
		if (colorImage != nullptr)
		{
			uint32_t *color = m_colorImage.get();
			ConvertYUY2ToRGBA((uint8_t *)colorImage, m_rgbWidth, m_rgbHeight,
				(uint8_t*)color);
		}
		if (m_imagesCapture && m_numShot < NUM_SHOTS)
		{
			m_imagesCapture = false;
			m_inProcessing = true;
			glutPostRedisplay();
			bool rt = m_calibWrapper->AddImage(left, m_width, m_height,
				m_width, 0, m_numShot);
			if (rt)
			{
				rt = m_calibWrapper->AddImage(right, m_width, m_height,
					m_width, 1, m_numShot);
				if (rt && m_cameraInfo.isRGB)
				{
					uint8_t *gray = m_grayImage.get();
					ConvertYUY2ToLuminance8((uint8_t *)colorImage,
						m_rgbWidth, m_rgbHeight, gray);
					rt = m_calibWrapper->AddImage(gray, m_rgbWidth,
						m_rgbHeight, m_rgbWidth, 2, m_numShot);
				}
			}
			m_inProcessing = false;
			if (rt)
			{
				m_numShot += 1;
			}
			else
			{
				m_watch->Restart();
				m_shotFailed = true;
			}
			if (m_numShot == NUM_SHOTS)
			{
				m_inUpdating = true;
				glutPostRedisplay();
				rt = m_calibWrapper->CalculateCalibration(m_width,
					m_height, m_rgbWidth, m_rgbHeight);
				if (rt == 0)
					printf("Calibration successed.\n");
				else
					printf("Calibration failed.\n");
				m_inUpdating = false;
				glutLeaveMainLoop();
			}
		}
		glutPostRedisplay();
	});
}
void CustomCalibration::ConvertLuminance16ToLuminance8(const uint16_t* image, int width,
	int height, uint8_t* output)
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
void CustomCalibration::ConvertYUY2ToLuminance8(const uint8_t* image, int width, int
	height, uint8_t* output)
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
void CustomCalibration::OnDisplay(void)
{
	// Render image
	glEnable(GL_TEXTURE_2D);
	glColor4ub(255, 255, 255, 255);
	if (m_cameraInfo.isRGB)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		uint8_t *color = (uint8_t*)m_colorImage.get();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_rgbWidth, m_rgbHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, color);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex2d(-1.0, -1.0);
		glTexCoord2d(0, 0); glVertex2d(-1.0, 1.0);
		glTexCoord2d(1, 0); glVertex2d(1.0, 1.0);
		glTexCoord2d(1, 1); glVertex2d(1.0, -1.0);
		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	uint8_t *left = m_leftImage.get();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_LUMINANCE,
		GL_UNSIGNED_BYTE, left);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2d(-1.0, -1.0);
	glTexCoord2d(0, 0); glVertex2d(-1.0, -0.5);
	glTexCoord2d(1, 0); glVertex2d(-0.5, -0.5);
	glTexCoord2d(1, 1); glVertex2d(-0.5, -1.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, m_textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	uint8_t *right = m_rightImage.get();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_LUMINANCE,
		GL_UNSIGNED_BYTE, right);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2d(-0.5, -1.0);
	glTexCoord2d(0, 0); glVertex2d(-0.5, -0.5);
	glTexCoord2d(1, 0); glVertex2d(0, -0.5);
	glTexCoord2d(1, 1); glVertex2d(0, -1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	COLOR color = { 0xFF, 0x45, 0, 0xFF };
	if (m_inProcessing || m_inUpdating || m_shotFailed)
	{
		if (m_inProcessing || m_inUpdating)
		{
			color.G = 0xff;
			color.R = 0;
			if (m_inProcessing)
				RenderText(-5, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Processing
					image ...", color);
			else
					RenderText(-5, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Processing
						calibration ...", color);
		}
		else
		{
			RenderText(-5, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Corner detection
				failed.Please retake the shot", color);
				if (m_watch->ElapsedMilliseconds() > 2000)
				{
					m_shotFailed = false;
				}
		}
	}
	else
	{
		std::vector<POINT_D> points;
		points.push_back({ -1.0, 0.0 });
		points.push_back({ 1.0, 0.0 });
		points.push_back({ 0.0, 1.0 });
		points.push_back({ 0.0, -1.0 });
		points.push_back({ -1.0, -0.75 });
		points.push_back({ -0.502, -0.75 });
		points.push_back({ -0.498, -0.75 });
		points.push_back({ 0.0, -0.75 });
		points.push_back({ -0.75, -0.5 });
		points.push_back({ -0.75, -1.0 });
		points.push_back({ -0.25, -0.5 });
		points.push_back({ -0.25, -1.0 });
		RenderLines(points, color, 2);
	}
	color.G = 0xFF;
	color.B = 0xFF;
	string numCaptured = to_string(m_numShot) + " / " + to_string(NUM_SHOTS);
	RenderText(-3, -0.92, GLUT_BITMAP_TIMES_ROMAN_24, numCaptured.c_str(), color);
	RenderText(-2, 0.85, GLUT_BITMAP_TIMES_ROMAN_24, m_cameraInfo.name.c_str(),
		color);
	string fwVersion = "FW Version: " + m_cameraInfo.fw_ver;
	RenderText(-3, 0.85, GLUT_BITMAP_TIMES_ROMAN_24, fwVersion.c_str(), color);
	string serial = "Serial Number: " + m_cameraInfo.serial;
	RenderText(-3, 0.75, GLUT_BITMAP_TIMES_ROMAN_24, serial.c_str(), color);
	glutSwapBuffers();
}
void CustomCalibration::OnIdle(void)
{ }
void CustomCalibration::OnKeyBoard(unsigned char key, int x, int y)
{
	switch (tolower(key))
	{
	case 'q':
	case 27: //ESC
		if (m_captureStarted)
		{
			m_rsDevice->StopCapture();
		}
		glutLeaveMainLoop();
		break;
	case 13: //Enter
		m_imagesCapture = true;
		break;
	}
}
void CustomCalibration::OnClose(void)
{
	if (m_captureStarted)
		m_rsDevice->StopCapture();
	m_captureStarted = false;
}
void CustomCalibration::ConvertYUY2ToRGBA(const uint8_t* image, int width, int height,
	uint8_t* output)
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
		RenderText(-3, 0.75, GLUT_BITMAP_TIMES_ROMAN_24, serial.c_str(), color);
		glutSwapBuffers();
	}
	void CustomCalibration::OnIdle(void)
	{ }
	void CustomCalibration::OnKeyBoard(unsigned char key, int x, int y)
	{
		switch (tolower(key))
		{
		case 'q':
		case 27: //ESC
			if (m_captureStarted)
			{
				m_rsDevice->StopCapture();
			}
			glutLeaveMainLoop();
			break;
		case 13: //Enter
			m_imagesCapture = true;
			break;
		}
	}
	void CustomCalibration::OnClose(void)
	{
		if (m_captureStarted)
			m_rsDevice->StopCapture();
		m_captureStarted = false;
	}
	void CustomCalibration::ConvertYUY2ToRGBA(const uint8_t* image, int width, int height,
		uint8_t* output)
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
			{
				int nStrLengthPixels = 0;
				for (char *p = (char*)text; *p; p++)
				{
					if (*p == '\n') break;
					nStrLengthPixels += glutBitmapWidth(font, *p);
				}
				if (x == -3)
					x0 = w - nStrLengthPixels - 20;
				else
					x0 = (w - nStrLengthPixels) / 2;
			}
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, +1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glColor4ub(color.R, color.G, color.B, color.A);
			glRasterPos2f(x0, y0);
			glutBitmapString(font, (const unsigned char*)text);
			// Restore GL state to what it was prior to this call
			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glPopAttrib();
		}
