#include "stdafx.h"
#include "vtkWriter.h"
#include "Device.h"

using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;

int main() try {

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCLPointCloud2 cloud_blob;
	cout << "PCD 파일경로를 입력해주세요.." << endl;
	string filePath; getline(std::cin, filePath);
	cout << "파일을 로딩합니다.." << endl;
	pcl::io::loadPCDFile(filePath, cloud_blob);
	cout << "파일로딩 끝!" << endl;
	pcl::fromPCLPointCloud2(cloud_blob, *cloud);

	PointCloud<PointXYZ> cloud2 = *cloud;
	cloud2.width = cloud->width;
	cloud2.height = cloud->height;
	cloud2.is_dense = false;
	cloud2.points.resize(cloud2.width*cloud2.height);
	cout << cloud2.width << endl;
	cout << cloud2.height << endl;
	
	pcl::visualization::CloudViewer viewer("PCL Viewer");
	viewer.showCloud(cloud2.makeShared());
	while (!viewer.wasStopped());
	
	std::string result_name;
	cout << "vtk 파일이름(확장자 제외) >>" << endl;
	std::cin >> result_name;

	vtkWriter fout(result_name+".vtk", &cloud2);
	cout << "File is saved." << endl;
	return EXIT_SUCCESS;
}
catch (const rs::error & e)
{
	// Method calls against librealsense objects may throw exceptions of type rs::error
	printf("rs::error was thrown when calling %s(%s):\n", e.get_failed_function().c_str(), e.get_failed_args().c_str());
	printf("    %s\n", e.what());
	return EXIT_FAILURE;
}