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
#include <utility>
#include <map>

namespace realsense {
	using namespace std;
	using namespace rs2;
	
	//raw to other formating
	string getFirstSerial();
	string getSerial(int devIdx);

	enum RS_400_SENSOR {
		STEREO_MODULE,
		RGB_CAMERA
	};

	enum RS_400_STREAM_TYPE
	{
		RS400_STREAM_DEPTH,
		RS400_STREAM_INFRARED,
		RS400_STREAM_INFRARED1,
		RS400_STREAM_INFRARED2,
		RS400_STREAM_COLOR,
		RS400_STREAM_COUNT
	};

	enum RS_400_FORMAT {
		RAW16,
		Y16,
		Y8,
		BGRA8,
		RGBA8,
		BGR8,
		RGB8,
		YUYV,
		UYVY,

	};
	enum class RS_400_DEPTH_RESOLUTION {
		R1280_720,
		R848_480,
		R640_480,
		R640_360,
		R480_270,
		R424_240
	};

	enum RS_400_RESOLUTION {
		R1920_1080,
		R1280_720,
		R960_540,
		R848_480,
		R640_480,
		R640_360,
		R480_270,
		R484_480,
		R424_240,
		R320_240,
		R320_180
	};

	enum RS_400_FPS {
		HZ6,
		HZ15,
		HZ30,
		HZ60
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
		void printDeviceInfo();
		void printSensorInfo();
		void selectSensorAndStream();
		void Device::startStreaming(int streamProp);
		void capture();
		void stopStreaming();
		/******************************/

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

		/******************************/
	private:
		RS_400_STREAM_TYPE m_streamName2Enum(string streamName);
		
		rs2::context* m_context;
		rs2::device m_device;
		vector<rs2::sensor> m_sensors;
		rs2::sensor m_stereoSensor;
		rs2::sensor m_colorSensor;
		std::vector<std::vector<map<int, rs2::stream_profile>>> m_streoUniqueStreams;
		//map<std::pair<rs2_stream, int>, int> m_streoUniqueStreams;
		std::vector<std::vector<map<int, rs2::stream_profile>>> m_colorUniqueStreams;

		rs2::frame_queue m_depthFrameQueue;
		rs2::frame_queue m_colorFrameQueue;
		RS_400_SENSOR m_selectedSensor;
		RS_400_STREAM_TYPE m_selectedStream;
		/************************/
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


#endif