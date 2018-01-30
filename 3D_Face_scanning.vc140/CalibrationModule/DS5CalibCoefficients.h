/*
* INTEL CORPORATION PROPRIETARY INFORMATION
* This software is supplied under the terms of a license agreement
* or nondisclosure agreement with Intel Corporation and may not be
* copied or disclosed except in accordance with the terms of that
* agreement.
* Copyright(c) 2016-2017 Intel Corporation. All Rights Reserved.
*/
/** @file DS5CalibCoefficients.h */
#pragma once
#include <cstdint>
#include <vector>
#include <cstddef>
namespace dscam
{
#pragma pack(push, 1)
	//! Calibration table header for DS5. Generic for all tables.
	struct DS5CalibrationTableHeader
	{
		uint16_t version; //!< Table version
		uint16_t tableType; //!< Table type
		uint32_t tableSize; //!< Table size
		uint32_t fullVersion; //!< Complete version of the table
		uint32_t crc32; //!< CRC32 of the content
	};
	//! DS5 calibration intrinsics parameters for non-rectified camera
	struct DS5CoeffsIntrinsics
	{
		float fx; //!< Focal length in x axis, normalizedby width
		float fy; //!< Focal length in y axis, normalizedby height
		float px; //!< Principal point x axis coordinate,normalized by width
		float py; //!< Principal point y axis coordinate,normalized by height
		float k[5]; //!< Distortion coefficients
	};
	//! DS5 calibration intrinsics parameters for rectified camera
	struct DS5CoeffsMode
	{
		float rfx; //!< Rectified focal length in x axis
		float rfy; //!< Rectified focal length in y axis
		float rpx; //!< Rectified principal point x axiscoordinate
		float rpy; //!< Rectified principal point y axiscoordinate
	};
	//! DS5 calibration coefficients. Contains rectification parameters and data used by thechip to produce depth map.
	struct DS5CalibrationCoefficients
	{
		DS5CoeffsIntrinsics instrinsicsLeft; //!< Intrinsics of the left camera
		DS5CoeffsIntrinsics instrinsicsRight; //!< Intrinsics of the right camera
		float Rleft[9]; //!< Inverse rotation of the left camerain rectified coordinate system
		float Rright[9]; //!< Inverse rotation of the left camerain rectified coordinate system
		float B; //!< Baseline (maintains polarity)
		uint32_t useBrownModel; //!< Whether to use Brown or TYZXdistrotion model(tangential distortion)
		uint8_t reserved[88]; //!< Reserved
	};
	//! DS5 recitifed resolution index
	enum DS5CoeffsModeIndex
	{
		DS5M_1920_1080 = 0, //!< 1920x1080 rectified resolution (R8L8only)
		DS5M_1280_720 = 1, //!< 1280x720 rectified resolution
		DS5M_640_480 = 2, //!< 640x480 rectified resolution
		DS5M_848_480 = 3, //!< 848x480 rectified resolution
		DS5M_640_360 = 4, //!< 640x360 rectified resolution
		DS5M_424_240 = 5, //!< 424x240 rectified resolution
		DS5M_320_240 = 6, //!< 320x240 rectified resolution
		DS5M_480_270 = 7, //!< 480x270 rectified resolution
		DS5M_1280_800 = 8, //!< 1280x800 rectified resolution (R8L8only)
		DS5M_960_540 = 9 //!< 960x540 rectified resolution
	};
	//! DS5 calibration type
	enum DS5CalibrationType
	{
		DS5CT_Custom = 0x00, //!< Custom calibration type (orotherwise undefined)
		DS5CT_Production = 0x01, //!< Production calibration
		DS5CT_Technician = 0x02, //!< Technician calibration
		DS5CT_OEM = 0x03, //!< OEM calibration
		DS5CT_DynamicTargetless = 0x04, //!< Dynamic calibration (targetless)
		DS5CT_DynamicWithTarget = 0x05, //!< Dynamic calibration (with target)
		DS5CT_TechnicianNonRT = 0x06, //!< Technician calibration (non-RTalgorithm)
		DS5CT_Validation = 0x07, //!< Calibration done for validatoin purposes
		DS5CT_CustomerFlag = 0x1000 //!< Customer used their own calibration.This is used as a flag and sticks after dynamic calibration.
	};

	//! DS5 calibration coefficients table. Table ID is 0x19.
	struct DS5CalibrationCoefficientsTable
	{
		DS5CalibrationTableHeader header; //!< Header
		DS5CalibrationCoefficients coeffs; //!< Coefficients
		DS5CoeffsMode modes[12]; //!< Rectified camera parameters. Eachentry in the table corresponds to a resolution
		uint8_t reserved2[64]; //!< Reserved
	};

