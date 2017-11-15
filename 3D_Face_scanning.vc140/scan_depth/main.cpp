#include "stdafx.h"
#include "vtkWriter.h"
#include "Device.h"

using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;
void SaveFile(PointCloud<PointXYZ>*);

int main() try {
	Device realSense;
	realSense.start();
	DrawWindows win(1280, 960, "Your Face", realSense.ctx.get_device_count() * 2);
	win.init(realSense.dev, realSense.devices);

	cout << "Realsense 촬영중입니다" << endl;

	FrontEndPoint FrontEndPoints;
	RightEndPoint RightEndPoints;
	LeftEndPoint LeftEndPoints;

	
	std::cout << "Capture Depth Image... " << std::endl;
	do {
		///depth 이미지 촬영
		FrontEndPoints.initPoint();
		realSense.capture();
		FrontEndPoints.points = realSense.get_depth_points_array();
		FrontEndPoints.setResolution(realSense.depth_intrin.width, realSense.depth_intrin.height);
	} while (FrontEndPoints.isRightEndPointPosition() == true);
	std::cout << "Depth Image is Captured \n\n";

	std::cout << "\nResize the Depth Image..." << std::endl;
	int Width = FrontEndPoints.Width;
	int Height = FrontEndPoints.Height;
	int subWidth = FrontEndPoints.E.Idx - FrontEndPoints.W.Idx;
	int subHeight = FrontEndPoints.S.Row - FrontEndPoints.N.Row;
	PointCloud<PointXYZ> cloud;
	cloud.width = subWidth;
	cloud.height = subHeight;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);

	int newindex = 0;
	for (int i = FrontEndPoints.N.Row; i < FrontEndPoints.S.Row; i++){
		int idx = FrontEndPoints.W.Col + i*Width;
		for (int j = 0; j < subWidth; j++) {
			if (FrontEndPoints.points[idx + j].z <= FrontEndPoints.points[FrontEndPoints.B.Idx].z) {
				cloud.points[newindex].x = -FrontEndPoints.points[idx + j].x;
				cloud.points[newindex].y = -FrontEndPoints.points[idx + j].y;
				cloud.points[newindex].z = -FrontEndPoints.points[idx + j].z;
			}
			++newindex;
		}
	}
	std::cout << "Depth Image is Resized points["<<newindex<<"]\n" <<  std::endl;

	/*
	RightEndPoint,LeftEndPoint도 Front랑 같은 코드로 구현하면 됨
	*/
	
	pcl::visualization::CloudViewer viewer("PCL Viewer");
	viewer.showCloud(cloud.makeShared());
	while (!viewer.wasStopped());

	SaveFile(&cloud);
	realSense.save_image_file("filename.bmp", BMP);
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