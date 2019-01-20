# Sun tracker
This work is small part of our complex university project - Space printing rover.

## Introduction
Space printing rover use fresnel lens for concentrate solar energy in focal point. According to this funcionality we need to set lens in right inertial system corresponding with sun position at the sky.

Advantage of this concept is that is possible to aim at Sun either from width angle. But disadvantage is less precision. So to the future we are expecting using fusion with camera, with some object detection algorithm.

<p align="center">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/Suntracker/Photodocumentation/IMG_5165.JPG" width="307" title="hover text">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/Suntracker/Photodocumentation/Model1.PNG" width="500" alt="accessibility text">
</p>


### Library
* [STM32 Library](https://github.com/xgallom/stm32-f446ze) - Source files necesary for correct working

## Realization

* 5 x Photoresistor [R1, R2, R3, R4, R5]

* 5 x Resistor [R11, R12, R13, R14, R15]

* 2 x servo motor

* Suntracker prototype
<p align="center">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/Suntracker/Photodocumentation/Suntracker_schem.jpg" width="600"
</p>
  
Resistors values depend on your modification, important is set working point. For this you need to calculate simple voltage divider.

#### 3D model
* [Download from here](https://github.com/Zahorack/Shared-projects/tree/master/Suntracker/3Dmodel) stl, stp or CatiaPart and lets modify.
<p align="center">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/Suntracker/Photodocumentation/Model2.PNG" width="600"
</p>