	//! Structure used to update the calibration during live streaming using the CALIBRECALCcommand
	struct DS5CalibrationCoefficientsUpdateParam
	{
		DS5CalibrationCoefficients coeffs; //!< Coefficients
		DS5CoeffsMode mode; //!< Rectified camera parameters for thecurrent resolution
	};

	//! DS5 raw calibration intrinsics parameters for non-rectified camera
	struct DS5CalParameters
	{
		float K[9]; //!< Intrinsics stored as 3x3 matrix,normalized by width and height
		float d[5]; //!< Distortion coefficients
		float R[3]; //!< The rotation of the camera asRodriquez rotation vector
		float T[3]; //!< The translation of the camera,passed as T = -Rt, where t is the translation vector
	};

	//! DS5 depth calibration table for versions 2. and 3.0. Contains raw calibraiton data. Table ID = 0x1F.
	struct DS5DepthCalibrationTableV2030
	{
		DS5CalibrationTableHeader header; //!< Header
		uint32_t rmax; //!< Maximum permissible rotation
		DS5CalParameters parametersLeft; //!< Parameters of the left camera
		DS5CalParameters parametersRight; //!< Parameters of the right camera
		float Rd[3]; //!< Rotation vector of the depth cameraagainst world coordinates.Stored as Rodriguez rotation vector.
		float Td[3]; //!< The new translation between nonrectified left and right camera, passed as T=-Rt, where t is the translation vector and Ris the rotaion matrix
		uint16_t imageWidth; //!< Width of the images used duringcalibration
		uint16_t imageHeight; //!< Height of the images used duringcalibration
		uint8_t reserved[48]; //!< Reserved
	};
	//! DS5 depth calibration table. Contains raw calibraiton data. Table ID = 0x1F.
	struct DS5DepthCalibrationTable
	{
		DS5CalibrationTableHeader header; //!< Header
		uint32_t rmax; //!< Maximum permissible rotation
		DS5CalParameters parametersLeft; //!< Intrinsics of the left camera
		DS5CalParameters parametersRight; //!< Intrinsics of the right camera
		float Kd[9]; //!< Intrinsics of the depth camera atcalibration resolution
		float Rd[3]; //!< Rotation vector of the depth cameraagainst world coordinates.Stored as Rodriguez rotation vector.
		float Td[3]; //!< The new translation between nonrectified left and right camera, passed as T=-Rt, where t is the translation vector and Ris the rotaion matrix
		uint16_t imageWidth; //!< Width of the images used duringcalibration
		uint16_t imageHeight; //!< Height of the images used duringcalibration
		uint16_t calibrationType; //!< Calibration type
		uint8_t reserved[10]; //!< Reserved
	};
	//! DS5 RGB calibration table. Contains RGB calibraiton data. Table ID = 0x20.
	struct DS5RGBCalibrationTable
	{
		DS5CalibrationTableHeader header; //!< Header
		DS5CalParameters parameters; //!< Intrinsics of the RGB camera
		float P[12]; //!< Projection matrix from depth tounrectified RGB camera
		uint16_t imageWidth; //!< Width of the images used duringcalibration
		uint16_t imageHeight; //!< Height of the images used duringcalibration
		float Krect[9]; //!< Intrinsics of the rectified RGBcamera
		float Rrect[9]; //!< Inverse rotation of the RGB camerain rectified coordinate system
		float Trect[3]; //!< Translation of the RGB camera inrectified coordinate system
		uint8_t reserved[24]; //!< Reserved
	};
	//! DS5 table creation status
	enum DS5TableCreationStatus
	{
		DS5CTS_OK, //!< OK
		DS5CTS_InvalidTable, //!< One of the tables was invalid
		DS5CTS_InvalidLeftRightResolution, //!< Left & Right camera resolution isnot supported
		DS5CTS_LeftIntrinsicsUnreasonable, //!< Left camera intrinsics unreasonable
		DS5CTS_RightIntrinsicsUnreasonable //!< Right camera intrinsics unreasonable
	};
	//! DS5 table parse status
	enum DS5TableParseStatus
	{
		DS5CPS_OK, //!< OK
		DS5CPS_InvalidTable, //!< Some of the tables were not valid orcorrect version
		DS5CPS_InvalidParameter //!< One of the output variables was notvalid
	};
#pragma pack(pop)
#if 0
	/** Makes sure that the table are the latest version (upgrades them if not). Additional
	elements in the calibration table
	* that cannot be recovered if the table is old will be set to 0, thus make sure that
	the version is noted properly before
	* calling this function for any disabilities.
	*
	* @param coeffsTable: The coefficients table in any supported version, which will be
	converted to latest version.
	* @param depthTable: The depth table in any supported version, which will be converted
	to latest version.
	* @param rgbTable: The RGB table in any supported version, which will be converted to
	latest version. This parameter is optional.
	* @return Will fail if the version is too old.
	*/
	bool EnsureTablesAreTheLatest(void* coeffsTable, void* depthTable, void* rgbTable =NULL);
	/** Calculates CRC32
	*
	* @param buffer: The data
	* @param length: Length of the data
	* @return CRC32 checksum
	*/
	uint32_t CalculateCrc32(uint8_t *buffer, int length);
	/** Updates CRC32 checksum in calibration coefficients table
	*
	* @param coeffsTable: The calibration coefficients table
	*/
	void UpdateCrc32(DS5CalibrationCoefficientsTable* coeffsTable);
	/** Updates CRC32 checksum in depth calibration table
	*
	* @param depthTable: The depth calibration table
	*/
	void UpdateCrc32(DS5DepthCalibrationTable* depthTable);
	/** Updates CRC32 checksum in RGB calibration table
	*
	* @param rgbTable: The RGB calibration table
	*/
	void UpdateCrc32(DS5RGBCalibrationTable* rgbTable);
	
/** Update the calibration tables with recalculated extrinsic parameters.
*
* @param coeffsTable: The calibration coefficients table
* @param depthTable: The depth calibration table
* @param rgbTable: The RGB calibration table - this parameter is optional and may be
NULL
* @param calibrationType: Method used for the re-calibration
* @param R: The new rotation between non-rectified left and right camera, passed as 3x3
rotation matrix
* @param T: The new translation between non-rectified left and right camera, passed as
T=-Rt, where t is the translation vector
* @return Whether the calibration recalculation succeeded
*/
bool UpdateCalibration(DS5CalibrationCoefficientsTable* coeffsTable,
	DS5DepthCalibrationTable* depthTable, DS5RGBCalibrationTable* rgbTable,
	DS5CalibrationType calibrationType, double R[9], double T[3]);
/** <B>INTERNAL USE ONLY!</B><BR>
* Calculates updated rectification parameters for specified resolution.
*
* @param coeffsTable: The calibration coefficients table
* @param depthTable: The depth calibration table
* @param R: The new rotation between non-rectified left and right camera, passed as 3x3
rotation matrix
* @param T: The new translation between non-rectified left and right camera, passed as
T=-Rt, where t is the translation vector
* @param modeWidth: Image width of the rectified camera
* @param modeHeight: Image height of the rectified camera
* @param mode: The parameter will be populated with the rectified camera intrinsics
* @param Rleft: The inverse rotation of the left camera in the new rectified coordinate
system
* @param Rright: The inverse rotation of the right camera in the new rectified
coordinate system
* @return Whether the calibration recalculation succeeded
*/
bool RecalculateMode(const DS5CalibrationCoefficientsTable& coeffsTable, const
	DS5DepthCalibrationTable& depthTable, double R[9], double T[3], int modeWidth, int
	modeHeight, DS5CoeffsMode& mode, double Rleft[9], double Rright[9]);
/** Creates calibration tables based on supplied parameters, which assumes that left
camera is the reference camera and is located at world origin.
*
* @param coeffsTable: The calibration coefficients table
* @param depthTable: The depth calibration table
* @param rgbTable: The RGB calibration table - this parameter is optional and may be
NULL
* @param resolutionLeftRight: The resolution of the left and right camera, specified as
[width; height]
* @param focalLengthLeft: The focal length of the left camera, specified as [fx; fy] in
pixels
* @param principalPointLeft: The principal point of the left camera, specified as [px;
py] in pixels
* @param distortionLeft: The distortion of the left camera, specified as Brown's
distortion model [k1; k2; p1; p2; k3]
* @param focalLengthRight: The focal length of the right camera, specified as [fx; fy]
in pixels
* @param principalPointRight: The principal point of the right camera, specified as
[px; py] in pixels
* @param distortionRight: The distortion of the right camera, specified as Brown's
distortion model [k1; k2; p1; p2; k3]
*@param rotationLeftRight: The rotation from the right camera coordinate system to the
left camera coordinate system, specified as a 3x3 row - major rotation matrix
* @param translationLeftRight : The translation from the right camera coordinate system
to the left camera coordinate system, specified as a 3x1 vector in milimeters
* @param hasRGB : Whether RGB camera calibration parameters are supplied
* @param resolutionRGB : The resolution of the RGB camera, specified as[width; height]
* @param focalLengthRGB : The focal length of the RGB camera, specified as[fx; fy] in
pixels
* @param principalPointRGB : The principal point of the RGB camera, specified as[px;
py] in pixels
* @param distortionRGB : The distortion of the RGB camera, specified as Brown's
distortion model[k1; k2; p1; p2; k3]
* @param rotationLeftRGB : The rotation from the RGB camera coordinate system to the
left camera coordinate system, specified as a 3x3 row - major rotation matrix
* @param translationLeftRGB : The translation from the RGB camera coordinate system to
the left camera coordinate system, specified as a 3x1 vector in milimeters
* @return When DS5CTS_OK then the tables were created successfully
*/

DS5TableCreationStatus CreateCalibrationTables(DS5CalibrationCoefficientsTable*
	coeffsTable, DS5DepthCalibrationTable* depthTable, DS5RGBCalibrationTable* rgbTable,
	const int resolutionLeftRight[2], const double focalLengthLeft[2], const double
	principalPointLeft[2],
	const double distortionLeft[5], const double focalLengthRight[2], const double
	principalPointRight[2], const double distortionRight[5], const double rotationRight[9],
	const double translationRight[3], const bool hasRGB, const int resolutionRGB[2],
	const double focalLengthRGB[2], const double principalPointRGB[2], const double
	distortionRGB[5], const double rotationRGB[9], const double translationRGB[3]);

/** Parses calibration tables into ordinary calibraiton parameters
*
* @param coeffsTable: The calibration coefficients table
* @param depthTable: The depth calibration table
* @param rgbTable: The RGB calibration table - this parameter is optional and may be
NULL
* @param resolutionLeftRight: The resolution of the left and right camera, specified as
[width; height]
* @param focalLengthLeft: The focal length of the left camera, specified as [fx; fy] in
pixels
* @param principalPointLeft: The principal point of the left camera, specified as [px;
py] in pixels
* @param distortionLeft: The distortion of the left camera, specified as Brown's
distortion model [k1; k2; p1; p2; k3]
* @param focalLengthRight: The focal length of the right camera, specified as [fx; fy]
in pixels
* @param principalPointRight: The principal point of the right camera, specified as
[px; py] in pixels
* @param distortionRight: The distortion of the right camera, specified as Brown's
distortion model [k1; k2; p1; p2; k3]
* @param rotationLeftRight: The rotation from the right camera coordinate system to the
left camera coordinate system, specified as a 3x3 rotation matrix
* @param translationLeftRight: The translation from the right camera coordinate system
to the left camera coordinate system, specified as a 3x1 vector in milimeters
* @param hasRGB: Whether RGB camera calibration parameters are supplied
* @param resolutionRGB: The resolution of the RGB camera, specified as [width; height]
* @param focalLengthRGB: The focal length of the RGB camera, specified as [fx; fy] in
pixels
* @param principalPointRGB: The principal point of the RGB camera, specified as [px;
py] in pixels
* @param distortionRGB: The distortion of the RGB camera, specified as Brown's
distortion model [k1; k2; p1; p2; k3]
* @param rotationLeftRGB: The rotation from the RGB camera coordinate system to the
left camera coordinate system, specified as a 3x3 rotation matrix
* @param translationLeftRGB: The translation from the RGB camera coordinate system to
the left camera coordinate system, specified as a 3x1 vector in milimeters
* @return When DS5CPS_OK then the tables were parsed successfully
*/
DS5TableParseStatus ParseCalibrationTables(const DS5CalibrationCoefficientsTable*
	coeffsTable, const DS5DepthCalibrationTable* depthTable, const DS5RGBCalibrationTable*
	rgbTable, int resolutionLeftRight[2], double focalLengthLeft[2], double
	principalPointLeft[2],
	double distortionLeft[5], double focalLengthRight[2], double
	principalPointRight[2], double distortionRight[5], double rotationRight[9], double
	translationRight[3], bool& hasRGB, int resolutionRGB[2], double focalLengthRGB[2], double
	principalPointRGB[2],
	double distortionRGB[5], double rotationRGB[9], double translationRGB[3]);
#endif
}