#pragma once
#include <cstdint>
#include <vector>
namespace CustomCalibWrapper
{
	class CustomCalibrationWrapper
	{
	private:
		void* mData;
		void *mRs400Device;
	public:
		CustomCalibrationWrapper(void *rs400Dev, int chessboardWidth, int
			chessboardHeight, float chessboardSquareSize, int numCameras, int numImages);
		~CustomCalibrationWrapper();
		bool AddImage(uint8_t* image, int width, int height, int stride, int
			cameraIndex, int imageIndex);
		int CalculateCalibration(int lrWidth, int lrHeight, int rgbWidth, int
			rgbHeight);
	};
}