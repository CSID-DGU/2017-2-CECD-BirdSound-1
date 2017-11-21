#include "stdafx.h"
#include "vtkWriter.h"
#include "Device.h"

using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;
void SaveFile(PointCloud<PointXYZ>*);

int main() try {
	PointCloud<PointXYZ> cloud;
	Device realSense;
	realSense.start();
	DrawWindows win(1280, 960, "Your Face", realSense.ctx.get_device_count() * 2);
	win.init(realSense.dev, realSense.devices);

	cout << "Realsense 촬영중입니다" << endl;

	FrontEndPoint FrontEndPoints;
	RightEndPoint RightEndPoints;
	LeftEndPoint LeftEndPoints;

	realSense.capture();
	std::cout << "Capture Depth Image... " << std::endl;


	auto points = realSense.get_depth_points_array();

	cloud.width = realSense.depth_intrin.width;
	cloud.height = realSense.depth_intrin.height;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);
	cout << "PCL 로 변환중..." << endl;

	for (size_t i = 0; i < cloud.points.size(); ++i) {
		cloud.points[i].x = -points->x;
		cloud.points[i].y = -points->y;
		cloud.points[i].z = -points->z;
		++points;
	}
	string result_name;
	cout << "파일이름>>" << endl;
	
	std::cin >> result_name;
	cout << "저장중" << endl;
	savePCDFileASCII(result_name + ".pcd", cloud);
	
	cout << "저장완료" << endl;

	pcl::visualization::CloudViewer viewer("PCL Viewer");
	viewer.showCloud(cloud.makeShared());

	while (!viewer.wasStopped());

	return EXIT_SUCCESS;
}
catch (const rs::error & e)
{
	// Method calls against librealsense objects may throw exceptions of type rs::error
	printf("rs::error was thrown when calling %s(%s):\n", e.get_failed_function().c_str(), e.get_failed_args().c_str());
	printf("    %s\n", e.what());
	return EXIT_FAILURE;
}
void textureSave(rs::intrinsics color_intrin, rs::extrinsics depth_to_color, rs::intrinsics depth_intrin, const uint16_t * depth_image, const uint8_t * color_image, float scale) {
	string filename = "test.texture";
	std::ofstream fout(filename);
	
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
}
void SaveFile(PointCloud<PointXYZ> *cloud) {
	string Output;
	cout << "\nOutput Filename(.vtk |.pcd)  If you don't want to save, Input \"skip\".\n > "; cin >> Output;
	if (Output.length() >= 4) {
		string extenstion = Output.substr(Output.length() - 4, Output.length());
		if (extenstion == ".pcd"&& Output.length()>4) {
			savePCDFileASCII(Output, *cloud);
			cout << "File is saved." << endl;
		}
		else if (extenstion == ".vtk"&& Output.length()>4) {
			vtkWriter fout(Output, cloud);
			cout << "File is saved." << endl;
		}
		else if (extenstion == "skip") {
			cout << "Skipped" << endl;
		}
		else {
			std::cout << "[Error] Input right fileName" << std::endl;
		}
	}
	else {
		std::cout << "[Error] Input right fileName" << std::endl;
	}
}