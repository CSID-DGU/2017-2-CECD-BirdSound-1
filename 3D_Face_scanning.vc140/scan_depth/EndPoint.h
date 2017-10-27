#pragma once

#include "stdafx.h"
using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;
//TODO:
// index 0을 넘어 설경우 처리 
class EndPoint {
public:
	PointCloud<PointXYZ> *cloud;
	int width, height;
	int Img_CenterPoint;
	int  W, E, S, N, WE_MidPoint;

	const rs::float3 *points;
	device * dev;

	EndPoint() {
		initPoint();
	}
	void initPoint() {
		W = -1;
		E = -1;
		N = -1;
		S = -1;
		Img_CenterPoint = -1;
		WE_MidPoint = -1;
	}
	void setOriginPoints(device * a_dev) {
		dev = a_dev;
	}
	void setCloud(PointCloud<PointXYZ> *a_cloud) {
		cloud = a_cloud;

		setPosition('C', cloud->width*cloud->height / 2 + cloud->width / 2);

	}
	rs::intrinsics getDepthImage() {
		dev->wait_for_frames();
		rs::intrinsics depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
		auto Points = reinterpret_cast<const rs::float3 *>(dev->get_frame_data(rs::stream::points));
		points = Points;
		return depth_intrin;
	}
	void setResolution(int a_width, int a_height) {
		width = a_width;
		height = a_height;
	}
	void setPosition(char direction, int a_pos) {
		switch (direction) {
		case 'W':
		case 'w':
			W = a_pos;
			std::cout << " End Point W is set" << std::endl;
			break;

		case 'E':
		case 'e':
			E = a_pos;
			std::cout << " End Point E is set" << std::endl;
			break;

		case 'S':
		case 's':
			S = a_pos;
			std::cout << " End Point S is set" << std::endl;
			break;

		case 'N':
		case 'n':
			N = a_pos;
			std::cout << " End Point N is set" << std::endl;
			break;
		case 'M':
		case 'm':
			WE_MidPoint = (W + E) / 2;
			std::cout << " Mid Point is set" << std::endl;
			break;
		case 'C':
		case 'c':
			Img_CenterPoint = cloud->width*cloud->height / 2 + cloud->width / 2;
			std::cout << " Center Point is set" << std::endl;
			break;
		default:
			ErrorPrint(1);
			std::cout << "[ Error ] : Undefined character " << std::endl;
			break;
		}
	}
	bool isRightEndPointPosition();
	void ErrorPrint(int number) {
		std::cout << "[ Error ] : ";
		switch (number) {
		case 1:
			std::cout << "Undefined character Check 'EndPoint::setPosition()' " << std::endl;
			break;

		}
	}

};

bool EndPoint::isRightEndPointPosition() {
	printf("%d %d\n", cloud->points.size(), Img_CenterPoint);
	for (int i = 0; i < cloud->width / 2; i++) {	//West
		int idx = Img_CenterPoint - i;
		int flag = 0;
		if (points[idx].x == 0.0) {
			flag = 1;
			for (int c = 0; c < 4; c++) {
				if (points[idx - c].x != 0.0) {
					flag = 0;
				}
			}
			if (flag == 1) {
				setPosition('W', idx);
				break;
			}
		}
	}
	for (int i = 0; i < cloud->width / 2; i++) { //east
		int idx = Img_CenterPoint + i;
		int flag = 0;
		if (points[idx].x == 0.0) {
			flag = 1;
			for (int c = 0; c < 4; c++) {
				if (points[idx + c].x != 0.0) {
					flag = 0;
				}
			}
			if (flag == 1) {
				setPosition('E', idx);
				break;
			}
		}
	}
	setPosition('M', NULL);
	for (int i = 0; i < cloud->height / 2; i++) { //north
		int idx = WE_MidPoint - (i * cloud->width);
		int flag = 0;
		if (points[idx].x == 0.0) {
			flag = 1;
			for (int c = 0; c < 4; c++) {
				if (points[idx - (c * cloud->width)].x != 0.0) {
					flag = 0;
				}
			}
			if (flag == 1) {
				setPosition('N', idx);
				break;
			}
		}
	}
	for (int i = 0; i < cloud->height / 2; i++) { //south
		int idx = WE_MidPoint + (i * cloud->width);
		int flag = 0;
		if (points[idx].x == 0.0) {
			flag = 1;
			for (int c = 0; c < 4; c++) {
				if (points[idx + (c * cloud->width)].x != 0.0) {
					flag = 0;
				}
			}
			if (flag == 1) {
				setPosition('S', idx);
				break;
			}
		}
	}
	std::cout << " W : " << W << " E : " << E << " N : " << N << " S : " << S << std::endl;
	std::cout << " E-W : " << E - W << " S-N : " << (S / cloud->width) - (E / cloud->width) << std::endl;

	if (W!= -1 && E != -1 && S != -1 && N != -1 && S != N) { // 초기값을 구하고 상단점과 하단점을 구했을 경우 
		if (1.1 > (E - W) / ((S / cloud->width) - (E / cloud->width)) && (E - W) / ((S / cloud->width) - (E / cloud->width)) > 0.9) {
			return false;
		}
	}
	return true;
};