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
	//need to calibration
	int m_numCornersHor = 7, m_numCornersVer = 9;
	int m_numSquares = m_numCornersHor * m_numCornersVer;
	cv::Size m_board_sz = cv::Size(m_numCornersHor, m_numCornersVer);
	std::vector<cv::Point2f> m_pointBuf;


	RS_400_STREAM_TYPE m_stream;
	realsense::Device* m_device;
	bool isDetect;

};