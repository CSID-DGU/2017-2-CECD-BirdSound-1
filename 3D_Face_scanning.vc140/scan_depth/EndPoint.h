#pragma once

#include "stdafx.h"
using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;
//TODO:
// index 0을 넘어 설경우 처리 
class Pos {
public:
	int Row;
	int Col;
	int Idx;

	void toString() {
		std::cout<<"(" << Row << ", " << Col << ")";
	};
}typedef Pos;

class EndPoint {
public:	
	PointCloud<PointXYZ> *cloud;
	int width, height;
	Pos Img_CenterPoint, WE_MidPoint;
	Pos  W, E, S, N;
	const rs::float3 *points;
	device * dev;

	EndPoint() {
		initPoint();
	}
	void initPoint() {
		W.Row = -1; 	W.Col = -1; 	W.Idx = -1;
		E.Row = -1;		E.Col = -1;		E.Idx = -1;
		N.Row = -1;		N.Col = -1;		N.Idx = -1;
		S.Row = -1;		S.Col = -1;		S.Idx = -1;
		Img_CenterPoint.Row = -1;	Img_CenterPoint.Col = -1;	Img_CenterPoint.Idx = -1;
		WE_MidPoint.Row = -1;		WE_MidPoint.Col = -1;		WE_MidPoint.Idx = -1;
	}
	void setOriginPoints(device * a_dev) {
		dev = a_dev;
	}
	void setCloud(PointCloud<PointXYZ> *a_cloud) {
		cloud = a_cloud;
		width = cloud->width;
		height = cloud->height;

		Img_CenterPoint.Col = cloud->width / 2;
		Img_CenterPoint.Row = cloud->height / 2;
		Img_CenterPoint.Idx = cloud->width*cloud->height / 2 + cloud->width / 2;

		std::cout << " Center Point is set" << std::endl;
	}
	rs::intrinsics getDepthImage() {
		dev->wait_for_frames();
		rs::intrinsics depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
		auto Points = reinterpret_cast<const rs::float3 *>(dev->get_frame_data(rs::stream::points));
		points = Points;
		return depth_intrin;
	}
	void ErrorPrint(int number) {
		std::cout << "[ Error ] : ";
		switch (number) {
		case 1:
			std::cout << "Undefined character Check 'EndPoint::setPosition()' " << std::endl;
			break;

		}
	}
	void setPosition(char direction, int a_pos) {
		switch (direction) {
		case 'W':
		case 'w':
			W.Idx = a_pos;
			W.Row = getRow(W.Idx);
			W.Col = getCol(W.Idx);
			std::cout << " End Point W is set" << std::endl;
			break;

		case 'E':
		case 'e':
			E.Idx = a_pos;
			E.Row = getRow(E.Idx);
			E.Col = getCol(E.Idx);
			std::cout << " End Point E is set" << std::endl;
			break;

		case 'S':
		case 's':
			S.Idx = a_pos;
			S.Row = getRow(S.Idx);
			S.Col = getCol(S.Idx);
			std::cout << " End Point S is set" << std::endl;
			break;

		case 'N':
		case 'n':
			N.Idx = a_pos;
			N.Row = getRow(N.Idx);
			N.Col = getCol(N.Idx);
			std::cout << " End Point N is set" << std::endl;
			break;
		case 'M':
		case 'm':
			WE_MidPoint.Idx = a_pos;
			WE_MidPoint.Row = getRow(WE_MidPoint.Idx);
			WE_MidPoint.Col = getCol(WE_MidPoint.Idx);
			std::cout << " Mid Point is set" << std::endl;
			break;
		default:
			ErrorPrint(1);
			std::cout << "[ Error ] : Undefined character " << std::endl;
			break;
		}
	}

	virtual int getEastEndPointPosition() = NULL;
	virtual int getWestEndPointPosition() = NULL;
	virtual int getSouthEndPointPosition() = NULL;
	virtual int getNorthEndPointPosition() = NULL;

	int getRow(int idx) {
		return (idx + 1) / width;
	}
	int getCol(int Idx) {
		return Idx % width;
	}
};

