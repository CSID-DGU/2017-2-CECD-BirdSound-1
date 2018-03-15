## 리얼센스 v2.9.0에 명시되어있는 [헤더파일](https://github.com/IntelRealSense/librealsense/blob/v2.9.0/include/librealsense2/h/rs_option.h) 을 기준으로 설명합니다.

Normal Mode 에는 다음과 같은 rs2_option 들이 있고, 사용자는 이를 조정할 수 있다.
```
typedef enum rs2_option
{
    RS2_OPTION_BACKLIGHT_COMPENSATION                     , /**< Enable / disable color backlight compensation*/
    RS2_OPTION_BRIGHTNESS                                 , /**< Color image brightness*/
    RS2_OPTION_CONTRAST                                   , /**< Color image contrast*/
    RS2_OPTION_EXPOSURE                                   , /**< Controls exposure time of color camera. Setting any value will disable auto exposure*/
    RS2_OPTION_GAIN                                       , /**< Color image gain*/
    RS2_OPTION_GAMMA                                      , /**< Color image gamma setting*/
    RS2_OPTION_HUE                                        , /**< Color image hue*/
    RS2_OPTION_SATURATION                                 , /**< Color image saturation setting*/
    RS2_OPTION_SHARPNESS                                  , /**< Color image sharpness setting*/
    RS2_OPTION_WHITE_BALANCE                              , /**< Controls white balance of color image. Setting any value will disable auto white balance*/
    RS2_OPTION_ENABLE_AUTO_EXPOSURE                       , /**< Enable / disable color image auto-exposure*/
    RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE                  , /**< Enable / disable color image auto-white-balance*/
    RS2_OPTION_VISUAL_PRESET                              , /**< Provide access to several recommend sets of option presets for the depth camera */
    RS2_OPTION_LASER_POWER                                , /**< Power of the F200 / SR300 projector, with 0 meaning projector off*/
    RS2_OPTION_ACCURACY                                   , /**< Set the number of patterns projected per frame. The higher the accuracy value the more patterns projected. Increasing the number of patterns help to achieve better accuracy. Note that this control is affecting the Depth FPS */
    RS2_OPTION_MOTION_RANGE                               , /**< Motion vs. Range trade-off, with lower values allowing for better motion sensitivity and higher values allowing for better depth range*/
    RS2_OPTION_FILTER_OPTION                              , /**< Set the filter to apply to each depth frame. Each one of the filter is optimized per the application requirements*/
    RS2_OPTION_CONFIDENCE_THRESHOLD                       , /**< The confidence level threshold used by the Depth algorithm pipe to set whether a pixel will get a valid range or will be marked with invalid range*/
    RS2_OPTION_EMITTER_ENABLED                            , /**< Laser Emitter enabled */
    RS2_OPTION_FRAMES_QUEUE_SIZE                          , /**< Number of frames the user is allowed to keep per stream. Trying to hold-on to more frames will cause frame-drops.*/
    RS2_OPTION_TOTAL_FRAME_DROPS                          , /**< Total number of detected frame drops from all streams */
    RS2_OPTION_AUTO_EXPOSURE_MODE                         , /**< Auto-Exposure modes: Static, Anti-Flicker and Hybrid */
    RS2_OPTION_POWER_LINE_FREQUENCY                       , /**< Power Line Frequency control for anti-flickering Off/50Hz/60Hz/Auto */
    RS2_OPTION_ASIC_TEMPERATURE                           , /**< Current Asic Temperature */
    RS2_OPTION_ERROR_POLLING_ENABLED                      , /**< disable error handling */
    RS2_OPTION_PROJECTOR_TEMPERATURE                      , /**< Current Projector Temperature */
    RS2_OPTION_OUTPUT_TRIGGER_ENABLED                     , /**< Enable / disable trigger to be outputed from the camera to any external device on every depth frame */
    RS2_OPTION_MOTION_MODULE_TEMPERATURE                  , /**< Current Motion-Module Temperature */
    RS2_OPTION_DEPTH_UNITS                                , /**< Number of meters represented by a single depth unit */
    RS2_OPTION_ENABLE_MOTION_CORRECTION                   , /**< Enable/Disable automatic correction of the motion data */
    RS2_OPTION_AUTO_EXPOSURE_PRIORITY                     , /**< Allows sensor to dynamically ajust the frame rate depending on lighting conditions */
    RS2_OPTION_COLOR_SCHEME                               , /**< Color scheme for data visualization */
    RS2_OPTION_HISTOGRAM_EQUALIZATION_ENABLED             , /**< Perform histogram equalization post-processing on the depth data */
    RS2_OPTION_MIN_DISTANCE                               , /**< Minimal distance to the target */
    RS2_OPTION_MAX_DISTANCE                               , /**< Maximum distance to the target */
    RS2_OPTION_TEXTURE_SOURCE                             , /**< Texture mapping stream unique ID */
    RS2_OPTION_FILTER_MAGNITUDE                           , /**< The 2D-filter effect. The specific interpretation is given within the context of the filter */
    RS2_OPTION_FILTER_SMOOTH_ALPHA                        , /**< 2D-filter parameter controls the weight/radius for smoothing.*/
    RS2_OPTION_FILTER_SMOOTH_DELTA                        , /**< 2D-filter range/validity threshold*/
    RS2_OPTION_STEREO_BASELINE                            , /**< The distance in mm between the first and the second imagers in stereo-based depth cameras*/
    RS2_OPTION_COUNT                                      , /**< Number of enumeration values. Not a valid input: intended to be used in for-loops. */
} rs2_option;
const char* rs2_option_to_string(rs2_option option);
```

