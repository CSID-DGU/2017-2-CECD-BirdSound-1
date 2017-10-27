#include "stdafx.h"
#include "EndPoint.h"
using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;
int main() try {
	PointCloud<PointXYZ> cloud;
	context ctx;
	device * dev = ctx.get_device(0);
	cout << "리얼센스 활성화 중..." << endl;
	dev->enable_stream(rs::stream::depth, rs::preset::best_quality);
	dev->start();

	EndPoint EndPoints;


	EndPoints.setOriginPoints(dev);
	do {
		///depth 이미지 촬영
		EndPoints.initPoint();
		//cout << "리얼센스 활성화 완료" << endl;
		//cout << "촬영합니다! 김치!!!!" << endl;
		//cout << "촬영일자 : " << dev->get_frame_timestamp(rs::stream::depth) << endl;
		rs::intrinsics depth_intrin = EndPoints.getDepthImage();


		cloud.width = depth_intrin.width;
		cloud.height = depth_intrin.height;
		cloud.is_dense = false;
		cloud.points.resize(cloud.width * cloud.height);
		EndPoints.setCloud(&cloud);
		//cout << "PCL 로 변환중..." << endl;
		std::cout << "\n\n";

	} while (EndPoints.isRightEndPointPosition() == true);

	for (int row = 0; row < EndPoints.Img_CenterPoint; row += cloud.width) {
		for (int i = EndPoints.N - (EndPoints.E - EndPoints.W) / 2 + row; i < EndPoints.N + (EndPoints.E - EndPoints.W) / 2 + row; i++) {
			int idx = i;
			cloud.points[idx].x = -2 * EndPoints.points[idx].x;
			cloud.points[idx].y = -2 * EndPoints.points[idx].y;
			cloud.points[idx].z = -2 * EndPoints.points[idx].z;
		}
	}


	//cout << "파일로 저장 중..." << endl; savePCDFileASCII("test_pcd.pcd", cloud); 	cout << "저장완료" << endl;

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
