#include "stdafx.h"
#include "vtkWriter.h"
using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;
void SaveFile(PointCloud<PointXYZ>*);
int main() try {
	Device realSense;
	DrawWindows win(1280, 960, "Your Face", realSense.ctx.get_device_count() * 2);
	win.init(realSense.dev, realSense.devices);

	cout << "리얼센스 활성화 중..." << endl;

	/*
	TODO
	1. 앞/좌/우면을 위한 cloud 3개 생성하기
	*/

	FrontEndPoint FrontEndPoints(realSense.dev);
	RightEndPoint RightEndPoints(realSense.dev);
	LeftEndPoint LeftEndPoints(realSense.dev);

	std::cout << "Capture Depth Image... " << std::endl;
	do {
		///depth 이미지 촬영
		FrontEndPoints.initPoint();
		rs::intrinsics depth_intrin = FrontEndPoints.getDepthImage();
		FrontEndPoints.setResolution(depth_intrin.width, depth_intrin.height);
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

	return EXIT_SUCCESS;
}
catch (const rs::error & e)
{
	// Method calls against librealsense objects may throw exceptions of type rs::error
	printf("rs::error was thrown when calling %s(%s):\n", e.get_failed_function().c_str(), e.get_failed_args().c_str());
	printf("    %s\n", e.what());
	return EXIT_FAILURE;
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