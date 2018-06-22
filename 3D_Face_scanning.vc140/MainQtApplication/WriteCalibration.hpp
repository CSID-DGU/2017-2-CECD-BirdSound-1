#pragma once

#include <fstream>

namespace CalibParamXmlWrite
{
	void WriteCustomCalibrationParametersToFile(std::string fileName, const int resolutionLeftRight[2], const double focalLengthLeft[2], const double principalPointLeft[2],
		const double distortionLeft[5], const double focalLengthRight[2], const double principalPointRight[2], const double distortionRight[5],
		const double rotationLeftRight[9], const double translationLeftRight[3], const bool hasRGB, const int resolutionRGB[2],
		const double focalLengthRGB[2], const double principalPointRGB[2], const double distortionRGB[5], const double rotationRGB[9], const double translationRGB[3])
	{
		std::ofstream file;
		file.open(fileName, std::ios::out);
		file << "<?xml version=\"1.0\"?>\n";
		file << "<Config>\n";
		file << "    <param name = \"ResolutionLeftRight\">\n";
		file << "        <value>" << resolutionLeftRight[0] << "</value>\n";
		file << "        <value>" << resolutionLeftRight[1] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"FocalLengthLeft\">\n";
		file << "        <value>" << focalLengthLeft[0] << "</value>\n";
		file << "        <value>" << focalLengthLeft[1] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"PrincipalPointLeft\">\n";
		file << "        <value>" << principalPointLeft[0] << "</value>\n";
		file << "        <value>" << principalPointLeft[1] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"DistortionLeft\">\n";
		file << "        <value>" << distortionLeft[0] << "</value>\n";
		file << "        <value>" << distortionLeft[1] << "</value>\n";
		file << "        <value>" << distortionLeft[2] << "</value>\n";
		file << "        <value>" << distortionLeft[3] << "</value>\n";
		file << "        <value>" << distortionLeft[4] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"FocalLengthRight\">\n";
		file << "        <value>" << focalLengthRight[0] << "</value>\n";
		file << "        <value>" << focalLengthRight[1] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"PrincipalPointRight\">\n";
		file << "        <value>" << principalPointRight[0] << "</value>\n";
		file << "        <value>" << principalPointRight[1] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"DistortionRight\">\n";
		file << "        <value>" << distortionRight[0] << "</value>\n";
		file << "        <value>" << distortionRight[1] << "</value>\n";
		file << "        <value>" << distortionRight[2] << "</value>\n";
		file << "        <value>" << distortionRight[3] << "</value>\n";
		file << "        <value>" << distortionRight[4] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"RotationLeftRight\">\n";
		file << "        <value>" << rotationLeftRight[0] << "</value>\n";
		file << "        <value>" << rotationLeftRight[1] << "</value>\n";
		file << "        <value>" << rotationLeftRight[2] << "</value>\n";
		file << "        <value>" << rotationLeftRight[3] << "</value>\n";
		file << "        <value>" << rotationLeftRight[4] << "</value>\n";
		file << "        <value>" << rotationLeftRight[5] << "</value>\n";
		file << "        <value>" << rotationLeftRight[6] << "</value>\n";
		file << "        <value>" << rotationLeftRight[7] << "</value>\n";
		file << "        <value>" << rotationLeftRight[8] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"TranslationLeftRight\">\n";
		file << "        <value>" << translationLeftRight[0] << "</value>\n";
		file << "        <value>" << translationLeftRight[1] << "</value>\n";
		file << "        <value>" << translationLeftRight[2] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"HasRGB\">\n";
		file << "        <value>" << (int)hasRGB << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"ResolutionRGB\">\n";
		file << "        <value>" << resolutionRGB[0] << "</value>\n";
		file << "        <value>" << resolutionRGB[1] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"FocalLengthRGB\">\n";
		file << "        <value>" << focalLengthRGB[0] << "</value>\n";
		file << "        <value>" << focalLengthRGB[1] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"PrincipalPointRGB\">\n";
		file << "        <value>" << principalPointRGB[0] << "</value>\n";
		file << "        <value>" << principalPointRGB[1] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"DistortionRGB\">\n";
		file << "        <value>" << distortionRGB[0] << "</value>\n";
		file << "        <value>" << distortionRGB[1] << "</value>\n";
		file << "        <value>" << distortionRGB[2] << "</value>\n";
		file << "        <value>" << distortionRGB[3] << "</value>\n";
		file << "        <value>" << distortionRGB[4] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"RotationLeftRGB\">\n";
		file << "        <value>" << rotationRGB[0] << "</value>\n";
		file << "        <value>" << rotationRGB[1] << "</value>\n";
		file << "        <value>" << rotationRGB[2] << "</value>\n";
		file << "        <value>" << rotationRGB[3] << "</value>\n";
		file << "        <value>" << rotationRGB[4] << "</value>\n";
		file << "        <value>" << rotationRGB[5] << "</value>\n";
		file << "        <value>" << rotationRGB[6] << "</value>\n";
		file << "        <value>" << rotationRGB[7] << "</value>\n";
		file << "        <value>" << rotationRGB[8] << "</value>\n";
		file << "    </param>\n";
		file << "    <param name = \"TranslationLeftRGB\">\n";
		file << "        <value>" << translationRGB[0] << "</value>\n";
		file << "        <value>" << translationRGB[1] << "</value>\n";
		file << "        <value>" << translationRGB[2] << "</value>\n";
		file << "    </param>\n";
		file << "</Config>\n";
		file.close();
	}

}
