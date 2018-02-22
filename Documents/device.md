### 리얼센스 장치구성 (D415)
![text](./assets/cam2.png)

D415는 2개의 **"센서"** (**RGB_CAMERA**, **STEREO_MODULE**) 로 구성되고, 총 4개의 하드웨어 부품을 가지고 있다. (rgb camera, ir camera(left), ir camera(right), ir projector)  

각 센서별로 아래와 같은 **Stream** 을 얻는것이 가능하다.  
* Sensor::RGB_CAMERA = { Color0 }  
* Sensor::STEREO_MODULE = { Infrared0, Infrared1, Infrared2, Depth0 }    

여기서 Infrared1 은 왼쪽 IR카메라 스트림 , Infrared2는 오른쪽 IR카메라 스트림 이다. Infrared0은 해상도가 1280x720 인것으로 보아 IR1&2 를 합친 스트림으로 보인다.


장치의 센서에 접근하는 방법은 다음과 같다. ~~(realsense 기초 사용법을 먼저 보고오자)~~

```  
/* 장치의 센서별 접근 */
rs2::context ctx;
rs2::device_list list = ctx.query_devices();
rs2::device dev = list[0];
vector<rs2::sensor> = device.query_sensors();
rs2::sensor stereo_sensor = sensor[0];
rs2::sensor color_sensor = sensor[1];
```
각 센서객체를 얻어왔다면 다음과 같이 **stream_profile** 을 주어, 스트림활성화를 시킬 수 있다.
```
/* 센서별 스트림 활성화 및 데이터 get */
auto sensor = streo_sensor;
sensor.open(stream_profile)
sensor.start([&](rs2::frame f) {frame_queue.enqueue(f)}
rs2::frame frame = frame_queue.wait_for_frame();
auto data = frame.get_data(); //frame data get
```
stream_profile 은 `rs2::stream_profile` 클래스 이며, 각 스트림마다 이용가능한 stream_profile이 사전에 정해져있다. (Definition 링크는 [hot_link.md](./hotlink.md) 를 참조)  
이를 벗어난 스트림 프로파일을 사용하려고 하면 예외가 발생한다. 각 스트림마다 이용가능한 stream_profile 은 [stream_profile.md](./stream_profile) 에 정리해 두었으니 참고바란다.
