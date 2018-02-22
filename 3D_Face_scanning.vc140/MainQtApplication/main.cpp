#pragma warning (disable : 4996)

#include "iomodule.h"
#include "InitializeModule.hpp" //�ʱ�ȭ �κ� ���� �� ui include
#include "MainModule.hpp"
#include "DemoFirstPart.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//�ʱ�ȭ ����..
	InitializeModule i;
	i.show();
	_sleep(300); //�ʱ�ȭ�� 3�ʸ� ��������.
	//�ʱ�ȭ ��!
	i.close();


	//���������� ����
	//IOModule w;
	//w.show();o
	DemoFirstPart df;
	df.show();
	
	//MainModule m;
	//m.show();
	//���������� ��
	return a.exec();
}
