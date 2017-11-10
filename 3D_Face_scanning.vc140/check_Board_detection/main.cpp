#pragma warning (disable : 4996)

#include<iostream>
#include<librealsense/rs.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\calib3d\calib3d.hpp>
using namespace rs;
using namespace std;
using namespace cv;

int main()
{
	context ctx;
	device *dev = ctx.get_device(0);
	std::vector<rs::device *> devices;

	if (ctx.get_device_count() <= 0)
	{
		std::cout << "No devices connected!!\n";
		return -1;
	}
	
	for (int i = 0; i < ctx.get_device_count(); ++i)devices.push_back(ctx.get_device(i));
	// Configure and start our devices
	for (auto dev : devices)
	{
		std::cout << "Starting " << dev->get_name() << "... ";
		dev->enable_stream(rs::stream::color, rs::preset::best_quality);
		dev->start();
	}

	Mat outimage;
	vector <Point2f> out_centers;
	//vector <Point2f> centers;

	const int GridCol = 11;
	const int GirdRow = 8;
	
	while (1) 
	{
		const uint8_t * color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);

		for(int i=0;i<30;i++)
		dev->wait_for_frames();
		color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);
		
		Mat image(Size(640, 480), CV_8UC3, (void*)color_image, Mat::AUTO_STEP);


		//cvtColor(image, image, CV_RGB2GRAY);
		//image=imread("cow.jpg");
		std::cout << "Start Finding\n";

		bool found = false;
		for (int i = GirdRow; i >= 3; i--)
		{
			found = false;
			for (int j = GridCol; j >= 3; j--)
			{
				Size ss(j, i); vector <Point2f> out_centers;
				outimage = image;

				std::cout << "Start Finding 가로 세로" << j << " " << i << "\n";
				found = findChessboardCorners(outimage, ss, out_centers);

				if (found > 0)
				{
					drawChessboardCorners(outimage, ss, out_centers, found);
					cout << "find: " << found << std::endl;

					for(int i=0;i<out_centers.size();i++)
						std::cout << out_centers[i].x << " " << out_centers[i].y << "\n";
					break;
				}

				else cout << "find: " << found << std::endl;

			}

			if (found > 0)
			{
				std::cout << "Hi";
				break;
			}
		}


		if (found > 0)
		{
			outimage = image;
			break;
		}

		outimage = image;
		break;
	}
	//display the result
	cv::namedWindow("Display window", WINDOW_AUTOSIZE);
	cv::imshow("Display window", outimage);

	cv::waitKey(0);
	return 0;
}

//
//int main()
//{
//	Size size(5,5);
//	Mat outimage;
//	
//	//vector <Point2f> centers;
//	
//	//cvtColor(outimage, outimage, CV_RGB2GRAY);
//	
//	for (int i=6;i>=3;i--) 
//	{
//		bool found = false;
//		bool flag = false;
//		for (int j=6;j>=3;j--)
//		{
//			if (j == 5 && i == 5)std::cout << "Nellow";
//			Size ss(j, i); vector <Point2f> out_centers;
//			outimage = imread("cow.jpg");
//			
//			std::cout << "Start Finding 가로 세로"<<j<<" "<<i<<"\n";
//			bool found = findChessboardCorners(outimage, ss, out_centers);
//			
//			if (found > 0)
//			{
//				drawChessboardCorners(outimage, ss, out_centers, found);
//				cout << "bfind: " << found << std::endl;
//				flag = true;
//				break;
//			}
//
//			else cout << "find: " << found<<std::endl;
//			
//		}
//
//		if (flag) 
//		{
//			std::cout << "Hi";
//			break; 
//		}
//	}
//
//	cv::namedWindow("Display window", WINDOW_AUTOSIZE);
//	cv::imshow("Display window", outimage);
//
//	cv::waitKey(0);
//	return 0;
//}