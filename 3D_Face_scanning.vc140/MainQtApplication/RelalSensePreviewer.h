//#pragma once
//#ifndef DEVICE_H
//#define DEVICE_H
//#define MAX_CAM_NUM 3
//#define MIN_CAM_NUM 0
//
//#ifdef Q_FOREACH
//#undef Q_FOREACH
//#endif
//
////#define STB_IMAGE_WRITE_IMPLEMENTATION
////#include "stb_image_write.h"
//
////#include "libRealsense2\rs.hpp"
//#include"librealsense2/rs.hpp"
//#include <iostream>
//#include <iomanip>
//#include <cstdint>
//#include <sstream>
//#include <map>
//
//#include"vtkActor.h"
//#include"vtkProperty.h"
//#include"vtkRenderWindow.h"
//#include"vtkRenderer.h"
//#include<vtkCellArray.h>
//
//#include <vtkCamera.h>
//#include<vtkRenderer.h>
//
//#include"vtkSphereSource.h"
//#include"vtkSTLWriter.h"
//#include"vtkOBJExporter.h"
//
//#include<vtkPolyData.h>
//#include<vtkPolyDataMapper.h>
//#include<vtkPoints.h>
//
//#include"MeshIO.h"
//#include"ImageIO.h"
//
//#include"vtkRenderWindowInteractor.h"
//#include<string>
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                     These parameters are reconfigurable                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define STREAM          RS2_STREAM_DEPTH  // rs2_stream is a types of data provided by RealSense device           //
//#define FORMAT          RS2_FORMAT_Z16    // rs2_format is identifies how binary data is encoded within a frame   //
//#define WIDTH           640               // Defines the number of columns for each frame                         //
//#define HEIGHT          480               // Defines the number of lines for each frame                           //
//#define FPS             30                // Defines the rate of frames per second                                //
//#define STREAM_INDEX    0                 // Defines the stream index, used for multiple streams of the same type //
//#define HEIGHT_RATIO    20                // Defines the height ratio between the original frame to the new frame //
//#define WIDTH_RATIO     10                // Defines the width ratio between the original frame to the new frame  //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//#define ROWS          (HEIGHT / HEIGHT_RATIO) // Each row represented by 20 rows in the original frame
//#define ROW_LENGTH    (WIDTH / WIDTH_RATIO) // Each column represented by 10 columns in the original frame
//#define DISPLAY_SIZE  ((ROWS + 1) * (ROW_LENGTH + 1))
//#define BUFFER_SIZE   (DISPLAY_SIZE * sizeof(char))
//
//
//
//
//enum { color, depth };
//
//
//class Realsense {
//
//	enum class filetype { stl, obj };
//	typedef struct unit
//	{
//		std::map<int, rs2::frame> frames_per_stream;
//		rs2::pipeline pipe;
//		rs2::pipeline_profile profile;
//	} unit;
//	uint32_t deviceNum = NULL;
//	rs2::device_list deviceList;
//	std::map <int, unit> pipe_map;
//
//public:
//	void init();
//	void info(int);
//	void startStreaming(int, int);
//	void stopStreaming(int, int);
//	rs2::frame Realsense::capture(int devNum, int streamType, int restNum = 10);
//	std::vector<rs2::frame> Realsense::capture(int devNum, int streamType, int frameNum, int restNum = 10);
//	std::string Realsense::saveImage(rs2::frame &frame, std::string filepath, int filetype);
//	vtkPoints* Realsense::frameToVtkPoints(rs2::frame &frame);
//	/*1이면 stl 2면 obj로 저장*/
//	void MeshConstruct(vtkPoints *points, int saveType = 3);
//	bool isInit();
//	void GetVideoStreamIntrinsics()
//	{
//		rs2::pipeline pipe;
//		rs2::pipeline_profile selection = pipe.start();
//		auto depth_stream = selection.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>();
//		auto resolution = std::make_pair(depth_stream.width(), depth_stream.height());
//		auto i = depth_stream.get_intrinsics();
//		auto principal_point = std::make_pair(i.ppx, i.ppy);
//		auto focal_length = std::make_pair(i.fx, i.fy);
//		rs2_distortion model = i.model;
//	}
//private:
//
//	void restFrame(unit &cam_unit, int num);
//
//
//
//private:
//	const double INF = 9999999999999;
//	const int height = 720;
//	const int width = 1280;
//	double getDistane(double *src, double *tar);
//};
//
class RelalSensePreviewer {};
//class RelalSensePreviewer
//{
//public:
//	RelalSensePreviewer();
//	~RelalSensePreviewer();
//	Realsense*										D415;
//	MeshIO*											m_MeshIO;
//	ImageIO*										m_ImageIO;
//
//	vtkPolyData*									m_PolyData;
//	vtkPolyData* GetPolyData()						{ return m_PolyData; }
//
//	vtkImageData*									m_ImageData;
//	vtkImageData* GetImageData()					{ return m_ImageData; }
//
//	vtkPolyDataMapper*								m_Mapper;
//	vtkPolyDataMapper* GetMapper()					{ return m_Mapper; }
//
//	vtkTexture*										m_Texture;
//	vtkTexture* GetTexture()						{ return m_Texture; }
//	int												m_IsTexture;
//	int IsTexture()									{ return m_IsTexture; };
//
//	vtkActor*										m_Actor;
//	vtkActor* GetActor()							{ return m_Actor; }
//
//	vtkRenderer*									m_Renderer;
//	vtkRenderer* GetRenderer()						{ return m_Renderer; }
//
//	vtkRenderWindow*								m_RenWin;
//	vtkRenderWindow* GetRenderWindow()				{ return m_RenWin; }
//
//
//	int InitializeVariables();
//	int DestroyVariables();
//	void ConnectSceneToCtrl(void* uiCtrl, int xCtrlSize, int yCtrlSize);
//	int CreateModel(std::string meshPath, int extType);
//	int CreateTexture(std::string imgPath, int extType);
//	int ReleaseModel();
//	int CaptureSave(std::string imagePath, int extType, int sizeRatio);
//	int MeshSave(std::string meshPath, int extType);
//	int TextureMeshSave(std::string meshPath, int meshExtType, std::string imagePath, int imgExtType);
//	int NonTextureMeshSave(std::string meshPath, int meshExtType);
//	void Rendering();
//	int Create2DScene();
//
//	void drawStream()
//	{
//		if(!D415->isInit())
//			D415->init();
//		rs2::frame *frame=D415->getStream();
//		rs2_frame;
//		D415->frameToVtkPoints(frame[0]);
//		
//	}
//
//};
//
//#endif