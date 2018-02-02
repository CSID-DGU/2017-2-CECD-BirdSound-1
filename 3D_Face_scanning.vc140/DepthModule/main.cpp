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
	/*realsense.init();
	realsense.info(0);
	realsense.startStreaming(0, depth);
	rs2::frame frame = realsense.capture(0, depth);
	vtkPoints *points = realsense.frameToVtkPoints(frame);
		
	realsense.stopStreaming(0, depth);*/

	float start = omp_get_wtime();
	//realsense.MeshConstruct(points);
	//realsense.MeshConstructWithOMP(points,3,4);/*intel compiler의 경우 4개*/
	//realsense.MeshConstructWithOMPnSIMD(points, 3, 4);
	realsense.viewRawStream();
	std::cout << omp_get_wtime()-start << "\n";
	
	cout << "IS IT OK??" << endl;
}

/*
0.07초 정도 mesh구축에 소요.
*/