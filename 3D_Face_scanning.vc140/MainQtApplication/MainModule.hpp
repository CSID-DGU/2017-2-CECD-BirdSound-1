#include "ui_mainmodule.h"
#include "ui_calibrationmodule.h"
#include "ui_scanmoduleqt.h"
#include "ui_registrationmodule.h"
#include "Data.cpp"
#include <list>
#include <string>
using namespace std;

class DataNode {
	string name;
	string data;
	string file_size;
	string id;

	string& operator [](int i) {
		switch (i)
		{
		case 0: return name;
		case 1: return data;
		case 2: return file_size;
		case 3: return id;
		default:
			break;
		}
	}

};

/*TODO
- runViewer모드 스트링값 전달
*/
class MainModule : public QWidget { //QWidget 상속..
	Q_OBJECT

public:
	MainModule(QWidget* parent = Q_NULLPTR);
	void runCalibrationModule();
	void runScanModule();
	void runViewerModule();
	void runExpModule();
	void loadDB();
public:
	Data *data;
private slots:
	void cellSelected(int nRow, int nCol);
private:
	Ui::MainModule ui;
	std::list<DataNode> application_data;
};