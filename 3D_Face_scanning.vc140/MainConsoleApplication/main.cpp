#include "libRealsense2\rs.hpp"
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;


int main(int argc, char * argv[]) {
	rs2::context ctx;
	auto devl = ctx.query_devices();
	auto dev = devl[0];
	cout << " Device info: \n";
	for (auto j = 0; j < RS2_CAMERA_INFO_COUNT; ++j)
	{
		auto param = static_cast<rs2_camera_info>(j);
		if (dev.supports(param))
			cout << "    " << left << setw(30) << rs2_camera_info_to_string(rs2_camera_info(param))
			<< ": \t" << dev.get_info(param) << endl;
	}
	cout << "eee";
}