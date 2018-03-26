#include "WorkerThread.hpp"

void WorkerThread::run() {
	if (m_stream == RS400_STREAM_COLOR) {
		//use unrectified format for calibration. noted Custom_Calib_paper.pdf 2.4 11page.
		//IR1,2 = Y16, RGB = YUY2 (YUYV)
		//m_device->selectSensorAndStreamProps(m_stream, R1920_1080, YUYV, HZ15);
		m_device->selectSensorAndStreamProps(m_stream, R1920_1080, RGB8, HZ15);

		unique_ptr<uint32_t[]> colorBuf = unique_ptr<uint32_t[]>(new uint32_t[1920 * (1080 + 1)]);

		QImage color_image;
		while (true) {

			auto fColor = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_COLOR);

			//캘리브레이션 모드에 들어가있으면 이를 시작한다.
			if (isCalib) {
				//uint32_t *color = colorBuf.get();
				//ConvertYUY2ToRGBA((uint8_t*)fColor.get_data(), 1920, 1080, (uint8_t*)color);
				//cv::Mat colorImage(cv::Size(1920, 1080), CV_8UC4, (uint8_t*)color, cv::Mat::AUTO_STEP);
				//cv::Mat gray_image;
				/*bool foundColor = cv::findChessboardCorners(colorImage, m_board_sz, m_pointBufColor, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
				if (foundColor)
				{
				cv::cvtColor(colorImage, gray_image, CV_BGR2GRAY);
				cv::cornerSubPix(gray_image, m_pointBufColor, cv::Size(7, 9), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
				cv::drawChessboardCorners(colorImage, cv::Size(7, 9), cv::Mat(m_pointBufColor), foundColor);
				}*/
				//cv::waitKey(1);
				////QImage color_image(colorImage.data, 1920, 1080, QImage::Format_RGB888);
			}
			else {
				color_image = QImage((uchar*)fColor.get_data(), 1920, 1080, QImage::Format_RGB888);
			}
			QPixmap cbuf = QPixmap::fromImage(color_image);

			//emit progressChanged(10);
			//여기까지도 정상적으로 오게된다.
			emit updateColorPixmap(cbuf);
		}
	}
	else if (m_stream == RS400_STREAM_INFRARED1) {
		m_device->selectSensorAndStreamProps(m_stream, R1920_1080, Y16, HZ15);
		//auto leftBuf = unique_ptr<uint8_t[]>(new uint8_t[1920*(1080 + 1)]);
		QImage left_image;
		while (true) {
			auto fLeft = m_device->capture(RS_400_STREAM_TYPE::RS400_STREAM_INFRARED1);
			uint8_t *left = (uint8_t*)fLeft.get_data();
			ConvertLuminance16ToLuminance8((uint16_t*)fLeft.get_data(), 1920, 1080, left);
			if (isCalib) {

			}
			else {

			}
			//cv::Mat leftImage(cv::Size(1920, 1080), CV_16U, (void*)fLeft.get_data(), cv::Mat::AUTO_STEP);


			cv::Mat left8(cv::Size(1920, 1080), CV_8U, left, cv::Mat::AUTO_STEP);
			/*bool founLeft = cv::findChessboardCorners(left8, m_board_sz, m_pointBufLeft, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
			if (founLeft)
			{
			cornerSubPix(left8, m_pointBufLeft, cv::Size(m_numCornersHor, m_numCornersVer), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(left8, cv::Size(m_numCornersHor, m_numCornersVer), cv::Mat(m_pointBufLeft), founLeft);
			}*/
			///cv::waitKey(1);
			left_image = QImage(left8.data, 1920, 1080, QImage::Format_Grayscale8);
			QPixmap lbuf = QPixmap::fromImage(left_image);
		}

	}
}
