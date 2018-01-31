#pragma once
#ifndef DEVICE_H
#define DEVICE_H
#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif
#ifdef _WIN32
#define MUTEX_LOCK EnterCriticalSection
#define MUTEX_UNLOCK LeaveCriticalSection
#else
#define MUTEX_LOCK(m) if (0 != pthread_mutex_lock(m)) throw std::runtime_error
("pthread_mutex_lock failed")
#define MUTEX_UNLOCK(m) if (0 != pthread_mutex_unlock(m)) throw std::runtime_error
("pthread_mutex_unlock failed")
#endif

//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
#include "common.h"
#include "libRealsense2\rs.hpp"
#include "librealsense2\rs_advanced_mode.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdint>



namespace realsense {
	using namespace std;
	using namespace rs2;
	
	//raw to other formating
	
	string getFirstSerial() {
		return getSerial(0);
	}

	string getSerial(int devIdx) {
		if (devIdx < 0) return;
		rs2::context ctx;
		if (ctx.query_devices().size < devIdx) return;
		rs2::device dev = ctx.query_devices()[devIdx];
		string serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
		return serial_number;
	}

	enum RS_400_STREAM_TYPE
	{
		RS400_STREAM_DEPTH,
		RS400_STREAM_INFRARED,
		RS400_STREAM_INFRARED2,
		RS400_STREAM_COLOR,
		RS400_STREAM_COUNT
	};

	enum GVD_FIELDS
	{
		SKU_COMPONENT = 166,
		RGB_MODE = 178,
	};

	struct camera_info
	{
		std::string name;
		std::string serial;
		std::string fw_ver;
		std::string pid;
		bool isRGB;
		bool isWide;
	};

	class Device {
	public:
		Device(string serialNumber);
		camera_info InitializeCamera(string serial_number);
		bool SetMediaMode(int width, int height, int frameRate, int colorWidth, int colorHeight, bool enableColor);
		bool GetProfile(rs2::stream_profile& profile, rs2_stream stream, int width, int height, int fps, int index);
		void EnableAutoExposure(float value);
		void EnableEmitter(float value);
		void SetAeControl(unsigned int point);
		void StartCapture();
		void StartCapture(std::function<void(const void *leftImage, const void *rightImage, const void *depthImage, const uint64_t timeStamp)> callback);
		auto GetRawImage(RS_400_STREAM_TYPE streamType, rs2_format format);
		
		camera_info info;
		std::uint8_t* leftImage;
		std::uint8_t* rightImage;
		std::uint8_t* colorImage;
		std::uint8_t* depthImage;
	private:
		rs2::context* m_context;
		rs2::device m_device;
		rs2::sensor m_depthSensor;
		rs2::sensor m_colorSensor;

		std::function<void(const void *leftImage, const void *rightImage, const void *colorImage, const uint64_t timeStamp)> callback;
		std::vector<rs2::stream_profile> depthProfiles;
		std::vector<rs2::stream_profile> colorProfile;
		std::unique_ptr<uint16_t[]> lrImage[2];

		std::unique_ptr<uint8_t[]> m_grayImage;
		bool isAdvanced;
		int m_width;
		int m_height;
		int m_fps;
		int m_rgbWidth;
		int m_rgbHeight;
		void *pData[RS400_STREAM_COUNT + 1];
		uint64_t timestamp[RS400_STREAM_COUNT + 1];
		uint64_t ts;
		bool captureStarted;
		bool stopProcessFrame;
		bool bColorEnabled;
		#ifdef _WIN32
			CRITICAL_SECTION m_mutex;
		#else
			pthread_mutex_t m_mutex;
		#endif
		

	};
}



class RS400Device{

};


#endif