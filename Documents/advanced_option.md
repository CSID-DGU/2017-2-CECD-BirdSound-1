# Advanced Mode Parameters...
버전 2.10.0 기준의 advanced_mode preset [링크](https://github.com/IntelRealSense/librealsense/blob/v2.10.0/src/ds5/advanced_mode/presets.cpp)  
현재 사용중인 리얼센스 라이브러리의 버전은 2.9.0....  
400,420 - 63개  
405, 410, 430 - 65개  
( 2개의 차이는  
p.laser_state.laser_state = 1;  p.laser_power.laser_power = 150.f;  
차이임. )
넘버링이 가장 유사한 D410을 가지고 프리셋을 분석하면 될듯.
 * 2.9.0 advanced_mode 컴파일 문의 : https://communities.intel.com/thread/121550?q=advanced
 * advanced_mode doc : https://github.com/IntelRealSense/librealsense/blob/master/doc/rs400/rs400_advanced_mode.md

[v 2.10.0 preset](https://github.com/IntelRealSense/librealsense/blob/f11482ddc645594f12dc003044db74e1c1895b13/src/ds5/advanced_mode/presets.cpp#L146)

## Depth Control
#### 1. DS Second Peak Threshold = 325

#### 2. DS Neighbor Threshold
#### 3. DS Median Threshold
#### 4. Estimate Median Increment
#### 5. Estimate Median Decrement
#### 6. Score Minimum Threshold
#### 7. Score Maximum Threshold
#### 8. DS LR Threshold
#### 9. Texture Cunt Threshold
#### 10. Dexture Difference Threshold

## RSM
#### 1. RSM bypass
#### 2. Disparity Difference Threshold
#### 3. SLO RAU Difference Threshold
#### 4. Remove Threshold

## Rau Support Vector Control
#### 1. Min West
#### 2. Min East
#### 3. Min WE Sum
#### 4. Min North
#### 5. Min South
#### 6. Min NS sum
#### 7. U shrink
#### 8. V shrink

## Color Control
#### 1. Disable SAD color
#### 2. Disable RAU color
#### 3. Disable SLO Right color
#### 4. Disable SLO Left color
#### 5. Disable SAD Normalize

## Rau Color Thresholds Control
#### 1. Diff Threshold Red
#### 2. Diff Threshold Green
#### 3. Diff Threshold Blue

## SLO Color Thresholds Control
#### 1. Diff Threshold Red
#### 2. Diff Threshold Green
#### 3. Diff Threshold Blue

## SLO Penalty Control
#### 1. K1 Penalty
#### 2. K2 Penalty
#### 3. K1 Penalty Mod1
#### 4. K1 Penalty Mod2
#### 5. K2 Penalty Mod1
#### 6. K2 Penalty Mod2

## HDAD
#### 1. Ignore SAD
#### 2. AD Lambda
#### 3. Census Lambda

## Color Correction
#### 1. Color Correction 1~12

## Depth table
#### 1. Depth Units
#### 2. Depth Clamp Min
#### 3. Depth Clamp Max
#### 4. Disparity Mode
#### 5. Disparity Shift

## AE Control
#### 1. Mean Intensity Set Point

## Sensus Enable Reg
#### 1. u-Diameter
#### 2. v-Diameter
