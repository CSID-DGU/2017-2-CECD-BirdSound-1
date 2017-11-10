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

	const int GridCol = 10;
	const int GirdRow = 7;
	

	const uint8_t * color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);

	for (int i = 0; i<30; i++)
		dev->wait_for_frames();
	color_image = (const uint8_t *)dev->get_frame_data(rs::stream::color);

	Mat image(Size(640, 480), CV_8UC3, (void*)color_image, Mat::AUTO_STEP);


	//cvtColor(image, image, CV_RGB2GRAY);
	//image=imread("cow.jpg");
	std::cout << "Start Finding\n";

	int col, row;
	bool found = false;
	for (int i = GirdRow; i >= 3; i--)
	{
		found = false; int j;
		for (j = GridCol; j >= 3; j--)
		{
			Size ss(j, i);
			outimage = image;

			std::cout << "Start Finding 가로 세로" << j << " " << i << "\n";
			found = findChessboardCorners(outimage, ss, out_centers);

			if (found > 0)
			{
				drawChessboardCorners(outimage, ss, out_centers, found);
				cout << "find: " << found << std::endl;

				for (int i = 0; i<out_centers.size(); i++)
					std::cout << out_centers[i].x << " " << out_centers[i].y << "\n";
				break;
			}

			else cout << "find: " << found << std::endl;

		}

		if (found > 0)
		{
			//std::cout << "Hi";
			col = j;
			row = i;
			break;
		}
	}


	if (found > 0)outimage = image;
	

	outimage = image;
	
	//display the result
	for (int i = 0; i<out_centers.size(); i++)
		std::cout << out_centers[i].x << " " << out_centers[i].y << "\n";

	float sumOfdis = 0.0f;
	float average = 0.0f;
	std::vector<float> dis;

	std::cout << "#Detected Point is " << out_centers.size() << "\n";
	
	for (int i = 0; i < out_centers.size()-1; i++)
	{
		if (i == col-1)continue;

		float _distance;
		float x1, x2;
		float y1, y2;

		x1 = out_centers[i].x;
		y1 = out_centers[i].y;
		
		x2 = out_centers[i+1].x;
		y2 = out_centers[i+1].y;
		
		_distance = sqrt((x1 - x2)*(x1 - x2) + (y2 - y1)*(y2 - y1));

		std::cout << _distance << "\n";
		sumOfdis += _distance;
		dis.push_back(_distance);
		
	} 
	//average /= sumOfdis;
	////std::cout << "Average of distance is "<<average;
	////std::cout << "average of (square Deviation) is " ;

	//float stdv = 0.0f;

	//for (int i = 0; i < dis.size(); i++)
	//{
	//	stdv+=(dis[i] - average);
	//}

	//stdv /= (out_centers.size() - 1);
	//std::cout << stdv << "\n";

	cv::namedWindow("Display window", WINDOW_AUTOSIZE);
	cv::imshow("Display window", outimage);
	cv::waitKey(0);

	return 0;
}
