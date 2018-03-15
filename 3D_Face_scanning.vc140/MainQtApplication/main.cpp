#include "scanmoduleqt.h"
#include <QtWidgets/QApplication>

#include<crtdbg.h>
#ifndef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE)
#endif


int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc(21133);
	QApplication a(argc, argv);
	ScanModuleQT w;
	w.show();
	return a.exec();

	_CrtDumpMemoryLeaks();
}
