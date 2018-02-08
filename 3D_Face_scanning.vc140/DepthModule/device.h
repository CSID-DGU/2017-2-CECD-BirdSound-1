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
	void ConvertYUY2ToRGBA(const uint8_t* image, int width, int height, uint8_t* output);
	void ConvertYUY2ToLuminance8(const uint8_t* image, int width, int height, uint8_t* output);
	void ConvertLuminance16ToLuminance8(const uint16_t* image, int width, int height, uint8_t* output);
	void ReorderY16(const uint16_t* image, int width, int height);

	enum RS_400_SENSOR {
		STEREO_MODULE,
		RGB_CAMERA
	};

	enum RS_400_STREAM_TYPE
	{
		RS400_STREAM_DEPTH, //Only Z16 format
		RS400_STREAM_INFRARED, //LR image
		RS400_STREAM_INFRARED1, //L image //Only Y8, Y16 format
		RS400_STREAM_INFRARED2, //R image //Only Y8, Y16 format
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
		Z16
	};

	enum RS_400_RESOLUTION {
		R1920_1080,
		R1280_720,
		R960_540,
		R848_480,
		R640_480,
		R640_360,
		R480_270,
		R424_240,
		R320_240,
		R320_180
	};

	enum RS_400_FPS {
		HZ6,
		HZ15,
		HZ25,
		HZ30,
		HZ60,
		HZ90
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
		void selectSensorAndStreamProps();
		void startStreaming(rs2::stream_profile& stream_profile);
		void Device::startStreaming(vector<rs2::stream_profile> &stream_profile);
		void Device::stopStreaming(rs2::stream_profile& stream_profile);
		rs2::frame capture(RS_400_STREAM_TYPE);
		void EnableEmitter(float value);
		void stopStreaming(RS_400_SENSOR);


		/*camera_info InitializeCamera(string serial_number);
		bool SetMediaMode(int width, int height, int frameRate, int colorWidth, int colorHeight, bool enableColor);
		bool GetProfile(rs2::stream_profile& profile, rs2_stream stream, int width, int height, int fps, int index);
		void EnableAutoExposure(float value);
		
		void SetAeControl(unsigned int point);
		void StartCapture();
		void StartCapture(std::function<void(const void *leftImage, const void *rightImage, const void *depthImage, const uint64_t timeStamp)> callback);
		auto GetRawImage(RS_400_STREAM_TYPE streamType, rs2_format format);*/
	

		camera_info info;
		std::uint8_t* leftImage;
		std::uint8_t* rightImage;
		std::uint8_t* colorImage;
		std::uint8_t* depthImage;


	private:
		RS_400_STREAM_TYPE m_stream2Enum(string streamName);
		RS_400_FORMAT m_format2Enum(rs2_format format);
		RS_400_RESOLUTION m_resolution2Enum(string resolution);
		RS_400_FPS m_fps2Enum(int fps);
		void m_getProfile(vector<stream_profile> &profile_set);
		/*std::function<void(const void *leftImage, const void *rightImage, const void *colorImage, const uint64_t timeStamp)> callback;
		std::vector<rs2::stream_profile> depthProfiles;
		std::vector<rs2::stream_profile> colorProfile;
		std::unique_ptr<uint16_t[]> lrImage[2];*/


		rs2::context* m_context;
		rs2::device m_device;
		vector<rs2::sensor> m_sensors;
		rs2::sensor m_stereoSensor;
		rs2::sensor m_colorSensor;
		std::map<int, std::map<int, pair<int, rs2::stream_profile>>> m_streoUniqueStreams;
		std::map<int, std::map<int, pair<int, rs2::stream_profile>>> m_colorUniqueStreams;
		rs2::frame_queue m_depthFrameQueue;
		rs2::frame_queue m_ir_FrameQueue;
		rs2::frame_queue m_ir1_FrameQueue;
		rs2::frame_queue m_ir2_FrameQueue;
		rs2::frame_queue m_colorFrameQueue;
		bool m_colorStreamCheck;
		bool m_depthStreamCheck;
		bool m_irStreamCheck;
		bool m_ir1StreamCheck;
		bool m_ir2StreamCheck;
		RS_400_SENSOR m_selectedSensor;

		/*std::unique_ptr<uint8_t[]> m_grayImage;
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
		bool bColorEnabled;*/
		#ifdef _WIN32
			CRITICAL_SECTION m_mutex;
		#else
			pthread_mutex_t m_mutex;
		#endif
	};
}


#endif
