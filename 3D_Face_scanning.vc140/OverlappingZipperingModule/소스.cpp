#include <fstream>
#include <iostream>
int main() {

	std::ifstream fin; // 클래스 객체
	fin.open("./resulttmp.txt"); // 파일경로를 지정할 수도 있다
	double tmp;
	fin >> tmp;
	std::cout << tmp;
}