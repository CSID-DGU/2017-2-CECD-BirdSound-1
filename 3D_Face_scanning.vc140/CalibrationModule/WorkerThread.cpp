#include "WorkerThread.hpp"

void WorkerThread::run() {
	if (m_stream == RS400_STREAM_COLOR) {
		//use unrectified format for calibration. noted Custom_Calib_paper.pdf 2.4 11page.
		//IR1,2 = Y16, RGB = YUY2 (YUYV)
		m_device->selectSensorAndStreamProps(m_stream, R1920_1080, YUYV, HZ15);
		//m_device->selectSensorAndStreamProps(m_stream, R1920_1080, RGB8, HZ15);
		
		unique_ptr<uint32_t[]> colorBuf = unique_ptr<uint32_t[]>(new uint32_t[1920 * (1080 + 1)]);
		
		QImage color_image;
		while (m_threadLife) {

			auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);
			uint32_t *color = colorBuf.get();
			ConvertYUY2ToRGBA((uint8_t*)fColor.get_data(), 1920, 1080, (uint8_t*)color);
			//캘리브레이션 모드에 들어가있으면 이를 시작한다.
			if (isSetDetect) {
				cv::Mat cv_color(cv::Size(1920, 1080), CV_8UC4, (uint8_t*)color, cv::Mat::AUTO_STEP);
				cv::Mat cv_gray;
				bool found = cv::findChessboardCorners(cv_color, m_board_sz, m_pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
				if (found)
				{
					cv::cvtColor(cv_color, cv_gray, CV_RGBA2GRAY);
					cv::cornerSubPix(cv_gray, m_pointBuf, cv::Size(m_numCornersHor, m_numCornersVer), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
					cv::drawChessboardCorners(cv_color, cv::Size(m_numCornersHor, m_numCornersVer), cv::Mat(m_pointBuf), found);
				}
				
				QImage color_image(cv_color.data, 1920, 1080, QImage::Format_RGB888);

				//cv::waitKey(1);
				/*color_image = QImage(1920, 1080, QImage::Format_RGB888);
				color_image.fill(QColor(Qt::red).rgb());*/
				color_image = QImage(cv_color.data, 1920, 1080, QImage::Format_RGBA8888);
			}
			else {
				//color_image = QImage((uchar*)fColor.get_data(), 1920, 1080, QImage::Format_RGB888); only for rgb8 stream test
				color_image = QImage((uchar*)color, 1920, 1080, QImage::Format_RGBA8888);
			}
			QPixmap cbuf = QPixmap::fromImage(color_image);
			emit updateColorPixmap(cbuf);
		}
	}
	else if (m_stream == RS400_STREAM_INFRARED1) {
		m_device->selectSensorAndStreamProps(m_stream, R1920_1080, Y16, HZ15);
		auto leftBuf = unique_ptr<uint8_t[]>(new uint8_t[1920*(1080 + 1)]);
		QImage left_image;
		while (true) {
			auto fLeft = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
			uint8_t *left = (uint8_t*)leftBuf.get();
			ConvertLuminance16ToLuminance8((uint16_t*)fLeft.get_data(), 1920, 1080, left);
			if (isSetDetect) {
				cv::Mat cv_left(cv::Size(1920, 1080), CV_8U, left, cv::Mat::AUTO_STEP);
				bool found = cv::findChessboardCorners(cv_left, m_board_sz, m_pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
				if (found)
				{
					cornerSubPix(cv_left, m_pointBuf, cv::Size(m_numCornersHor, m_numCornersVer), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
					cv::drawChessboardCorners(cv_left, cv::Size(m_numCornersHor, m_numCornersVer), cv::Mat(m_pointBuf), found);
				}
				//cv::waitKey(1);
				//left_image = QImage(1920, 1080, QImage::Format_RGB888);
				//left_image.fill(QColor(Qt::red).rgb());
				left_image = QImage(cv_left.data, 1920, 1080, QImage::Format_Grayscale8);
			}
			else {
				left_image = QImage(left, 1920, 1080, QImage::Format_Grayscale8);
			}
			
			QPixmap lbuf = QPixmap::fromImage(left_image);
			emit updateIR1Pixmap(lbuf);
		}

	}
	else if (m_stream == RS400_STREAM_INFRARED2) {
		m_device->selectSensorAndStreamProps(m_stream, R1920_1080, Y16, HZ15);
		auto rightBuf = unique_ptr<uint8_t[]>(new uint8_t[1920*(1080 + 1)]);
		QImage right_image;
		while (true) {
			auto fRight = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED2);
			uint8_t *right = (uint8_t*)rightBuf.get();
			ConvertLuminance16ToLuminance8((uint16_t*)fRight.get_data(), 1920, 1080, right);
			if (isSetDetect) {
				cv::Mat cv_right(cv::Size(1920, 1080), CV_8U, right, cv::Mat::AUTO_STEP);
				bool found = cv::findChessboardCorners(cv_right, m_board_sz, m_pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
				if (found)
				{
					cornerSubPix(cv_right, m_pointBuf, cv::Size(m_numCornersHor, m_numCornersVer), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
					cv::drawChessboardCorners(cv_right, cv::Size(m_numCornersHor, m_numCornersVer), cv::Mat(m_pointBuf), found);
				}
				//cv::waitKey(1);
				/*right_image = QImage(1920, 1080, QImage::Format_RGB888);
				right_image.fill(QColor(Qt::red).rgb());*/
				right_image = QImage(cv_right.data,1920, 1080, QImage::Format_Grayscale8);
			}
			else {
				right_image = QImage(right, 1920, 1080, QImage::Format_Grayscale8);
			}
			
			QPixmap rbuf = QPixmap::fromImage(right_image);
			emit updateIR2Pixmap(rbuf);
		}
	}
}
