* 장치 시작  

```
using namespace std;

rs2::context ctx;
rs2::device_list list = ctx.query_devices();
rs2::device dev = list[0];
string serialNumber = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER)




rs2::config cfg;
cfg.enable_device(serialNumber);
cfg.enable_stream(RS2_STREAM_DEPTH, RS2_FORMAT_Z16);

rs2::pipeline pipe;
rs2::pipeline profile = pipe.start(cfg);
rs2::frameset frames = pipe.wait_for_frames();
rs2::frame frame = frames.get_depth_frame();
frame.get_data(); //Pointer to depth pixels


rs2::stream_profile ir1_stream = profile.get_stream(RS2_STREAM_INFRARED,1);
rs2::stream_profile ir2_stream = profile.get_stream(RS2_STREAM_INFRARED,2);

rs2_extrinsics e = ir1_stream.get_extrinsic_to(ir2_stream);  

```
> ```
typedef struct rs2_extrinsics
{
    float rotation[9];    /**< Column-major 3x3 rotation matrix */
    float translation[3]; /**< Three-element translation vector, in meters */
} rs2_extrinsics;
```

* [rs_camera_info](https://github.com/IntelRealSense/librealsense/blob/ba01147d65db16fdf4da36a3e718fe81c8421034/include/librealsense2/h/rs_sensor.h#L22)
