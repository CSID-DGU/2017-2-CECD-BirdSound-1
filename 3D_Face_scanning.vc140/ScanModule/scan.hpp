#ifndef DEVICE_H
#define DEVICE_H
#define MAX_CAM_NUM 3
#define MIN_CAM_NUM 0
//If you don't have opencv, disable below
#define OPENCV_MODULE

//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
#include "common.h"
#include "libRealsense2\rs.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <sstream>
#include <map>
#include <vtkPoints.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyle.h>
#include <vtkSphereSource.h>
#include <vtkSTLWriter.h>
#include <vtkOBJExporter.h>
#ifdef OPENCV_MODULE
#include <opencv2\opencv.hpp>
#endif // OPENCV_MODULE

using namespace std;

class Realsense {

	enum class filetype { stl, obj };
	struct camUnit
	{
		std::map<int, rs2::frame> frames_per_stream;
		rs2::pipeline pipe;
		rs2::pipeline_profile profile;
	};

	size_t deviceCount = NULL;
	rs2::device_list deviceList;
	std::map <int, camUnit> camMap;

public:
	enum class streamType { color, depth, infrared_left, infrared_right };
	enum class streamFormat {

		RS2_FORMAT_Z16, /**< 16-bit linear depth values. The depth is meters is equal to depth scale * pixel value. */
		RS2_FORMAT_DISPARITY16, /**< 16-bit linear disparity values. The depth in meters is equal to depth scale / pixel value. */
		RS2_FORMAT_DISPARITY32, /**< 32-bit float-point disparity values. Depth->Disparity conversion : Disparity = Baseline*FocalLength/Depth */

		RS2_FORMAT_RGB8, /**< 8-bit red, green and blue channels */
		RS2_FORMAT_BGR8, /**< 8-bit blue, green, and red channels -- suitable for OpenCV */
		RS2_FORMAT_RGBA8, /**< 8-bit red, green and blue channels + constant alpha channel equal to FF */
		RS2_FORMAT_BGRA8, /**< 8-bit blue, green, and red channels + constant alpha channel equal to FF */

		RS2_FORMAT_Y8, /**< 8-bit per-pixel grayscale image */
		RS2_FORMAT_Y16, /**< 16-bit per-pixel grayscale image */

		RS2_FORMAT_RAW10, /**< Four 10-bit luminance values encoded into a 5-byte macropixel */
		RS2_FORMAT_RAW16, /**< 16-bit raw image */
		RS2_FORMAT_RAW8, /**< 8-bit raw image */


		RS2_FORMAT_YUYV, /**< Standard YUV pixel format as described in https://en.wikipedia.org/wiki/YUV */
		RS2_FORMAT_UYVY, /**< Similar to the standard YUYV pixel format, but packed in a different order */

		RS2_FORMAT_XYZ32F, /**< 32-bit floating point 3D coordinates. */
		RS2_FORMAT_GPIO_RAW, /**< Raw data from the external sensors hooked to one of the GPIO's */
		RS2_FORMAT_COUNT             /**< Number of enumeration values. Not a valid input: intended to be used in for-loops. */
	};

	void camInit();
	void camInfo(int);
	void startStreaming(int devNum, streamType streamType);
	void startStreaming(int devNum, streamFormat streamFormat, streamType streamType);
	void stopStreaming(int devNum, streamType streamType);
	rs2::frame Realsense::capture(int devNum, int streamType, int restNum = 10);
	std::vector<rs2::frame> Realsense::capture(int devNum, int streamType, int frameNum, int restNum = 10);
	std::string Realsense::saveImage(rs2::frame &frame, string filepath, int filetype);
	vtkPoints* Realsense::frameToVtkPoints(rs2::frame &frame);
	/*1이면 stl 2면 obj로 저장*/
	void MeshConstruct(vtkPoints *points, int saveType = 3);

private:
	bool isInit();
	void restFrame(unit &cam_unit, int num);

private:
	const double INF = 9999999999999;
	const int height = 720;
	const int width = 1280;
	double getDistane(double *src, double *tar);
};

namespace RS400 {
	cv::Mat frameToMat(const rs2::frame& f);

	class RS400 : public Realsense {
	public:
		cv::Mat frameToMat(const rs2::frame& f);

	};
}

#endif