class FrontEndPoint : public EndPoint{
public:
	int getEastEndPointPosition() {
		int idx = 0;
		int flag = 0;
		for (int i = 0; i < cloud->width / 2; i++) { //east
			idx = Img_CenterPoint.Idx + i;
			flag = 0;
			if (points[idx].x == 0.0) {
				flag = 1;
				for (int c = 0; c < 3; c++) {
					if (points[idx + c].x != 0.0) {
						flag = 0;
					}
				}
				if (flag == 1) {
					return idx + 5;
					break;
				}
			}
		}
	}
	int getWestEndPointPosition() {
		int idx = 0;
		int flag = 0;
		for (int i = 0; i < cloud->width / 2; i++) {	//West
			idx = Img_CenterPoint.Idx - i;
			flag = 0;
			if (points[idx].x == 0.0) {
				flag = 1;
				for (int c = 0; c < 3; c++) {
					if (points[idx - c].x != 0.0) {
						flag = 0;
					}
				}
				if (flag == 1) {
					return idx;
					break;
				}
			}
		}
	}

	int getNorthEndPointPosition() {
		int idx = 0;
		int flag = 0;
		for (int i = 0; i < cloud->height / 2; i++) { //north
			if ((WE_MidPoint.Idx - (i * cloud->width)) > 0) {
				idx = WE_MidPoint.Idx - (i * cloud->width);
				flag = 0;
				if (points[idx].x == 0.0) {
					flag = 1;
					for (int c = 0; c < 3; c++) {
						if (points[idx - (c * cloud->width)].z != 0.0) {
							flag = 0;
						}
					}
					if (flag == 1) {
						return idx + cloud->width;
						break;
					}
				}
			}
			else {
				std::cout << "얼굴이 너무 위로올라 갔습니다.\n" << std::endl;
				exit(1);
			}
		}
	}
	int getSouthEndPointPosition() {
		int idx = 0;
		int flag = 0;

		double prev = 0;
		double gradient = 0;
		for (int i = 0; i < cloud->height / 2; i++) { //south
			idx = WE_MidPoint.Idx + (i * cloud->width);
			flag = 0;
			if (points[idx].x == 0.0) {
				flag = 1;
				for (int c = 0; c < 3; c++) {
					if (points[idx + (c * cloud->width)].x != 0.0) {
						flag = 0;
					}
				}
				if (flag == 1) {
					return idx + 4 * cloud->width;
					break;
				}
			}
		}
	}
	bool isRightEndPointPosition() {
		setPosition('E', getEastEndPointPosition());
		setPosition('W', getWestEndPointPosition());

		setPosition('M', NULL);
		setPosition('N', getNorthEndPointPosition());
		setPosition('S', getSouthEndPointPosition());
		//setPosition('S', WE_MidPoint.Idx+1);

		std::cout << " W : "; W.toString();
		std::cout << " E : "; E.toString();
		std::cout << " N : "; N.toString();
		std::cout << " S : "; S.toString();
		std::cout << "\n";

		std::cout << " E-W : " << E.Col - W.Col << " S-N : " << (S.Row - N.Row) << std::endl;

		if (W.Idx != -1 && E.Idx != -1 && S.Idx != -1 && N.Idx != -1 && S.Idx != N.Idx) { // 초기값을 구하고 상단점과 하단점을 구했을 경우 
			double ratio = ((double)S.Row - N.Row) / ((double)E.Col - W.Col);
			std::cout << "Width / Height ratio : " << ratio << std::endl;
			if (2.0 > ratio && ratio >= 1.0) {
				return false;
			}
		}
		return true;
	}
	
};

class RightEndPoint : public EndPoint {
public:
	int Frame_W=200, Frame_H=200;
	void setFrameSize(int W, int H) {
		Frame_W = W;
		Frame_H = H;
	}
	int getEastEndPointPosition() {	//Front와 같음 
		int idx = 0;
		int flag = 0;
		for (int i = 0; i < cloud->width / 2; i++) { //east
			idx = Img_CenterPoint.Idx + i;
			flag = 0;
			if (points[idx].x == 0.0) {
				flag = 1;
				for (int c = 0; c < 3; c++) {
					if (points[idx + c].x != 0.0) {
						flag = 0;
					}
				}
				if (flag == 1) {
					return idx+5;
					break;
				}
			}
		}
	}
	int getWestEndPointPosition() { 
		return E.Idx - Frame_W;
	}
	int getSouthEndPointPosition() {
		return N.Idx + Frame_H * cloud->width;
	}
	int getNorthEndPointPosition()
	{
		int idx = 0;
		int flag = 0;
		for (int i = 0; i < cloud->height / 2; i++) { //Front랑 Mid에서 움직일지 
			if ((Img_CenterPoint.Idx - (i * cloud->width)) > 0) {
				idx = Img_CenterPoint.Idx - (i * cloud->width);
				flag = 0;
				if (points[idx].x == 0.0) {
					flag = 1;
					for (int c = 0; c < 3; c++) {
						if (points[idx - (c * cloud->width)].z != 0.0) {
							flag = 0;
						}
					}
					if (flag == 1) {
						return idx - 5 * cloud->width;
						break;
					}
				}
			}
			else {
				std::cout << "[Right] : 얼굴이 너무 위로올라 갔습니다.\n" << std::endl;
				exit(1);
			}
		}
	}

