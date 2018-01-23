//#include "vtk-8.1/vtkAutoInit.h"
//VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
//VTK_MODULE_INIT(vtkInteractionStyle);
//#include <vtk-8.1/vtkSphereSource.h>
//#include <vtk-8.1/vtkPolyData.h>
//#include <vtk-8.1/vtkSmartPointer.h>
//#include <vtk-8.1/vtkPolyDataMapper.h>
//#include <vtk-8.1/vtkActor.h>
//#include <vtk-8.1/vtkRenderWindow.h>
//#include <vtk-8.1/vtkRenderer.h>
//#include <vtk-8.1/vtkRenderWindowInteractor.h>
//
//int main(int, char *[])
//{
//	// Create a sphere
//	vtkSmartPointer<vtkSphereSource> sphereSource =
//		vtkSmartPointer<vtkSphereSource>::New();
//	sphereSource->SetCenter(0.0, 0.0, 0.0);
//	sphereSource->SetRadius(5.0);
//
//	vtkSmartPointer<vtkPolyDataMapper> mapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//	mapper->SetInputConnection(sphereSource->GetOutputPort());
//
//	vtkSmartPointer<vtkActor> actor =
//		vtkSmartPointer<vtkActor>::New();
//	actor->SetMapper(mapper);
//
//	vtkSmartPointer<vtkRenderer> renderer =
//		vtkSmartPointer<vtkRenderer>::New();
//	vtkSmartPointer<vtkRenderWindow> renderWindow =
//		vtkSmartPointer<vtkRenderWindow>::New();
//	renderWindow->AddRenderer(renderer);
//	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();
//	renderWindowInteractor->SetRenderWindow(renderWindow);
//
//	renderer->AddActor(actor);
//	renderer->SetBackground(.3, .6, .3); // Background color green
//
//	renderWindow->Render();
//	renderWindowInteractor->Start();
//
//	return EXIT_SUCCESS;
//} 

#include "MainQtApplication.h"
#include <QtWidgets/QApplication>
#undef foreach //Q_FOREACH 매크로 정의 해제
#include "librealsense2/rs.hpp"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainQtApplication w;
	rs2::context ctx;
	printf("A");
	w.show();
	return a.exec();
}