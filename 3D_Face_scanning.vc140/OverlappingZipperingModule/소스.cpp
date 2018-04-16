#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <forward_list>
#include <list>
#define WIDTH 1280
#define HEIGHT 720
#define POINTS 921600
#define RI 0
#define FR 1
#define LE 2
#define PAGE 3
#define FILENAME "resulttmp"
//"# vtk DataFile Version 3.0\nvtk output\nASCII\nDATASET POLYDATA\nPOINTS " +str(POINTS*PageNum)+" float\n"

class Points {
public:
	int L1[2] = { 710,340 };
	int L3[2] = { 680,480 };

	int F_L1[2] = { 620,380 };
	int F_L3[2] = { 680,480 };

	int F_R1[2] = { 790,330 };
	int F_R3[2] = { 760,470 };

	int R1[2] = { 740, 340 };
	int R3[2] = { 800, 460 };
	std::ifstream fin; // 클래스 객체
	double **data;

public:
	Points() {
	}
	void getXYZPoints(std::string filename) {
		fin.open("./resulttmp.txt"); // 파일경로를 지정할 수도 있다
		data = new double*[POINTS*PAGE];
		for (int i = 0; i < POINTS*PAGE; i++) {
			data[i] = new double[3];
			for (int j = 0; j < 3; j++) {
				fin >> data[i][j];
				//std::cout << data[i][j];
			}
			//std::cout <<'\n';
		}
		std::cout << "End load daata\n";
		fin.close();
	}
	int getPointIdx(int A[2]) {
		return A[0] + A[1] * WIDTH;
	}
	double getDistance3D(double P1[3], double P2[3]) {
		return sqrt(pow(P1[0] - P2[0], 2) + pow(P1[1] - P2[1], 2) + pow(P1[2] - P2[2], 2));
	}
	double getGrad(int P1[3], int P3[3]) {
		if (P1[0] == P3[0]) {
			std::cerr << "분모 is 0 \n";
			return 999999999;
		}
		else {
			return (P1[1] - P3[1]) / double(P1[0] - P3[0]);
		}
	}
	std::list<int*>* getGradDelPoint(int P1[2], int P3[2]) {
		double m = getGrad(P1, P3);
		int k = (-P1[0]) * m + P1[1];
		std::list<int*> *lists = new std::list<int*>;

		for (int idx = P1[1]; idx < P3[1]; idx++) {
			int *tmp = new int[2];
			tmp[0] = int((idx - k) / m);
			tmp[1] = idx;
			lists->push_back(tmp);
			lists->push_back(tmp);
			lists->push_back(tmp);
		}
		std::cout << "End gradient points\n";
		return lists;
	}
};
int main() {
	Points p;
	p.getXYZPoints(FILENAME);
	int tmp[2] = { p.F_L1[0] - 30, p.F_L1[1] - 100 };
	std::list<int*> *tmp2 = p.getGradDelPoint(tmp, p.F_L1);
	for (auto i = tmp2->cbegin(); i != tmp2->cend(); i++) {
		std::cout << (*i)[0]<<" "<<(*i)[1] << " \n";
	}
	
}