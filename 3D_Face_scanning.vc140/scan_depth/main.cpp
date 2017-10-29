#include "stdafx.h"
#include "EndPoint.h"
#include"DrawWindow.h"
//#include"Neural.h"
#include"Device.h"

using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;
int main() try {
	Device realSense;
	PointCloud<PointXYZ> cloud;
	DrawWindows win(1280, 960, "Your Face", realSense.ctx.get_device_count() * 2);
	win.init(realSense.dev, realSense.devices);

	cout << "리얼센스 활성화 중..." << endl;

	EndPoint EndPoints;
	EndPoints.setOriginPoints(realSense.dev);
	do {
		///depth 이미지 촬영
		EndPoints.initPoint();
		rs::intrinsics depth_intrin = EndPoints.getDepthImage();


		cloud.width = depth_intrin.width;
		cloud.height = depth_intrin.height;
		cloud.is_dense = false;
		cloud.points.resize(cloud.width * cloud.height);
		EndPoints.setCloud(&cloud);
		//cout << "PCL 로 변환중..." << endl;
		std::cout << "\n\n";

	} while (EndPoints.isRightEndPointPosition() == true);


	for (int row = 0; row < EndPoints.Img_CenterPoint.Idx; row += cloud.width) 
	{
		for (int i = EndPoints.N.Idx - (EndPoints.E.Idx - EndPoints.W.Idx) / 2 + row; i < EndPoints.N.Idx + (EndPoints.E.Idx - EndPoints.W.Idx) / 2 + row; i++) {
			int idx = i;
			cloud.points[idx].x = -2 * EndPoints.points[idx].x;
			cloud.points[idx].y = -2 * EndPoints.points[idx].y;
			cloud.points[idx].z = -2 * EndPoints.points[idx].z;
		}
	}

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
