#include "stdafx.h"


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
	cout << "리얼센스 활성화 완료" << endl;
	cout << "촬영합니다! 김치!!!!" << endl;
	dev->wait_for_frames();
	cout << "촬영일자 : " << dev->get_frame_timestamp(rs::stream::depth) << endl;


	rs::intrinsics depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
	auto points = reinterpret_cast<const rs::float3 *>(dev->get_frame_data(rs::stream::points));

	cloud.width = depth_intrin.width;
	cloud.height = depth_intrin.height;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);
	cout << "PCL 로 변환중..." << endl;

	for (size_t i = 0; i < cloud.points.size(); ++i) {

		if (-points->z == 0)continue;

		cloud.points[i].x = -points->x;
		cloud.points[i].y = -points->y;
		cloud.points[i].z = -points->z;
		++points;
	} 

	cout << "파일로 저장 중..." << endl;
	//savePCDFileASCII("test_pcd.pcd", cloud);
	cout << "저장완료" << endl;

	pcl::visualization::CloudViewer viewer("PCL Viewer");
	std::cout << "Where Die";
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