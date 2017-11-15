// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#pragma comment(lib, "pcl_common_debug.lib")
#pragma comment(lib, "pcl_features_debug.lib")
#pragma comment(lib, "pcl_filters_debug.lib")
#pragma comment(lib, "pcl_io_debug.lib")
#pragma comment(lib, "pcl_io_ply_debug.lib")
#pragma comment(lib, "pcl_kdtree_debug.lib")
#pragma comment(lib, "pcl_keypoints_debug.lib")
#pragma comment(lib, "pcl_ml_debug.lib")
#pragma comment(lib, "pcl_octree_debug.lib")
#pragma comment(lib, "pcl_outofcore_debug.lib")
#pragma comment(lib, "pcl_people_debug.lib")
#pragma comment(lib, "pcl_recognition_debug.lib")
#pragma comment(lib, "pcl_registration_debug.lib")
#pragma comment(lib, "pcl_sample_consensus_debug.lib")
#pragma comment(lib, "pcl_search_debug.lib")
#pragma comment(lib, "pcl_segmentation_debug.lib")
#pragma comment(lib, "pcl_stereo_debug.lib")
#pragma comment(lib, "pcl_surface_debug.lib")
#pragma comment(lib, "pcl_tracking_debug.lib")
#pragma comment(lib, "pcl_visualization_debug.lib")
#pragma comment(lib, "OpenNI2.lib")

#include <stdio.h>
#include <tchar.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <librealsense/rs.hpp>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>
#include "targetver.h"


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
