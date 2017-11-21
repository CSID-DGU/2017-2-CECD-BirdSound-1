#include "stdafx.h"
#include "vtkWriter.h"
#include "Device.h"

using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;

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
	for (int i = FrontEndPoints.N.Row; i < FrontEndPoints.S.Row; i++) {
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
	std::cout << "Depth Image is Resized points[" << newindex << "]\n" << std::endl;

	/*
	RightEndPoint,LeftEndPoint도 Front랑 같은 코드로 구현하면 됨
	*/

	pcl::visualization::CloudViewer viewer("PCL Viewer");
	viewer.showCloud(cloud.makeShared());
	while (!viewer.wasStopped());

	string result_name;
	cout << "파일이름(확장자 제외) >>" << endl;
	std::cin >> result_name;
	cout << "저장중..." << endl;
	savePCDFileASCII(result_name + ".pcd", cloud);
	cout << "저장완료" << endl;
	return EXIT_SUCCESS;
}
catch (const rs::error & e)
{
	// Method calls against librealsense objects may throw exceptions of type rs::error
	printf("rs::error was thrown when calling %s(%s):\n", e.get_failed_function().c_str(), e.get_failed_args().c_str());
	printf("    %s\n", e.what());
	return EXIT_FAILURE;
}