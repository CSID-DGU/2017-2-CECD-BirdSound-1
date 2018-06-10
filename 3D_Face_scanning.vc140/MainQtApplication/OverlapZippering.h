#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include"vtkRenderer.h"
#include"vtkActor.h"
#include<vector>
#include"vtkLandmarkTransform.h"
#include"vtkPoints.h"
#include"vtkPolyData.h"
#include"vtkVertexGlyphFilter.h"


#include"vtkRenderWindow.h"
#include"vtkPolyDataMapper.h"
#include"vtkTransformPolyDataFilter.h"
#include"vtkProperty.h"
#include"vtkPolyDataMapper.h"
#include"vtkRenderWindow.h"
#include"vtkRenderWindowInteractor.h"
#include"double3.h"
//#include"vtkMatrix4x4.h"

#include"MeshPreview.h"

#include"LandMarkInteractorStyle.h"
#include"vtkAppendPolyData.h"
#include"vtkTransformPolyDataFilter.h"
#include"vtkIterativeClosestPointTransform.h"
#include"vtkMatrix4x4.h"
#include"vtkTransform.h"

#include"vtkOBJExporter.h"
#include"vtkPointData.h"
#include"vtkTransformTextureCoords.h"
#include"vtkImageAppend.h"

#include "AlignModule.h"

#define WIDTH 1280
#define HEIGHT 720
#define POINTS 921600
#define RI 0
#define FR 1
#define LE 2
#define PAGE 3
#define FILENAME "resulttmp"
/**
TODO
1. addedMakeMesh 수정하기
*/
#ifndef Pos3D_H
#define Pos3D_H
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
	double& operator[](int ix) {
		return (*pos3d)[ix];
	}

	friend std::ostream& operator<< (std::ostream & os, const Pos3D& p) {
		os << "[" << (*(p.pos3d))[0] << ", " << (*(p.pos3d))[1] << ", " << (*(p.pos3d))[2] << "]";
		return os;
	}
};
#endif


#ifndef Pos_H
#define Pos_H
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
	int& operator[](int ix) {
		return (*pos)[ix];
	}
	friend std::ostream& operator<< (std::ostream & os, const Pos& p) {
		os << "[" << (*(p.pos))[0] << ", " << (*(p.pos))[1] << "]";
		return os;
	}
};
#endif

#ifndef PosSet_H
#define PosSet_H
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
	Pos& operator[](int ix) {
		return (*posset)[ix];
	}
	friend std::ostream& operator<< (std::ostream & os, const PosSet& p) {
		os << "[" << (*(p.posset))[0] << ", " << (*(p.posset))[1] << "]";
		return os;
	}
};
#endif

#ifndef PosPolyInt_H
#define PosPolyInt_H
class PosPolyInt {
public:
	int pospolyint[3];
	PosPolyInt(int a, int b, int c) {
		pospolyint[0] = a;
		pospolyint[1] = b;
		pospolyint[2] = c;
	}
	friend std::ostream& operator<< (std::ostream & os, const PosPolyInt& p) {
		os << "[" << (p.pospolyint)[0] << ", " <<(p.pospolyint)[1] << ", " <<(p.pospolyint)[2] << "]";
		return os;
	}
};
#endif

#ifndef OverlapZippering_H
#define OverlapZippering_H
class OverlapZippering {
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


	std::vector<PosSet>* connPoint_frle;
	std::vector<PosSet>* connPoint_frri;

	std::vector<std::string*>* addedmesh_frle;
	std::vector<std::string*>* addedmesh_frri;

	std::vector<Pos>* part_del_point_frle_FR;
	std::vector<Pos>* part_del_point_frle_LE;
	std::vector<Pos>* part_del_point_frri_FR;
	std::vector<Pos>* part_del_point_frri_RI;

	std::vector<Pos>* part_del_point_ALL[3];

	int A_ct;
	int B_ct;
	int C_ct;

	std::vector<std::string*>* A_ct_list;
	std::vector<std::string*>* B_ct_list;
	std::vector<std::string*>* C_ct_list;

	std::vector<Pos3D> data;
	std::vector<std::vector<Pos3D>> A;

	std::ofstream fout;
	std::ifstream fin;

	bool existMesh;
	MeshPreview *resultMesh;
public:
	OverlapZippering() {
		existMesh = false;
	}

