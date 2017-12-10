#pragma once
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "stdafx.h"

using namespace std;
using namespace rs;
using namespace pcl;
using namespace io;
#define FILE_LEN 16
/*
TODO
cloud 로 arr 교체하기
*/

typedef struct Color {
	int x;
	int y;
}Color;
class ObjWriter {
public:
	char filename[FILE_LEN];
	PointCloud<PointXYZ> *Cloud;
	Color *color;
	int subWidth;
	int subHeight;
	int subPOINTS;
	char mtlfile[FILE_LEN + 5] = "";
	char objfile[FILE_LEN + 5] = "";
	

	ObjWriter(char file[FILE_LEN], PointCloud<PointXYZ>* adpeth, Color *aImg) {
		strcpy(filename, file);
		Cloud = adpeth;
		color = aImg;
		subWidth = Cloud->width;
		subHeight = Cloud->height;
		subPOINTS = subWidth*subHeight;
		//Image must be Saved
		std::cout << "MTL\n"; saveMtl(); 
		std::cout << "OBJ\n"; saveOBJ();
	}
	void saveMtl() {
		strcat(mtlfile, filename);
		strcat(mtlfile, ".mtl");
		std::ofstream mtl(mtlfile);
		std::string mtlFile_1 = "newmtl f\nKd 0.00 0.00 0.00\nKa 0.00 0.00 0.00\nTf 1.00 1.00 1.00\nmap_Kd ";
		std::string mtlFIle_2 = ".bmp\nNi 1.00";
		mtl << mtlFile_1<< filename << mtlFIle_2;
	}
	double abs(double A) {
		if (A > 0) {
			return A;
		}
		else {
			return -A;
		}
	}
	void saveOBJ() {
		strcat(objfile, filename);
		strcat(objfile, ".obj");
		std::ofstream obj(objfile);
		int ct = 0;
		obj << "# This file is generated from Renai prs file.\n"
			<< "mtllib " << mtlfile << "\n";
		for (int i = 0; i < subPOINTS; i++) {
			obj << "v " << Cloud->points[i].x << " "<< Cloud->points[i].y << " " << Cloud->points[i].z << std::endl;
		}
		std::cout << "V ended\n";
		for (int j=0; j<subHeight; j++) {
			for (int i=0; i<subWidth; i++) {
				obj << "vt " << (0.005 + color[j*subWidth + i].x / float(subWidth)) << " " << (color[j*subWidth + i].y / float(subHeight)) << std::endl;
			}
			//std::cout <<j;
		}
		std::cout << "VT ended\n";
		for (int i = 0; i < subPOINTS; i++) {
			if ((i + subWidth + 1 < subPOINTS) && ((i + 1) % subWidth != 0)) {
				if (abs(Cloud->points[i].z - Cloud->points[i + subWidth + 1].z) > abs(Cloud->points[i + 1].z - Cloud->points[i + subWidth].z)) {
					if ((Cloud->points[i].x != 0) && (Cloud->points[i + subWidth].x != 0) && (Cloud->points[i + 1].x != 0))
						obj <<"f "<< i << "/" << i <<
						" " << i + subWidth <<"/" << i + subWidth <<
						" " << i + 1 << "/" << i + 1 <<
						std::endl;
					if ((Cloud->points[i + subWidth].x != 0) && (Cloud->points[i + 1].x != 0) && (Cloud->points[i + subWidth + 1].x != 0))
						obj << "f " << i + subWidth << "/" << i + subWidth <<
						" " << i + 1 << "/" << i + 1 <<
						" " << i + subWidth + 1 << "/" << i + subWidth + 1<<
						std::endl;
				}
				else {
					if ((Cloud->points[i].x != 0) && (Cloud->points[i + subWidth].x != 0) && (Cloud->points[i + subWidth + 1].x != 0))
						obj << "f " << i << "/" << i <<
						" " << i + subWidth << "/"<< i + subWidth<<
						" " << i + subWidth + 1 << "/" << i + subWidth + 1<<
						std::endl;
					if ((Cloud->points[i + 1].x != 0) && (Cloud->points[i + subWidth + 1].x != 0) && (Cloud->points[i].x != 0))
						obj << "f " << i + 1 << "/" << i + 1<<
						" " << i + subWidth + 1 << "/" << i + subWidth + 1<<
						" " << i << "/" << i<<
						std::endl;
				}
			}
		}
		std::cout << "Tex ended\n";
		obj.close();
	}
};