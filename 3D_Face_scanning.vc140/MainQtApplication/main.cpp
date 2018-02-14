#pragma warning (disable : 4996)
#include "iomodule.h"
#include "InitializeModule.hpp" //초기화 부분 모듈 및 ui include
#include "MainModule.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//초기화 진행..
	InitializeModule i;
	i.show();
	_sleep(3000); //초기화는 3초면 충분하지.
	//초기화 끝!
	i.close();
	
	
	//메인윈도우 진행
	//IOModule w;
	//w.show();
	MainModule m;
	m.show();
	//메인윈도우 끝
	return a.exec();
}