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
		WorkerThread(Device *device, RS_400_STREAM_TYPE stream, int max_shot_num) {
			m_max_shot_num = max_shot_num;
			isSetDetect = false;
			m_stream = stream;
			m_device = device;
			//connect(workerColor, &WorkerThread::updateColorPixmap, this, &CalibrationModule::updateColor);
		}

		//stop streaming
		~WorkerThread() {
			QImage image;
			image = QImage(1920, 1080, QImage::Format_RGB888);
			image.fill(QColor(Qt::red).rgb()); 
			QPixmap cbuf = QPixmap::fromImage(image);
			
			if (m_stream == RS_400_STREAM_TYPE::RS400_STREAM_COLOR) {
				m_device->stopStreaming(m_stream);
				emit updateColorPixmap(cbuf);
			}
			else if (m_stream == RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1) {
				m_device->stopStreaming(m_stream);
				emit updateIR1Pixmap(cbuf);
			}
			else if (m_stream == RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2) {
				m_device->stopStreaming(m_stream);
				emit updateIR2Pixmap(cbuf);
			}


		}	
		void run() override;

		void stop() {
			m_threadLife = false;
		}
public slots:
	
	void setDetection() {
		isSetDetect = true;
	}

	void unsetDetection() {
		isSetDetect = false;
	}

	void capture() {//m_pointBuf

		QImage endImage;
		endImage = QImage(1920, 1080, QImage::Format_RGB888);
		endImage.fill(QColor(Qt::red).rgb());
		if ((isSetDetect == true)&&(true)) {
			vector<cv::Point3f> obj;


			for (int i = 0; i < m_numCornersVer; i++)
				for (int j = 0; j < m_numCornersHor; j++)
					obj.push_back(cv::Point3f((float)j * 24.0f, (float)i * 24.0f, 0));
			
			/*for (int j = 0; j<m_numSquares; j++)
				obj.push_back(cv::Point3f(j / m_numCornersVer, j%m_numCornersHor, 0.0f));*/
			std::string str;
			image_points.push_back(m_pointBuf);
			object_points.push_back(obj);
			m_captureNum++;
			emit updateCapture(m_captureNum, m_stream);
			emit syncIRCam();
			if (m_captureNum == m_max_shot_num) {
				m_threadLife = false;
				wait(500);
				QPixmap buf = QPixmap::fromImage(endImage);
				if (m_stream == RS400_STREAM_COLOR) {
					emit updateColorPixmap(buf);
				}
				else if (m_stream == RS400_STREAM_INFRARED1) {
					emit updateIR1Pixmap(buf);
				}
				else if (m_stream == RS400_STREAM_INFRARED2) {
					emit updateIR2Pixmap(buf);
				}
				
				emit ready2Calibration(object_points, image_points, m_stream);
			}
		}	
	}
	
	void sync() {
		emit updateCapture(m_captureNum, m_stream);
		capture();
	}

signals:
void syncIRCam();
void updateColorPixmap(QPixmap pixmap);
void updateIR1Pixmap(QPixmap pixmap);
void updateIR2Pixmap(QPixmap pixmap);
void updateCapture(int captureNum, RS_400_STREAM_TYPE m_stream);
void ready2Calibration(std::vector<std::vector<cv::Point3f>> object_points, std::vector<std::vector<cv::Point2f>> image_points, RS_400_STREAM_TYPE m_stream);

private:
	//need to calibration
	std::vector<std::vector<cv::Point2f>> image_points;
	std::vector<std::vector<cv::Point3f>> object_points;
	int m_captureNum = 0;
	int m_max_shot_num;
	int m_numCornersHor = 7, m_numCornersVer = 9;
	int m_numSquares = m_numCornersHor * m_numCornersVer;
	cv::Size m_board_sz = cv::Size(m_numCornersHor, m_numCornersVer);
	std::vector<cv::Point2f> m_pointBuf;
	

	RS_400_STREAM_TYPE m_stream;
	realsense::Device* m_device;
	bool isSetDetect;
	bool m_threadLife = true;

};