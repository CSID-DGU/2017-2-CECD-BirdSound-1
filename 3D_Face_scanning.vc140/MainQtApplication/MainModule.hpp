#include "ui_mainmodule.h"
#include "ui_calibrationmodule.h"
#include "ui_scanmoduleqt.h"
#include "ui_registrationmodule.h"
#include "Data.cpp"
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
public:
	Data *data;
private slots:
	void cellSelected(int nRow, int nCol);
private:
	Ui::MainModule ui;
};