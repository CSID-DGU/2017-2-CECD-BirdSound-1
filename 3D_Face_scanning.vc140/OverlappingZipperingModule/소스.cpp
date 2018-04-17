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
class Pos3D {
public:
	std::vector<double>* pos3d;
	Pos3D() {
		pos3d = new std::vector<double>;
	}
	Pos3D(double a, double b, double c) {
		pos3d = new std::vector<double>;

		pos3d->push_back(a);
		pos3d->push_back(b);
		pos3d->push_back(c);
	}
	double operator[](int ix) {
		return (*pos3d)[ix];
	}
};
class Pos {
public:
	std::vector<int>* pos;
	Pos() {
		pos = new std::vector<int>;
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
class PosSet {
public:
	std::vector<Pos>* posset;
	PosSet() {

		posset = new std::vector<Pos>;
	}
	PosSet(Pos a, Pos b) {
		posset = new std::vector<Pos>;

		posset->push_back(a);
		posset->push_back(b);
	}
	Pos operator[](int ix) {
		return (*posset)[ix];
	}
	std::string operator<<(const std::string& s ) {
	}
};
class Points {
public:
	Pos L1 = Pos(710, 340);
	Pos L3 = Pos(680, 480);

	Pos F_L1 = Pos(620, 380);
	Pos F_L3 = Pos(680, 480);

	Pos F_R1 = Pos(790, 330);
	Pos F_R3 = Pos(760, 470);

	Pos R1 = Pos(740, 340);
	Pos R3 = Pos(800, 460);

	int frle_point_page_FR = 0;
	int frle_point_page_LE = 1;

	int frri_point_page_FR = 0;
	int frri_point_page_RI = 1;
	std::vector<PosSet>* del_tmp_point_frri;
	std::vector<PosSet>* del_tmp_point_frle;
	std::ifstream fin; // 클래스 객체
	std::vector<Pos3D> data;
	std::vector<std::vector<Pos3D>> A;
public:
	Points() {
	}
	void getXYZPoints(std::string filename) {
		fin.open("./resulttmp.txt"); // 파일경로를 지정할 수도 있다
		double tmp1, tmp2, tmp3;
		for (int k = 0; k < PAGE; k++) {
			for (int i = 0; i < POINTS; i++) {
				fin >> tmp1>> tmp2>> tmp3;
				data.push_back(Pos3D(tmp1, tmp2, tmp3));
			}
			A.push_back(data);
		}
		std::cout << "End load daata\n";
		fin.close();
	}
	int getPointIdx(Pos A) {
		return A[0] + A[1] * WIDTH;
	}
	double getDistance3D(Pos3D P1, Pos3D P2) {
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

	std::vector<Pos3D>* getWorkingSet(int page, Pos P) {
		std::vector<Pos3D>* tmp= new std::vector<Pos3D>;
		int	P_idx = getPointIdx(P);

		tmp->push_back(A[page][P_idx - 1]);
		tmp->push_back(A[page][P_idx]);
		tmp->push_back(A[page][P_idx + 1]);
		P_idx = P_idx + WIDTH;
		tmp->push_back(A[page][P_idx]);
		//std::cout << "page:" << page << " " << P << "\n";
		return tmp;
	}
	Pos getNextWorkingSetIndex(Pos now_p, int idx) {
		if (idx == 0)
			return Pos(now_p[0] - 1, now_p[1]);
		else if (idx == 1)
			return Pos(now_p[0], now_p[1]);
		else if (idx == 2)
			return Pos(now_p[0] + 1, now_p[1]);
		else if (idx == 3)
			return Pos(now_p[0], now_p[1] + 1);

	}
	std::vector<PosSet>* getDeleteIndex2(int remainPage, int deletePage, Pos D1, std::vector<Pos> remaine_list) {
		std::vector<PosSet>* del_point = new std::vector<PosSet>;
		Pos d_nxt = D1;
		Pos r_nxt;
		int min_idx = 0;
		double	min = 99999.0;
		double tmp = 0;
		del_point->push_back(PosSet(remaine_list[0], d_nxt));
		std::vector<Pos3D>* WS_d = getWorkingSet(deletePage, d_nxt);
		for (int i = 0; i < remaine_list.size(); i++) {
			min_idx = 0;
			min = 99999.0;
			r_nxt = remaine_list[i];
			for (int d_idx = 0; d_idx < WS_d->size(); d_idx++) {
				tmp = getDistance3D(A[remainPage][getPointIdx(r_nxt)],(*WS_d)[d_idx]);
				if (min > tmp) {	//      #최소인 점 min에 대해
					min = tmp;
					min_idx = d_idx;
				}
			}
			std::cout << min << "\n";
			d_nxt = getNextWorkingSetIndex(d_nxt, min_idx);
			del_point->push_back(PosSet(r_nxt, d_nxt)); //#그리고 해당점은 제거할 리스트에 넣는다.

			WS_d = getWorkingSet(deletePage, d_nxt);
			//#print(min_idx);

		}
		return del_point;
	}
};
int main() {
	Points p;
	p.getXYZPoints(FILENAME);

	std::vector<Pos>* F_LL = p.getF_LL();
	std::vector<Pos>* F_RL = p.getF_RL();

	//for (auto i = F_LL->cbegin(); i != F_LL->cend(); i++) { std::cout << (*(i->pos))[0] << "\n"; }

	std::cout << "\tget \t\tOverlap Point " << "\n";
	p.del_tmp_point_frle = p.getDeleteIndex2(FR, LE, Pos(p.L1[0] - 30, p.L1[1] - 100), *F_LL);
	
	for (auto i = p.del_tmp_point_frle->cbegin(); i != p.del_tmp_point_frle->cend(); i++) { 
		std::cout <<"["<< (*(i->posset))[0][0] <<", "<< (*(i->posset))[0][1]<<"], ["<< (*(i->posset))[1][0] << ", " << (*(i->posset))[1][1] << "]\n"; }

}