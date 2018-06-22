#include "InitializeModule.hpp"
#include "../../DepthModule/device.h"
#include <string>
#include <atlstr.h>
#include <windows.h>
#include <qprogressbar.h>
#include "ApplicationConfig.hpp"

using namespace std;

InitializeModule::InitializeModule(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

}
bool InitializeModule::Init() {
	int max = 100;
	int div = 10;
	//m_device->EnableEmitter(0.0f);
	ui.progressBar->setRange(0, max);
	ui.progressBar->setValue(0);

	//Check device connected?
	string devSerialNumber = realsense::getFirstSerial();
	if (devSerialNumber == "e115685") { //e115685 means "device not founded" (2.9.0)
		string contents = "Camera is not connected";
		CString c_contents= contents.c_str();
		LPTSTR l_contents = c_contents.GetBuffer(0);
		
		string title = "WARNNING";
		CString c_title = title.c_str();
		LPTSTR l_title = c_title.GetBuffer(0);

			
		MessageBox(0, l_contents, l_title, MB_OK);
		return false;
	}

	// Check Application directory
	//auto c = Config::get_instance();
	//DWORD ftyp = GetFileAttributesA(c.application_path.c_str());
	//if (ftyp == INVALID_FILE_ATTRIBUTES) { // Directory not exist
	//	CreateDirectory((LPCWSTR)c.application_path.c_str(), NULL);
	//}

	//if (ftyp & FILE_ATTRIBUTE_DIRECTORY) { // Directory exist

	//}
		
	
	ui.progressBar->show();
	for (int i = 1; i <= div; i++) {
		//프로세스 처리 
		QEventLoop loop;
		QTimer::singleShot(100, &loop, SLOT(quit()));
		loop.exec();
		qApp->processEvents();
		ui.progressBar->setValue(i*div);
	}
}