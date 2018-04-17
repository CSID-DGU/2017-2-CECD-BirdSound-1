#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <forward_list>
#include <vector>
#define WIDTH 1280
#define HEIGHT 720
#define POINTS 921600
#define RI 0
#define FR 1
#define LE 2
#define PAGE 3
#define FILENAME "resulttmp"
//"# vtk DataFile Version 3.0\nvtk output\nASCII\nDATASET POLYDATA\nPOINTS " +str(POINTS*PageNum)+" float\n"
class Pos {
public:
	std::vector<int>* pos;
	Pos() {

	}
	Pos(int a, int b) {
		pos = new std::vector<int>;
		
		pos->push_back(a);
		pos->push_back(b);
	}
	std::vector<int>* get() {
		return pos;
	}
	int operator[](int ix) {
		return (*pos)[ix];
	}
};
class Points {
public:
	Pos L1 = Pos(710, 340);
	Pos L3 = Pos(680,480 );

	Pos F_L1 = Pos(620,380 );
	Pos F_L3 = Pos(680,480 );

	Pos F_R1 = Pos(790,330 );
	Pos F_R3 = Pos(760,470 );

	Pos R1 = Pos(740, 340 );
	Pos R3 = Pos(800, 460 );

	int frle_point_page_FR= 0;
	int frle_point_page_LE= 1;

	int frri_point_page_FR=0;
	int frri_point_page_RI=1;
	std::vector<Pos*> del_tmp_point_frri;
	std::vector<Pos*> del_tmp_point_frle;
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
	double getGrad(Pos P1, Pos P3) {
		if (P1[0] == P3[0]) {
			std::cerr << "분모 is 0 \n";
			return 999999999;
		}
		else {
			return (P1[1] - P3[1]) / double(P1[0] - P3[0]);
		}
	}
	std::vector<Pos>* getGradDelPoint(Pos P1, Pos P3) {
		double m = getGrad(P1, P3);
		double k = (-P1[0]) * m + P1[1];
		std::vector<Pos> *lists = new std::vector<Pos>;

		for (int idx = P1[1]; idx < P3[1]; idx++) {
			Pos tmp(int((idx - k) / m), idx);
			lists->push_back(tmp);
			lists->push_back(tmp);
			lists->push_back(tmp);
		}
		std::cout << "End gradient points\n";
		return lists;
	}

	std::vector<Pos>* getF_LL() {
		std::vector<Pos>* F_LL = new std::vector<Pos>;

		Pos _F_LL_tmp1(F_L1[0] - 30, F_L1[1] - 100);
		Pos _F_LL_tmp3(F_L3[0] + 10, HEIGHT);

		std::vector<Pos>* F_LL_tmp1 = getGradDelPoint(_F_LL_tmp1, F_L1);
		std::vector<Pos>* F_LL_tmp2 = getGradDelPoint(F_L1, F_L3);
		std::vector<Pos>* F_LL_tmp3 = getGradDelPoint(F_L3, _F_LL_tmp3);

		for (auto i = F_LL_tmp1->cbegin(); i != F_LL_tmp1->cend(); i++) {
			F_LL->push_back(*i);
		}
		for (auto i = F_LL_tmp2->cbegin(); i != F_LL_tmp2->cend(); i++) {
			F_LL->push_back(*i);
		}
		for (auto i = F_LL_tmp3->cbegin(); i != F_LL_tmp3->cend(); i++) {
			F_LL->push_back(*i);
		}
		delete F_LL_tmp1, F_LL_tmp2, F_LL_tmp3;
		return F_LL;
	}
	std::vector<Pos>* getF_RL() {
		std::vector<Pos>* F_RL = new std::vector<Pos>;

		Pos _F_RL_tmp1(F_R1[0] + 30, F_R1[1] - 100);

		Pos _F_RL_tmp3(F_R3[0] + 200, HEIGHT);

		std::vector<Pos>* F_LR_tmp1 = getGradDelPoint(_F_RL_tmp1, F_R1);
		std::vector<Pos>* F_LR_tmp2 = getGradDelPoint(F_R1, F_R3);
		std::vector<Pos>* F_LR_tmp3 = getGradDelPoint(F_R3, _F_RL_tmp3);

		for (auto i = F_LR_tmp1->cbegin(); i != F_LR_tmp1->cend(); i++) {
			F_RL->push_back(*i);
		}
		for (auto i = F_LR_tmp2->cbegin(); i != F_LR_tmp2->cend(); i++) {
			F_RL->push_back(*i);
		}
		for (auto i = F_LR_tmp3->cbegin(); i != F_LR_tmp3->cend(); i++) {
			F_RL->push_back(*i);
		}
		delete F_LR_tmp1, F_LR_tmp2, F_LR_tmp3;
		return F_RL;
	}

	std::vector<Pos*> getDeleteIndex2(int remainPage, int deletePage, Pos D1, std::vector<Pos>* remaine_list) {

		return;
	}
};
int main() {
	Points p;
	p.getXYZPoints(FILENAME);

	std::vector<Pos>* F_LL = p.getF_LL();
	std::vector<Pos>* F_RL = p.getF_RL();

	//for (auto i = F_RL->cbegin(); i != F_RL->cend(); i++) { std::cout << (*(i->pos))[0] << "\n"; }
	
	std::cout << "\tget \t\tOverlap Point " << "\n"; 
	p.del_tmp_point_frle = p.getDeleteIndex2(FR, LE, Pos(p.L1[0] - 30, p.L1[1] - 100), F_LL);

}