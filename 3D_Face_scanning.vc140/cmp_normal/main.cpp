#include "stdafx.h"

using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;

int main(){
	clock_t begin, end;

	// Load input file into a PointCloud<T> with an appropriate type
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCLPointCloud2 cloud_blob;
	cout << "PCD 파일경로를 입력해주세요.." << endl;
	string filePath; getline(std::cin, filePath);
	cout << "파일을 로딩합니다.." << endl;
	pcl::io::loadPCDFile(filePath, cloud_blob);
	cout << "파일로딩 끝!" << endl;
	pcl::fromPCLPointCloud2(cloud_blob, *cloud);
	//* the data should be available in cloud

	// Normal estimation*
	cout << "*** Step1. Normal Estimation***" << endl << endl;;
	

	//search method1
	cout << "Method 0 : Octree(16.0 resolution) - radius(0.03)" << endl;
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	ne.setInputCloud(cloud);
	begin = clock();
	float resolution = 16.0f;
	pcl::search::Octree<pcl::PointXYZ>::Ptr octree(new pcl::search::Octree<pcl::PointXYZ>(resolution));
	ne.setSearchMethod(octree);
	ne.setRadiusSearch(0.03);
	ne.compute(*normals);
	end = clock();
	cout << "Done.. 수행시간 : " << ((end - begin) / CLOCKS_PER_SEC) << endl << endl;

	cout << "Method 1 : Octree(16.0 resolution) - k-neighborhood(10)" << endl;
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne1;
	pcl::PointCloud<pcl::Normal>::Ptr normals1(new pcl::PointCloud<pcl::Normal>);
	ne1.setInputCloud(cloud);
	begin = clock();
	octree->setInputCloud(cloud);
	ne1.setInputCloud(cloud);
	ne1.setSearchMethod(octree);
	ne1.setKSearch(10);
	ne1.compute(*normals1);
	end = clock();
	cout << "Done.. 수행시간 : " << ((end - begin) / CLOCKS_PER_SEC) << endl << endl;


	//search method2
	cout << "Method 2 : Kdtree - radius(0.03)" << endl;
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne2;
	pcl::PointCloud<pcl::Normal>::Ptr normals2(new pcl::PointCloud<pcl::Normal>);
	ne2.setInputCloud(cloud);
	begin = clock();
	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
	ne2.setSearchMethod(kdtree);
	ne2.setRadiusSearch(0.03);
	ne2.compute(*normals2);
	end = clock();
	cout << "Done.. 수행시간 : " << ((end - begin) / CLOCKS_PER_SEC) << endl << endl;

	cout << "Method 3 : Kdtree - k-neighborhood(10)" << endl;
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne3;
	pcl::PointCloud<pcl::Normal>::Ptr normals3(new pcl::PointCloud<pcl::Normal>);
	ne3.setInputCloud(cloud);
	begin = clock();
	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree2(new pcl::search::KdTree<pcl::PointXYZ>);
	kdtree2->setInputCloud(cloud);
	ne3.setInputCloud(cloud);
	ne3.setSearchMethod(kdtree2);
	ne3.setKSearch(10);
	ne3.compute(*normals3);
	end = clock();
	cout << "Done.. 수행시간 : " << ((end - begin) / CLOCKS_PER_SEC) << endl << endl;

	cout << "Finished." << endl;
	return (0);
}