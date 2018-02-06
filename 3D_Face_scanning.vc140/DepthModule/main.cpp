#pragma once

#include"vtkInteractorStyle.h"
#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);
//#include "scan.h"
#include "device.h"
#include<omp.h>

int main(void) {
	Realsense realsense;
	realsense.init();
	realsense.info(0);
	realsense.startStreaming(0, depth);
	rs2::frame frame = realsense.capture(0, depth);
	vtkPoints *points = realsense.frameToVtkPoints(frame);
		
	realsense.stopStreaming(0, depth);
	float average = 0.0f;
	const int N = 100;
	average = 0.0f;

	for (int i = 0; i < N; i++)
	{
		float start = omp_get_wtime();
		realsense.MeshConstruct(points);
		average += (omp_get_wtime() - start);
	}
	std::cout << "그냥 "<<(average /= N);
	average = 0.0f;
	printf("\n");

	for (int i = 0; i < N; i++)
	{
		float start = omp_get_wtime();
		realsense.MeshConstructWithOMP(points, 3, 4);/*intel compiler의 경우 4개*/
		average += (omp_get_wtime() - start);
	}
	std::cout << "omp적용 "<<(average /= N);
	average = 0.0f;
	printf("\n");

	for (int i = 0; i < N; i++)
	{
		float start = omp_get_wtime();
		realsense.MeshConstructWithOMPnSIMD(points, 3, 4);
		average += (omp_get_wtime() - start);
	}
	std::cout << "omp with simd " << (average /= N);
	average = 0.0f;

	

	cout << "IS IT OK??" << endl;
}

/*
0.07초 정도 mesh구축에 소요.
*/