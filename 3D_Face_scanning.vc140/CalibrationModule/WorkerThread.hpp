#pragma once
#include <qthread.h>
#include <qpixmap.h>
#include <qimage.h>
#include <opencv2\opencv.hpp>
#include <../../DepthModule/device.h>

using namespace realsense;

class WorkerThread: public QThread {
	Q_OBJECT
public:
		WorkerThread(Device *device, RS_400_STREAM_TYPE stream) {
		isDetect = false;
		m_stream = stream;
		m_device = device;
		//connect(workerColor, &WorkerThread::updateColorPixmap, this, &CalibrationModule::updateColor);
		
	}
		void run() override;;

public slots:
	void setDetection() {
		isDetect = true;
	}

	void unsetDetection() {
		isDetect = false;
	}

signals:
void updateColorPixmap(QPixmap pixmap);
void updateIR1Pixmap(QPixmap pixmap);
void updateIR2Pixmap(QPixmap pixmap);

private:
	RS_400_STREAM_TYPE m_stream;
	realsense::Device* m_device;
	bool isDetect;

};