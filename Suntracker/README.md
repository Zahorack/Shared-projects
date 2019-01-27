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
* [STM32 Library](https://github.com/Zahorack/Shared-projects/tree/master/Suntracker/src) - Includes necessary for compilation.

Source files are writen in C++, with STD (Standart peripheral library) support.

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
* [Download from here](https://github.com/Zahorack/Shared-projects/tree/master/Suntracker/3Dmodel) stl, stp or CatiaPart and print it on 3D printer.
<p align="center">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/Suntracker/Photodocumentation/Model2.PNG" width="600"
</p>

## Software

Main idea and necessary functionalities are evident from class declaration.

```
class Suntracker {
	Periph::Adc m_adcs[5] = {
			Periph::Adc(Periph::AdcPins::AdcPin1), Periph::Adc(Periph::AdcPins::AdcPin2),
			Periph::Adc(Periph::AdcPins::AdcPin3), Periph::Adc(Periph::AdcPins::AdcPin4),
			Periph::Adc(Periph::AdcPins::AdcPin5),
	};
	Periph::Servo 	m_servo1, m_servo2;
	Util::Timer m_timer;

	void measure();
public:
	Suntracker();

	void update();

};
```

This device is contrlled with more seriosly microcontroller [STM32](https://en.wikipedia.org/wiki/STM32) series F4, seated on NUCLEO development board.
<p align="center">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/Suntracker/Photodocumentation/NUCLEO-F446ZE.jpg" width="500"
</p>

On this platform we are developing  Space prtnting rover [firmware](https://github.com/xgallom/stm32-f446ze)