	void setLandmarkLeftFront(Pos& _L1, Pos& _L3, Pos& _F_L1, Pos& _F_L3)
	{
		for (int i = 0; i < 2; i++) {
			L1[i] = _L1[i];
			L3[i] = _L3[i];

			F_L1[i] = _F_L1[i];
			F_L3[i] = _F_L3[i];
		}
		std::cout << "L1: " << L1[0] << " " << L1[1] << "\n";
		std::cout << "L3: " << L3[0] << " " << L3[1] << "\n";

		std::cout << "F_L1: " << F_L1[0] << " " << F_L1[1] << "\n";
		std::cout << "F_L3: " << F_L3[0] << " " << F_L3[1] << "\n";
	}
	void setLandmarkRightFront(Pos& _R1, Pos& _R3, Pos& _F_R1, Pos& _F_R3)
	{
		for (int i = 0; i < 2; i++) {
			R1[i] = _R1[i];
			R3[i] = _R3[i];

			F_R1[i] = _F_R1[i];
			F_R3[i] = _F_R3[i];
		}
		std::cout << "R1: " << R1[0] << " " << R1[1] << "\n";
		std::cout << "R3: " << R3[0] << " " << R3[1] << "\n";

		std::cout << "F_R1: " << F_R1[0] << " " << F_R1[1] << "\n";
		std::cout << "F_R3: " << F_R3[0] << " " << F_R3[1] << "\n";
	}
	void getXYZPoints() {
		int point = 0;
		int subPOINTS = 0;
		double t[3];
		int page = 0;
		int base;
		for (int i = 0; i < resultMesh->size; i = i + 5)
		{
			vtkPoints *value[4];
			page = i % 5;
			for (int k = 0; k < 4; k++) {
				value[k] = resultMesh->GetPolyDataAt(i + k)->GetPoints();//이러면 좌측 0째 Mesh에 있는 point다 가져옴	
				int subPOINTS = value[k]->GetNumberOfPoints();
				base = k * subPOINTS;
				for (int j = 0; j < subPOINTS; j++)//갯수는 세면 됨
				{
					for (int u = 0; u < 3; u++) {
						t[u] = - A[page][base + j][u];
					}
					value[k]->SetPoint(j, t);
				}
			}
		}
	}
	void writePoints() {

		/*
		fout.open("points.txt");
		for (int k = 0; k < PAGE; k++) {
			for (int i = 0; i < POINTS; i++) {
				fout << A[k][i][0] << " " << A[k][i][1] << " " << A[k][i][2] << "\n";
			}
		}
		fout.close();
		*/
		
		fout.open("points0.txt");
		for (int i = 0; i < POINTS; i++) {
			fout << A[0][i][0] << " " << A[0][i][1] << " " << A[0][i][2] << "\n";
		}
		fout.close();
		fout.open("points1.txt");
		for (int i = 0; i < POINTS; i++) {
			fout << A[1][i][0] << " " << A[1][i][1] << " " << A[1][i][2] << "\n";
		}
		fout.close();
		fout.open("points2.txt");
		for (int i = 0; i < POINTS; i++) {
			fout << A[2][i][0] << " " << A[2][i][1] << " " << A[2][i][2] << "\n";
		}
		fout.close();
		fout.open("landmark.py");
		fout << "L1 = " << L1 << "\n";
		fout << "L3 = " << L3 << "\n\n";

		fout << "F_L1 = " << F_L1<< "\n";
		fout << "F_L3 = " << F_L3<< "\n\n";

		fout << "R1 = " << R1 << "\n";
		fout << "R3 = " << R3 << "\n\n";

		fout << "F_R1 = " << F_R1 << "\n";
		fout << "F_R3 = " << F_R3 << "\n";
		std::cout << "End write data\n";
		fout.close();
	}
	void setXYZPoints(MeshPreview &resultMesh) {
		this->resultMesh = &resultMesh;
		//_AM->existMesh = true;
		int point = 0;
		int subPOINTS = 0;
		double _t1, _t2, _t3;
		for (int i = 0; i < resultMesh.size; i = i + 5)
		{
			vtkPoints *value[4];
			for (int k = 0; k < 4; k++) {
				value[k] = resultMesh.GetPolyDataAt(i + k)->GetPoints();//이러면 좌측 0째 Mesh에 있는 point다 가져옴	
				int subPOINTS = value[k]->GetNumberOfPoints();
				for (int j = 0; j < subPOINTS; j++)//갯수는 세면 됨
				{
					_t1 = value[k]->GetPoint(j)[0];
					_t2 = value[k]->GetPoint(j)[1];
					_t3 = value[k]->GetPoint(j)[2];

					if (_t3<0.4 || _t1 > 0.4 || _t1 <-0.1 || _t3 >0.8)
						data.push_back(Pos3D(0.0, 0.0, 0.0));
					else
						data.push_back(Pos3D(-_t1, -_t2, -_t3));
					//std::cout << value->GetPoint(j)[0] << " " << value->GetPoint(j)[1] << " " << value->GetPoint(j)[2];//x,y,z값
				}
			}
			A.push_back(data);
			data.clear();
		}
	}
	void setXYZPoints(std::string filename) {
		fin.open("./resulttmp.txt"); // 파일경로를 지정할 수도 있다
		double tmp1, tmp2, tmp3;
		for (int k = 0; k < PAGE; k++) {
			for (int i = 0; i < POINTS; i++) {
				fin >> tmp1 >> tmp2 >> tmp3;
				data.push_back(Pos3D(tmp1, tmp2, tmp3));
			}
			A.push_back(data);
			data.clear();
		}
		std::cout << "End load data\n";
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
		return lists;
	}

