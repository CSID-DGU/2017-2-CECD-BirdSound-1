#include<iostream>
#include<string>
#include"Scan.h"


#include"../DepthModule/device.h"
int main()
{
	std::string serial= realsense::getFirstSerial();
	realsense::Device *dev=new realsense::Device(serial);
	Scan *sc = new Scan();
	dev->selectSensorAndStreamProps();
	

	for (int i = 0; i < 15; i++) 
	{
		rs2::frame fra = dev->capture(realsense::RS400_STREAM_DEPTH);
		sc->InsertFrame(fra);
	}

	std::cout << "ÃÔ¿µ ¿Ï·á";
	
	clock_t begin;
	begin = clock();
	//sc->frame2Points(fra);
	sc->frames2Points();
	printf("%lf", (double(clock()) - double(begin)) / 1000.0);
	sc->MeshConstruction(0, 0,4);



	return 0;
}