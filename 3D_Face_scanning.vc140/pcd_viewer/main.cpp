#include "stdafx.h"


using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;

int main(){
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCLPointCloud2 cloud_blob; 
	cout << "PCD 파일경로를 입력해주세요.." << endl;
	string filePath; getline(std::cin, filePath);
	cout << "파일을 로딩합니다.." << endl;
	pcl::io::loadPCDFile(filePath, cloud_blob);
	cout << "파일로딩 끝!" << endl;
	pcl::fromPCLPointCloud2(cloud_blob, *cloud);

	pcl::visualization::CloudViewer viewer("PCL Viewer");
	viewer.showCloud(cloud->makeShared());
	while (!viewer.wasStopped());
	return (0);
}