	std::vector<Pos>* getF_LL() {
		std::vector<Pos>* F_LL = new std::vector<Pos>;

		Pos _F_LL_tmp1(F_R1[0] - 3, F_R1[1] - 2);
		Pos _F_LL_tmp3(F_R3[0] + 3, HEIGHT);

		//std::vector<Pos>* F_LL_tmp1 = getGradDelPoint(_F_LL_tmp1, F_R1);
		//for (auto i = F_LL_tmp1->cbegin(); i != F_LL_tmp1->cend(); i++) {
		//	F_LL->push_back(*i);
		//}

		std::vector<Pos>* F_LL_tmp2 = getGradDelPoint(F_R1, F_R3);
		for (auto i = F_LL_tmp2->cbegin(); i != F_LL_tmp2->cend(); i++) {
			F_LL->push_back(*i);
		}

		std::vector<Pos>* F_LL_tmp3 = getGradDelPoint(F_R3, _F_LL_tmp3);
		for (auto i = F_LL_tmp3->cbegin(); i != F_LL_tmp3->cend(); i++) {
			F_LL->push_back(*i);
		}

		delete F_LL_tmp2, F_LL_tmp3;//F_LL_tmp1
		return F_LL;
	}
	std::vector<Pos>* getF_RL() {
		std::vector<Pos>* F_RL = new std::vector<Pos>;

		Pos _F_RL_tmp1(F_L1[0] + 3, F_L1[1] - 2);

		Pos _F_RL_tmp3(F_L3[0] + 3, HEIGHT);

		//std::vector<Pos>* F_LR_tmp1 = getGradDelPoint(_F_RL_tmp1, F_L1);
		//for (auto i = F_LR_tmp1->cbegin(); i != F_LR_tmp1->cend(); i++) {
		//	F_RL->push_back(*i);
		//}

		std::vector<Pos>* F_LR_tmp2 = getGradDelPoint(F_L1, F_L3);
		for (auto i = F_LR_tmp2->cbegin(); i != F_LR_tmp2->cend(); i++) {
			F_RL->push_back(*i);
		}

		std::vector<Pos>* F_LR_tmp3 = getGradDelPoint(F_L3, _F_RL_tmp3);
		for (auto i = F_LR_tmp3->cbegin(); i != F_LR_tmp3->cend(); i++) {
			F_RL->push_back(*i);
		}
		delete F_LR_tmp2, F_LR_tmp3; //F_LR_tmp1
		return F_RL;
	}

