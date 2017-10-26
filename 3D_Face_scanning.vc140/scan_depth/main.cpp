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

	int center_point = cloud.width*cloud.height / 2 + cloud.width / 2;

	printf("%d %d", cloud.points.size(), center_point);

	int w, e, n, s, we_center;
	for (int i = 0; i < cloud.width / 2; i++) {	//West
		int idx = center_point - i;
		int flag = 0;
		if (points[idx].x == 0.0) {
			flag = 1;
			for (int c = 0; c < 4; c++) {
				if (points[idx - c].x != 0.0) {
					flag = 0;
				}
			}
			if (flag == 1) {
				w = idx;
				printf("W\n");
				break;
			}
		}
	}
	for (int i = 0; i < cloud.width / 2; i++) { //east
		int idx = center_point + i;
		int flag = 0;
		if (points[idx].x == 0.0) {
			flag = 1;
			for (int c = 0; c < 4; c++) {
				if (points[idx + c].x != 0.0) {
					flag = 0;
				}
			}
			if (flag == 1) {
				e = idx;
				printf("E\n");
				break;
			}
		}
	}
	we_center = (w + e) / 2;
	for (int i = 0; i < cloud.height / 2; i++) { //north
		int idx = we_center - (i * cloud.width);
		int flag = 0;
		if (points[idx].x == 0.0) {
			flag = 1;
			for (int c = 0; c < 4; c++) {
				if (points[idx - (c * cloud.width)].x != 0.0) {
					flag = 0;
				}
			}
			if (flag == 1) {
				n = idx;
				printf("N\n");
				break;
			}
		}
	}
	for (int i = 0; i < cloud.height / 2; i++) { //south
		int idx = we_center + (i * cloud.width);
		int flag = 0;
		if (points[idx].x == 0.0) {
			flag = 1;
			for (int c = 0; c < 4; c++) {
				if (points[idx + (c * cloud.width)].x != 0.0) {
					flag = 0;

				}
			}

			if (flag == 1) {
				s = idx;
				printf("S\n");
				break;
			}
		}
	}
	for (int row = 0; row < center_point; row += cloud.width) {
		for (int i = n - (e - w) / 2 + row; i < n + (e - w) / 2 + row; i++) {
			int idx = i;
			cloud.points[idx].x = -2 * points[idx].x;
			cloud.points[idx].y = -2 * points[idx].y;
			cloud.points[idx].z = -2 * points[idx].z;
		}
	}
	for (size_t i = w; i < e; i++) {
		//cloud.points[i].x = -points[i].x;
		//cloud.points[i].y = -points[i].y;
		//cloud.points[i].z = -points[i].z;
		printf("\n%f %f %f", cloud.points[i].x, cloud.points[i].y, cloud.points[i].z);
	}
	++points;

	cout << "파일로 저장 중..." << endl;
	//savePCDFileASCII("test_pcd.pcd", cloud);
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
