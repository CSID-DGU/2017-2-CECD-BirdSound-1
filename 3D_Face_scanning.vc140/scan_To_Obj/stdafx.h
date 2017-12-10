// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#pragma comment(lib, "pcl_common_debug.lib")
#pragma comment(lib, "pcl_visualization_debug.lib")

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
#include "targetver.h"




// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
