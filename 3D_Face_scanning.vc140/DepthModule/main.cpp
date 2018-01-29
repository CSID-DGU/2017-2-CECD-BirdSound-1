#pragma once

#include"vtkInteractorStyle.h"
#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);
//#include "scan.h"
#include "device.h"


int main(void) {
	Realsense realsense;
	realsense.init();
	realsense.info(0);
	realsense.startStreaming(0, depth);
	rs2::frame frame = realsense.capture(0, depth);
	vtkPoints *points = realsense.frameToVtkPoints(frame);
		
	realsense.stopStreaming(0, depth);
	realsense.MeshConstruct(points);

	cout << "IS IT OK??" << endl;
}