# Project Configure
플랫폼 : Windows 8.1  
도구집합 : Visual Studio 2015 (v140)  

## General(일반)
출력 디렉터리 :
```..\..\bin\$(Platform)\ ```  
**\* 위 디렉토리에 OpenNI2.dll와 realsense-d.dll가 있어야함.**

## C/C++
전처리기 정의 : ```WIN32;_DEBUG;_CONSOLE;_LIB;%(PreprocessorDefinitions)```  
추가포함 디렉터리 : ```../../\third_party\glfw\include;../../\include;%OPENNI2_INCLUDE%;%PCL_ROOT%\include\pcl-1.8;%PCL_ROOT%\3rdParty\Boost\include\boost-1_61;%PCL_ROOT%\3rdParty\Eigen\eigen3;%PCL_ROOT%\3rdParty\VTK\include\vtk-7.0;%PCL_ROOT%\3rdParty\Qhull\include;%PCL_ROOT%\3rdParty\FLANN\include;%(AdditionalIncludeDirectories)```

## 링커
추가포함 디렉터리 : ```..\..\bin\$(Platform)\;%PCL_ROOT%\3rdParty\VTK\lib;%PCL_ROOT%\3rdParty\FLANN\lib;%PCL_ROOT%\3rdParty\Qhull\lib;%PCL_ROOT%\3rdParty\Boost\lib;%PCL_ROOT%\lib;%OPENNI2_LIB%;%(AdditionalIncludeDirectories)```  
추가 종속성 : ```opengl32.lib;glu32.lib;realsense-d.lib;OpenNI2.lib;%(AdditionalDependencies) ```