	bool isRightEndPointPosition() {
		setPosition('E', getEastEndPointPosition());
		setPosition('N', getNorthEndPointPosition());

		setPosition('W', getWestEndPointPosition());
		setPosition('S', getSouthEndPointPosition());
		//setPosition('S', WE_MidPoint.Idx+1);

		std::cout << " W : "; W.toString();
		std::cout << " E : "; E.toString();
		std::cout << " N : "; N.toString();
		std::cout << " S : "; S.toString();
		std::cout << "\n";

		std::cout << " E-W : " << E.Col - W.Col << " S-N : " << (S.Row - N.Row) << std::endl;

		if (W.Idx != -1 && E.Idx != -1 && S.Idx != -1 && N.Idx != -1 && S.Idx != N.Idx) { // 초기값을 구하고 상단점과 하단점을 구했을 경우 
			double ratio = ((double)S.Row - N.Row) / ((double)E.Col - W.Col);
			std::cout << "Width / Height ratio : " << ratio << std::endl;
			if (2.0 > ratio && ratio >= 1.0) {
				return false;
			}
		}
		return true;
	}
};
class LeftEndPoint : public EndPoint {
public:
	int Frame_W = 200, Frame_H = 200;
	void setFrameSize(int W, int H) {
		Frame_W = W;
		Frame_H = H;
	}
	int getEastEndPointPosition() {	//Front와 같음 
		return W.Idx + Frame_W;
	}
	int getWestEndPointPosition() {
		int idx = 0;
		int flag = 0;
		for (int i = 0; i < cloud->width / 2; i++) {	//West
			idx = Img_CenterPoint.Idx - i;
			flag = 0;
			if (points[idx].x == 0.0) {
				flag = 1;
				for (int c = 0; c < 3; c++) {
					if (points[idx - c].x != 0.0) {
						flag = 0;
					}
				}
				if (flag == 1) {
					return idx;
					break;
				}
			}
		}
	}
	int getSouthEndPointPosition() {
		return N.Idx + Frame_H * cloud->width;
	}
	int getNorthEndPointPosition()
	{
		int idx = 0;
		int flag = 0;
		for (int i = 0; i < cloud->height / 2; i++) { //Front랑 Mid에서 움직일지 
			if ((Img_CenterPoint.Idx - (i * cloud->width)) > 0) {
				idx = Img_CenterPoint.Idx - (i * cloud->width);
				flag = 0;
				if (points[idx].x == 0.0) {
					flag = 1;
					for (int c = 0; c < 3; c++) {
						if (points[idx - (c * cloud->width)].z != 0.0) {
							flag = 0;
						}
					}
					if (flag == 1) {
						return idx - 5 * cloud->width;
						break;
					}
				}
			}
			else {
				std::cout << "[Right] : 얼굴이 너무 위로올라 갔습니다.\n" << std::endl;
				exit(1);
			}
		}
	}

	bool isRightEndPointPosition() {
		setPosition('N', getNorthEndPointPosition());
		setPosition('W', getWestEndPointPosition());

		setPosition('E', getEastEndPointPosition());
		setPosition('S', getSouthEndPointPosition());
		//setPosition('S', WE_MidPoint.Idx+1);

		std::cout << " W : "; W.toString();
		std::cout << " E : "; E.toString();
		std::cout << " N : "; N.toString();
		std::cout << " S : "; S.toString();
		std::cout << "\n";

		std::cout << " E-W : " << E.Col - W.Col << " S-N : " << (S.Row - N.Row) << std::endl;

		if (W.Idx != -1 && E.Idx != -1 && S.Idx != -1 && N.Idx != -1 && S.Idx != N.Idx) { // 초기값을 구하고 상단점과 하단점을 구했을 경우 
			double ratio = ((double)S.Row - N.Row) / ((double)E.Col - W.Col);
			std::cout << "Width / Height ratio : " << ratio << std::endl;
			if (2.0 > ratio && ratio >= 1.0) {
				return false;
			}
		}
		return true;
	}
};