	std::vector<Pos3D>* getWorkingSet(int page, Pos P) {
		std::vector<Pos3D>* tmp = new std::vector<Pos3D>;
		int	P_idx = getPointIdx(P);

		tmp->push_back(A[page][P_idx - 1]);
		tmp->push_back(A[page][P_idx]);
		tmp->push_back(A[page][P_idx + 1]);
		P_idx = P_idx + WIDTH;

		if (P_idx < POINTS)
			tmp->push_back(A[page][P_idx]);
		else
			tmp->push_back(A[page][P_idx - WIDTH]);
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
	std::vector<PosSet>* getDeleteIndex2(int remainPage, int deletePage, Pos* D1, std::vector<Pos> remaine_list) {
		std::vector<PosSet>* del_point = new std::vector<PosSet>;
		Pos d_nxt = *D1;
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
				tmp = getDistance3D(A[remainPage][getPointIdx(r_nxt)], (*WS_d)[d_idx]);
				if (min > tmp) {	//      #최소인 점 min에 대해
					min = tmp;
					min_idx = d_idx;
				}
			}
			d_nxt = getNextWorkingSetIndex(d_nxt, min_idx);
			del_point->push_back(PosSet(r_nxt, d_nxt)); //#그리고 해당점은 제거할 리스트에 넣는다.

			WS_d = getWorkingSet(deletePage, d_nxt);
			//#print(min_idx);

		}
		return del_point;
	}
	std::vector<Pos>* getDeletePoint(int page, std::vector<PosSet> del_point, const char *direction) {
		std::map<int, int> part_dic_del_point;
		for (int idx = 0; idx < del_point.size(); idx++) {
			if (strcmp(direction, "deleteNagative") == 0) {
				part_dic_del_point.insert(std::pair<int, int>(del_point[idx][page][1], WIDTH));
				if (part_dic_del_point[del_point[idx][page][1]] > del_point[idx][page][0])
					part_dic_del_point[del_point[idx][page][1]] = del_point[idx][page][0];
			}
			else if (strcmp(direction, "deletePositive") == 0) {
				part_dic_del_point.insert(std::pair<int, int>(del_point[idx][page][1], 0));
				if (part_dic_del_point[del_point[idx][page][1]] < del_point[idx][page][0])
					part_dic_del_point[del_point[idx][page][1]] = del_point[idx][page][0];
			}
		}

		std::vector<Pos> *del_point_list = new std::vector<Pos>;
		std::vector<int> part_list_x_del_point;
		for (auto i = part_dic_del_point.cbegin(); i != part_dic_del_point.cend(); i++)
			part_list_x_del_point.push_back(part_dic_del_point[(*i).first]);

		int j = 0;
		for (auto i = part_dic_del_point.cbegin(); i != part_dic_del_point.cend(); i++, j++)
			del_point_list->push_back(Pos(part_list_x_del_point[j], (*i).first));
		return del_point_list;
	}
	void deletePoint(int page, char * direction, std::vector<Pos> &part_del_point) {
		int st_0;
		for (int idx = 0; idx < part_del_point.size(); idx++) {
			st_0 = getPointIdx(part_del_point[idx]);
			if (strcmp(direction, "deletePositive") == 0) {
				part_del_point[idx][0] = part_del_point[idx][0] - 1;
				for (int ix = st_0; ix < st_0 + WIDTH; ix++) {
					if ((ix % WIDTH) == 0)
						break;
					else
						for (int i = 0; i < 3; i++) {
							this->A[page][ix][i] = 0.0;
						}
				}
			}
			else if (strcmp(direction, "deleteNagative") == 0) {
				part_del_point[idx][0] = part_del_point[idx][0] + 1;
				for (int ix = st_0; ix > st_0 - WIDTH; ix--) {
					if ((ix % WIDTH) == 0)
						break;
					else
						for (int i = 0; i < 3; i++) {
							this->A[page][ix][i] = 0.0;
						}
				}
			}
		}
	}
	std::vector<PosSet>* getMeshLine(std::vector<Pos>& part_del_point_0, std::vector<Pos>& part_del_point_1, int page0, int page1) {
		int now_ptr_s = 0;
		double min, tmp;
		int min_idx;
		std::vector<PosSet>* connPoint = new std::vector<PosSet>;
		for (int i = 0; i < part_del_point_0.size(); i++) {
			min = 100.0;
			min_idx = -1;
			if (A[page0][getPointIdx(part_del_point_0[i])][0] != 0.0) {
				for (int j = 0; j < part_del_point_1.size(); j++) {
					tmp = getDistance3D(A[page0][getPointIdx(part_del_point_0[i])], A[page1][getPointIdx(part_del_point_1[j])]);
					if (min > tmp) {
						min_idx = j;
						min = tmp;
					}
				}
				if (now_ptr_s != 0 && min_idx <= now_ptr_s) {
					connPoint->push_back(PosSet(part_del_point_0[i], (*connPoint)[connPoint->size() - 1][1]));
				}
				else {
					for (int idx = now_ptr_s; idx < min_idx + 1; idx++) {
						connPoint->push_back(PosSet(part_del_point_0[i], part_del_point_1[idx]));
					}
					now_ptr_s = min_idx + 1;
				}
			}
		}
		return connPoint;
	}
	std::vector<std::string*>* addedMakeMesh(int page0, int page1, std::vector<PosSet>& connP) {
		std::vector<std::string*>* addedmesh = new std::vector<std::string*>;
		int page0_base = page0*POINTS;
		int page1_base = page1*POINTS;
		Pos s1, s2;
		Pos p1, p2, p3, p4, pp1, pp2, pp3;
		std::vector<PosSet> ps;
		int count = 0;
		for (int idx = 0; idx < connP.size() - 1; idx++) {
			p1 = connP[idx][0];
			p2 = connP[idx + 1][0];
			p3 = connP[idx + 1][1];
			p4 = connP[idx][1];
			//#add spatial mesh
			//ps.push_back(PosSet(p1, p2));
			//ps.push_back(PosSet(p4, p3));
			//ps.push_back(PosSet(p2, p1));
			//ps.push_back(PosSet(p3, p4));
			//for (int idx = 0; idx < ps.size(); idx++) {
			//	s1 = ps[idx][0];
			//	s2 = ps[idx][1];
			//	if (idx % 2 == 0) {
			//		base = page0_base;
			//		page = page0;
			//	}
			//	else {
			//		base = page1_base;
			//		page = page1;
			//	}
			//	/*
			//	if (p1[0] < p2[0]) {
			//		for (int i = 0; i < s2[0] - s1[0] - 1; i++) {
			//			pp1 = s1;
			//			pp2 = Pos(s2[0] - i, s2[1]);
			//			pp3 = Pos(s2[0] - i - 1, s2[1]);
			//			//print(A[page][getPointIdx(pp1)][0], A[page][getPointIdx(pp2)][0], A[page][getPointIdx(pp3)][0])
			//			if (A[page][getPointIdx(pp1)][0] != 0.0 && A[page][getPointIdx(pp2)][0] != 0.0 && A[page][getPointIdx(pp3)][0] != 0.0)
			//				addedmesh->push_back(PosPolyInt(getPointIdx(pp1) + base, getPointIdx(pp2) + base, getPointIdx(pp3) + base));
			//		}
			//	}
			//	if (s1[0] > s2[0]) {
			//		for (int i = 0; i < s1[0] - s2[0] - 1; i++) {
			//			pp1 = s1;
			//			pp2 = Pos(s2[0] + i + 1, s2[1]);
			//			pp3 = Pos(s2[0] + i, s2[1]);
			//			//print(A[page][getPointIdx(pp1)][0], A[page][getPointIdx(pp2)][0], A[page][getPointIdx(pp3)][0])
			//			if (A[page][getPointIdx(pp1)][0] != 0.0 && A[page][getPointIdx(pp2)][0] != 0.0 && A[page][getPointIdx(pp3)][0] != 0.0)
			//				addedmesh->push_back(PosPolyInt(getPointIdx(pp1) + base, getPointIdx(pp2) + base, getPointIdx(pp3) + base));
			//		}
			//	}*/
			//	//print('\n')
			//}

			if (page0 == RI) {
				if (p1[0] < p2[0]) {
					for (int i = 0; i < p2[0] - p1[0] - 1; i++) {
						pp1 = p1;
						pp2 = Pos(p2[0] - i, p2[1]);
						pp3 = Pos(p2[0] - i - 1, p2[1]);
						//std::cout << A[page0][getPointIdx(pp1)][0]<<" "<<A[page0][getPointIdx(pp2)][0] <<" "<<A[page0][getPointIdx(pp3)][0]<<"\n";
						if (A[page0][getPointIdx(pp1)][0] != 0.0 && A[page0][getPointIdx(pp2)][0] != 0.0 && A[page0][getPointIdx(pp3)][0] != 0.0)
							addedmesh->push_back(makeStrMesh(getPointIdx(pp1) + page0_base, getPointIdx(pp2) + page0_base, getPointIdx(pp3) + page0_base));
					}
				}
				if (p1[0] > p2[0]) {
					for (int i = 0; i < p1[0] - p2[0] - 1; i++) {
						pp1 = p1;
						pp2 = Pos(p2[0] + i + 1, p2[1]);
						pp3 = Pos(p2[0] + i, p2[1]);
						//print(A[page0][getPointIdx(pp1)][0], A[page0][getPointIdx(pp2)][0], A[page0][getPointIdx(pp3)][0])
						if (A[page0][getPointIdx(pp1)][0] != 0.0 && A[page0][getPointIdx(pp2)][0] != 0.0 && A[page0][getPointIdx(pp3)][0] != 0.0) {
							//std::cout<<A[page0][getPointIdx(pp1)][0] <<"\t"<< A[page0][getPointIdx(pp2)][0] <<"\t"<< A[page0][getPointIdx(pp3)][0] <<"\n";
							addedmesh->push_back(makeStrMesh(getPointIdx(pp1) + page0_base, getPointIdx(pp2) + page0_base, getPointIdx(pp3) + page0_base));
						}
					}
				}
			}
			//connect mesh
			if (getDistance3D(A[page0][getPointIdx(p1)], A[page1][getPointIdx(p3)]) < getDistance3D(A[page0][getPointIdx(p2)], A[page1][getPointIdx(p4)])) {
				if (A[page0][getPointIdx(p1)][0] != 0.0 && A[page1][getPointIdx(p3)][0] != 0.0 && A[page1][getPointIdx(p4)][0] != 0.0) {
					addedmesh->push_back(makeStrMesh(getPointIdx(p1) + page0_base, getPointIdx(p3) + page1_base, getPointIdx(p4) + page1_base));
				}
				if (p1[0] != p2[0] || p1[1] != p2[1])
					if (A[page0][getPointIdx(p1)][0] != 0.0 && A[page0][getPointIdx(p2)][0] != 0.0 && A[page1][getPointIdx(p3)][0] != 0.0) {

						addedmesh->push_back(makeStrMesh(getPointIdx(p1) + page0_base, getPointIdx(p2) + page0_base, getPointIdx(p3) + page1_base));
					}
			}
			else {
				if (A[page0][getPointIdx(p1)][0] != 0.0 && A[page0][getPointIdx(p2)][0] != 0.0 && A[page1][getPointIdx(p4)][0] != 0.0) {
					addedmesh->push_back(makeStrMesh(getPointIdx(p1) + page0_base, getPointIdx(p2) + page0_base, getPointIdx(p4) + page1_base));
				}
				if (p3[0] != p4[0] || p3[1] != p4[1])
					if (A[page0][getPointIdx(p2)][0] != 0.0 && A[page1][getPointIdx(p3)][0] != 0.0 && A[page1][getPointIdx(p4)][0] != 0.0) {
						addedmesh->push_back(makeStrMesh(getPointIdx(p2) + page0_base, getPointIdx(p3) + page1_base, getPointIdx(p4) + page1_base));
					}
			}
		}
		//printf("\t\t\t\t\t\t[%d]\n", count);
		return addedmesh;
	}
	int confirmMeshNumber(std::vector<Pos3D> P) {
		int ct = 0;
		for (int i = 0; i < POINTS; i++) {
			if ((i + WIDTH + 1) < POINTS && (i + 1) % WIDTH != 0) {
				if (abs(P[i][2] - P[i + WIDTH + 1][2]) > abs(P[i + 1][2] - P[i + WIDTH][2])) {
					if ((P[i][0] != 0 && P[i + WIDTH][0] != 0 && P[i + 1][0] != 0))
						ct += 1;
					if ((P[i + WIDTH][0] != 0 && P[i + 1][0] != 0 && P[i + WIDTH + 1][0] != 0))
						ct += 1;
				}
				else {
					if (P[i][0] != 0 && P[i + WIDTH][0] != 0 && P[i + WIDTH + 1][0] != 0)
						ct += 1;
					if (P[i + 1][0] != 0 && P[i + WIDTH + 1][0] != 0 && P[i][0] != 0)
						ct += 1;
				}
			}
		}
		return ct;
	}
	std::string* makeStrMesh(int p1, int p2, int p3) {
		std::string *s = new std::string("3 " + std::to_string(p1) + " " + std::to_string(p2) + " " + std::to_string(p3));
		return s;
	}
	std::vector<std::string*>* makeMesh(std::vector<Pos3D> A, int base) {
		std::vector<std::string*>* ct_list = new std::vector<std::string*>;
		for (int i = 0; i < POINTS; i++) {
			if ((i + WIDTH + 1) < POINTS && (i + 1) % WIDTH != 0) {
				if (abs(A[i][2] - A[i + WIDTH + 1][2]) > abs(A[i + 1][2] - A[i + WIDTH][2])) {
					if (A[i][0] != 0 && A[i + WIDTH][0] != 0 && A[i + 1][0] != 0)
						ct_list->push_back(makeStrMesh(base + i + 1, base + i + WIDTH, base + i));
					if (A[i + WIDTH][0] != 0 && A[i + 1][0] != 0 && A[i + WIDTH + 1][0] != 0)
						ct_list->push_back(makeStrMesh(base + i + WIDTH, base + i + 1, base + i + WIDTH + 1));

				}
				else {
					if (A[i][0] != 0 && A[i + WIDTH][0] != 0 && A[i + WIDTH + 1][0] != 0)
						ct_list->push_back(makeStrMesh(base + i + WIDTH + 1, base + i + WIDTH, base + i));
					if (A[i + 1][0] != 0 && A[i + WIDTH + 1][0] != 0 && A[i][0] != 0)
						ct_list->push_back(makeStrMesh(base + i + 1, base + i + WIDTH + 1, base + i));

				}
			}
		}
		return ct_list;
	}
	void setpart_del_point_ALL() {
		for (int i = 0; i < 3; i++) {
			part_del_point_ALL[i] = new std::vector<Pos>;
		}
		for (int i = 0; i < (*part_del_point_frri_RI).size(); i++) {
			(*(part_del_point_ALL[RI])).push_back((*part_del_point_frri_RI)[i]);
		}
		for (int i = 0; i < (*part_del_point_frle_FR).size(); i++) {
			(*(part_del_point_ALL[FR])).push_back((*part_del_point_frle_FR)[i]);
		}

		for (int i = 0; i < (*part_del_point_frri_FR).size(); i++) {
			(*(part_del_point_ALL[FR])).push_back((*part_del_point_frri_FR)[i]);
		}

		for (int i = 0; i < (*part_del_point_frle_LE).size(); i++) {
			(*(part_del_point_ALL[LE])).push_back((*part_del_point_frle_LE)[i]);
		}
	}
	void deleteOverlap() {
		std::vector<Pos>* F_LL = getF_LL();
		std::vector<Pos>* F_RL = getF_RL();

		//for (auto i = F_LL->cbegin(); i != F_LL->cend(); i++) { std::cout << (*i) << "\n"; }

		std::cout << "\tget \t\tOverlap Point " << "\n";

		del_tmp_point_frle = getDeleteIndex2(FR, LE, new Pos(L1[0] - 3, L1[1] - 3), *F_LL);
		del_tmp_point_frri = getDeleteIndex2(FR, RI, new Pos(L1[0] + 3, L1[1] - 3), *F_RL);

		//for (auto i = p.del_tmp_point_frle->cbegin(); i != p.del_tmp_point_frle->cend(); i++) {	std::cout << *i << "\n";}
		
		part_del_point_frle_FR = getDeletePoint(frle_point_page_FR, *del_tmp_point_frle, "deletePositive");
		part_del_point_frle_LE = getDeletePoint(frle_point_page_LE, *del_tmp_point_frle, "deleteNagative");//  #deleteNagative / deletePositive

		part_del_point_frri_FR = getDeletePoint(frri_point_page_FR, *del_tmp_point_frri, "deleteNagative");
		part_del_point_frri_RI = getDeletePoint(frri_point_page_RI, *del_tmp_point_frri, "deletePositive");//  #deleteNagative / deletePositive
		setpart_del_point_ALL();
		std::cout << part_del_point_frle_FR->size() << " " << part_del_point_frle_LE->size() << "\n";
		std::cout << part_del_point_frri_FR->size() << " " << part_del_point_frri_RI->size() << "\n";
		//for (auto i = p.part_del_point_frle_FR->cbegin(); i != p.part_del_point_frle_FR->cend(); i++) { std::cout <<*i<<"\n"; }

		std::cout << "\tdelete \t\tOverlap Point \n";
		deletePoint(FR, "deleteNagative", *(part_del_point_frle_FR));
		deletePoint(LE, "deletePositive", *(part_del_point_frle_LE));

		deletePoint(FR, "deletePositive", *(part_del_point_frri_FR));
		deletePoint(RI, "deleteNagative", *(part_del_point_frri_RI));
	}
	void zipperMesh() {
		//매쉬 개수 구하기
		std::cout << "Get \tMesh\n";

		connPoint_frle = getMeshLine(*part_del_point_frle_FR, *part_del_point_frle_LE, FR, LE);
		connPoint_frri = getMeshLine(*part_del_point_frri_RI, *part_del_point_frri_FR, RI, FR);
		std::cout << "\t\tconnect \tPoint Length(frle) : " << connPoint_frle->size() << "\n";
		std::cout << "\t\tconnect \tPoint Length(frri) : " << connPoint_frri->size() << "\n";
		//for (auto i = connPoint_frle->cbegin(); i != connPoint_frle->cend(); i++) { std::cout <<*i<<"\n"; }

		addedmesh_frle = addedMakeMesh(FR, LE, *connPoint_frle);
		addedmesh_frri = addedMakeMesh(RI, FR, *connPoint_frri);
		std::cout << "\t\t\t\t" << addedmesh_frle->size() << "\n";
		std::cout << "\t\t\t\t" << addedmesh_frri->size() << "\n";
		//for (auto i = addedmesh_frle->cbegin(); i != addedmesh_frle->cend(); i++) { std::cout <<*i<<"\n"; }

		std::cout << "Get \tMesh\n";
		A_ct = confirmMeshNumber(A[RI]);
		B_ct = confirmMeshNumber(A[FR]);
		C_ct = confirmMeshNumber(A[LE]);

		A_ct_list = makeMesh(A[RI], POINTS*RI);
		B_ct_list = makeMesh(A[FR], POINTS*FR);
		C_ct_list = makeMesh(A[LE], POINTS*LE);

		std::cout << ("Ready for writting Mesh Polygon\n");
		//포인트 반영
		getXYZPoints();
		//str 생성 
		
		/*
		fout.open("resulttmp.vtk");
		fout << "# vtk DataFile Version 3.0\nvtk output\nASCII\nDATASET POLYDATA\nPOINTS " << POINTS*PAGE << " float\n";
		std::cout << "\ttranslate points to string\n";
		for (int j = 0; j < PAGE; j++) {
			for (int i = 0; i < POINTS; i++) {
				fout << A[j][i][0] << " " << A[j][i][1] << " " << A[j][i][2] << "\n";
			}
		}


		int ct = A_ct + B_ct + C_ct + addedmesh_frle->size() + addedmesh_frri->size();
		std::cout << "ALL Mesh number: " << ct << "\n";
		fout << "\n\nPOLYGONS " + std::to_string(ct) + " " + std::to_string(ct * 4) + "\n";
		for (int i = 0; i < A_ct_list->size(); i++) {
			fout << (*(*A_ct_list)[i]) << "\n";
		}
		for (int i = 0; i < B_ct_list->size(); i++) {
			fout << (*(*B_ct_list)[i]) << "\n";
		}
		for (int i = 0; i < C_ct_list->size(); i++) {
			fout << (*(*C_ct_list)[i]) << "\n";
		}
		for (int i = 0; i < addedmesh_frle->size(); i++) {
			fout << (*(*addedmesh_frle)[i]) << "\n";
		}

		for (int i = 0; i < addedmesh_frri->size(); i++) {
			fout << (*(*addedmesh_frri)[i]) << "\n";
		}
		*/
	}
};
#endif

//int main() {
//
//
//	OverlapZippering p;
//	p.getXYZPoints(FILENAME);
//
//	p.deleteOverlap();
//	p.zipperMesh();
//
//
//}