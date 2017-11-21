/**
전체 Depth를 스캔 후, PCD 파일로 저장하는 프로그램입니다.
*/
#include "stdafx.h"
#include "Device.h"
#include "DrawWindow.h"

using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;

int main() try {
	PointCloud<PointXYZ> cloud;
	Device realSense;
	realSense.start();
	DrawWindows win(1280, 960, "Your Face", realSense.ctx.get_device_count() * 2);
	win.init(realSense.dev, realSense.devices);

	cout << "Capture Depth Image... " << endl;
	realSense.capture();
	cout << "Done." << endl;


	auto points = realSense.get_depth_points_array();
	cloud.width = realSense.depth_intrin.width;
	cloud.height = realSense.depth_intrin.height;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);
	cout << "Converting to PCL..." << endl;

	for (size_t i = 0; i < cloud.points.size(); ++i) {
		cloud.points[i].x = -points->x;
		cloud.points[i].y = -points->y;
		cloud.points[i].z = -points->z;
		++points;
	}

	string result_name;
	cout << "파일이름(확장자 제외) >>" << endl;
	std::cin >> result_name;
	cout << "저장중..." << endl;
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