DepthModule 솔루션에 정의된(device.cpp, device.h) printSensorInfo를 통해 본 Sensor : StereoModule 을 보면 아래와 같다.

```
[Stereo Module]
   0 : Backlight Compensation is not supported
   1 : Brightness is not supported
   2 : Contrast is not supported
   3 : Exposure
      Description   : Depth Exposure
      Current Value : 33000
   4 : Gain
      Description   : UVC image gain
      Current Value : 16
   5 : Gamma is not supported
   6 : Hue is not supported
   7 : Saturation is not supported
   8 : Sharpness is not supported
   9 : White Balance is not supported
   10 : Enable Auto Exposure
      Description   : Enable Auto Exposure
      Current Value : 1
   11 : Enable Auto White Balance
      Description   : Enable Auto White Balance
      Current Value : 0
   12 : Visual Preset
      Description   : Advanced-Mode Preset
      Current Value : 0
   13 : Laser Power
      Description   : Manual laser power in mw. applicable only when laser power mode is set to Manual
      Current Value : 150
   14 : Accuracy is not supported
   15 : Motion Range is not supported
   16 : Filter Option is not supported
   17 : Confidence Threshold is not supported
   18 : Emitter Enabled
      Description   : Power of the DS5 projector, 0 meaning projector off, 1 meaning projector on, 2 meaning projector in auto mode
      Current Value : 0
   19 : Frames Queue Size
      Description   : Max number of frames you can hold at a given time. Increasing this number will reduce frame drops but increase latency, and vice versa
      Current Value : 16
   20 : Total Frame Drops is not supported
   21 : Auto Exposure Mode is not supported
   22 : Power Line Frequency is not supported
   23 : Asic Temperature is not supported
   24 : Error Polling Enabled
      Description   : Enable / disable polling of camera internal errors
      Current Value : 1
   25 : Projector Temperature is not supported
   26 : Output Trigger Enabled
      Description   : Generate trigger from the camera to external device once per frame
      Current Value : 0
   27 : Motion Module Temperature is not supported
   28 : Depth Units
      Description   : Number of meters represented by a single depth unit
      Current Value : 0.0001
   29 : Enable Motion Correction is not supported
   30 : Auto Exposure Priority is not supported
   31 : Color Scheme is not supported
   32 : Histogram Equalization Enabled is not supported
   33 : Min Distance is not supported
   34 : Max Distance is not supported
   35 : Texture Source is not supported
   36 : Filter Magnitude is not supported
   37 : Filter Smooth Alpha is not supported
   38 : Filter Smooth Delta is not supported
   39 : Stereo Baseline
      Description   : Distance in mm between the stereo imagers
      Current Value : 55.0319
```

따라서 아래와 같은 옵션을 조정할 수 있다는뜻..

```
[Stereo Module]
   3 : Exposure
      Description   : Depth Exposure
      Current Value : 33000
   4 : Gain
      Description   : UVC image gain
      Current Value : 16
   10 : Enable Auto Exposure
      Description   : Enable Auto Exposure
      Current Value : 1
   11 : Enable Auto White Balance
      Description   : Enable Auto White Balance
      Current Value : 0
   12 : Visual Preset
      Description   : Advanced-Mode Preset
      Current Value : 0
   13 : Laser Power
      Description   : Manual laser power in mw. applicable only when laser power mode is set to Manual
      Current Value : 150
   18 : Emitter Enabled
      Description   : Power of the DS5 projector, 0 meaning projector off, 1 meaning projector on, 2 meaning projector in auto mode
      Current Value : 0
   19 : Frames Queue Size
      Description   : Max number of frames you can hold at a given time. Increasing this number will reduce frame drops but increase latency, and vice versa
      Current Value : 16
   24 : Error Polling Enabled
      Description   : Enable / disable polling of camera internal errors
      Current Value : 1
   26 : Output Trigger Enabled
      Description   : Generate trigger from the camera to external device once per frame
      Current Value : 0
   28 : Depth Units
      Description   : Number of meters represented by a single depth unit
      Current Value : 0.0001
   39 : Stereo Baseline
      Description   : Distance in mm between the stereo imagers
      Current Value : 55.0319
```

대략적인 파라미터들 값에 대한 대략적인 설명은 [Intel-RealSense-D40-Series-Datasheet.pdf](file://./assets/Intel-RealSense-D40-Series-Datasheet.pdf) 의 67페이지 4.7 Depth Camera Functions 에 나와있다.
