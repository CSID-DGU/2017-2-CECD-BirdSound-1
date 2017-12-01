#include <librealsense/rs.hpp>
#include<iostream>
#include <cstdio>
#include<fstream>
#include"Frame.h"

double yaw, pitch, lastX, lastY; int ml;

int main() //try
{
	rs::log_to_console(rs::log_severity::warn);
	rs::context ctx;
	printf("There are %d connected RealSense devices.\n", ctx.get_device_count());
	if (ctx.get_device_count() == 0) return EXIT_FAILURE;

	rs::device * dev = ctx.get_device(0);
	printf("\nUsing device 0, an %s\n", dev->get_name());

	Page pa;
	dev->enable_stream(rs::stream::depth, rs::preset::best_quality);
	dev->enable_stream(rs::stream::color, rs::preset::best_quality);
	dev->start();

	std::string name1, name2;

	std::cout << "depth\n";
	std::cin >> name1;
	std::cout << "color\n";
	std::cin >> name2;

	std::ofstream off1(name1);// ("depth.txt");
	std::ofstream off2(name2);

		
	for (int loop = 0; loop < 3; loop++)
	{

		//for (int i = 0; i < 30; i++)dev->wait_for_frames();
		dev->wait_for_frames();
		//std::cout << "@@";
		// Retrieve our images
		const uint16_t * depth_image = (const uint16_t *)dev->get_frame_data(rs::stream::depth);
		const uint8_t * color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);

		// Retrieve camera parameters for mapping between depth and color
		rs::intrinsics depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
		rs::extrinsics depth_to_color = dev->get_extrinsics(rs::stream::depth, rs::stream::color);
		rs::intrinsics color_intrin = dev->get_stream_intrinsics(rs::stream::color);
		float scale = dev->get_depth_scale();

		int index = 0;
		for (int dy = 0; dy < depth_intrin.height; ++dy)
		{
			for (int dx = 0; dx < depth_intrin.width; ++dx)
			{
				uint16_t depth_value = depth_image[dy * depth_intrin.width + dx];
				float depth_in_meters = depth_value * scale;


				
				rs::float2 depth_pixel = { (float)dx, (float)dy };   //2차원 픽셀을 구성 
				rs::float3 depth_point = depth_intrin.deproject(depth_pixel, depth_in_meters); //2차원에 실제 z값을 대입함 
				rs::float3 color_point = depth_to_color.transform(depth_point); //depth포인트를 color가 맵핑되는 포인트 좌표로 변환 
				rs::float2 color_pixel = color_intrin.project(color_point); //컬러

				//std::cout<<
				//std::cin >> off;									//if (depth_value == 0)
				
				//std::cin>>

				//std::cout << -depth_point.z << "\n";
				off1 << "" << depth_point.x << "\t" << depth_point.y << "\t" << depth_point.z << std::endl; //depth 
				off2 << "" << color_pixel.x << "\t" << color_pixel.y << "\t" << std::endl; //color
																							//I_C_point++;

				//off<< depth_image
				//off<<depth_image/
				//if (depth_in_meters == 0) continue;
				pa.setData(index, depth_point.z);
				index++;

				// Skip over pixels with a depth value of zero, which is used to indicate no data
			}
		}

		off1 << "\n";
		off2 << "\n";
	}

	std::cout << "촬영끝\n";
	pa.setStat();

	
	pa.printValidFrame(0.002);
	std::cout << "Valid z data file name\n";
	pa.prinValidData();

	std::cout << "All z data file name\n";
	//pa.printValidFrame(0.005);
	pa.printAllData();
	pa.printStat();
	return EXIT_SUCCESS;
}

//catch (const rs::error & e)
//{
//	// Method calls against librealsense objects may throw exceptions of type rs::error
//	printf("rs::error was thrown when calling %s(%s):\n", e.get_failed_function().c_str(), e.get_failed_args().c_str());
//	printf("    %s\n", e.what());
//	return EXIT_FAILURE;
//}
