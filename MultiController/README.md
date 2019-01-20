# Multi Controller
Programmable wireless controller for various applications

## Introduction
This device was constructed for Rover project, but can be modified to another else use.

<p align="center">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/MultiController/Photodocumentation/IMG_3594.JPG" width="350" title="hover text">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/MultiController/Photodocumentation/IMG_3591.JPG" width="350" alt="accessibility text">
</p>

### Motivation
* My usage: https://www.youtube.com/watch?v=fpdpvifSy0U

## Realization
 
* [Case box](https://www.aliexpress.com/item/1-Set-Aluminum-PCB-Instrument-Box-Enclosure-100-71-25mm-Electronic-Project-Case-DIY/32696386857.html?spm=a2g0s.9042311.0.0.27424c4dWN6cfZ) - Aluminium or plastic
* [Arduino nano](https://www.aliexpress.com/af/arduino-nano.html?SearchText=arduino+nano&d=y&initiative_id=SB_20190117150713&origin=n&catId=0&isViewCP=y&jump=afs) - Atmega 328p
* [Radio transciever](https://www.aliexpress.com/af/433-wireless-serial-port.html?SearchText=433+wireless+serial+port&d=y&initiative_id=SB_20190117152947&origin=n&catId=0&isViewCP=y&jump=afs) - UART interface
* [Analog joystick](https://www.aliexpress.com/af/analog-joystick-dual-axis.html?SearchText=analog+joystick+dual+axis&d=y&initiative_id=SB_20190117150926&origin=n&catId=0&isViewCP=y&jump=afs) - Dual axis
* [LCD display](https://www.aliexpress.com/af/arduino-lcd-i2c.html?SearchText=arduino+lcd+i2c&d=y&initiative_id=SB_20190117151049&origin=n&catId=0&isViewCP=y&jump=afs) -I2C interface ideally
* [Battery charging modul](https://www.aliexpress.com/af/18650-Lithium-Battery-Charging-Board.html?SearchText=18650+Lithium+Battery+Charging+Board&d=y&initiative_id=SB_20190117151240&origin=n&catId=0&isViewCP=y&jump=afs) - Lithium Ion
* [Lithium battery](https://www.aliexpress.com/item/Liitokalanew-original-NCR18650B-3-7V-3400mAh-18650-rechargeable-lithium-battery-for-Panasonic-battery-DIY-nickel-piece/1000004447086.html?spm=a2g0s.9042311.0.0.27424c4ddBSn0b) -1s
* [DC/DC converter](https://www.aliexpress.com/af/dc-converter-step-up.html?SearchText=dc+converter+step+up&d=y&initiative_id=SB_20190117151801&origin=n&catId=0&isViewCP=y&jump=afs) - Step up
* [Capacitor](https://www.aliexpress.com/af/capacitor-16V.html?SearchText=capacitor+16V&d=y&initiative_id=SB_20190117152249&origin=n&catId=0&isViewCP=y&jump=afs) - cca 1500uF (10V/16V)
* Switches, buttons, potentiometer, wires ..

<p align="center">
<img src="https://github.com/Zahorack/Shared-projects/blob/master/MultiController/Photodocumentation/MultiController_bb.jpg" width="600" title="hover text">

</p>


## Software
### Peripheral reading
Very easy with arduino. All we need is analog and digital input meassurement.
#### Analog input
Intern 10-bit ADC converter, cooperated well with arduino libraries, but for your best sometimes look into declaration.
Shorted definition of analogRead() function.
```
int analogRead(uint8_t pin)
{
     uint8_t low, high;
     if (pin >= 14) pin -= 14; // allow for channel or pin numbers
     // without a delay, we seem to read from the wrong channel
     //delay(1);
     // start the conversion
     sbi(ADCSRA, ADSC);
     // ADSC is cleared when the conversion finishes
     while (bit_is_set(ADCSRA, ADSC));

     // we have to read ADCL first; doing so locks both ADCL
     // and ADCH until ADCH is read.  reading ADCL second would
     // cause the results of each conversion to be discarded,
     // as ADCL and ADCH would be locked when it completed.
     low  = ADCL;
     high = ADCH;

     // combine the two bytes
     return (high << 8) | low;
}
```
You can see this is the simplest one way of ADC conversion, without Interrupts or DMA. But for now it is enough.

#### Digital input

```
int digitalRead(uint8_t pin)
{
        uint8_t timer = digitalPinToTimer(pin);
        uint8_t bit = digitalPinToBitMask(pin);
        uint8_t port = digitalPinToPort(pin);

        if (port == NOT_A_PIN) return LOW;

        // If the pin that support PWM output, we need to turn it off
        // before getting a digital reading.
        if (timer != NOT_ON_TIMER) turnOffPWM(timer);

        if (*portInputRegister(port) & bit) return HIGH;
        return LOW;
}
```
Again basic peripheral reading. In this step i have to recomended to use external interrupts for buttons reading. You can do this with predefined function attachInterrupt(). But please note for arduino nano are available for external interrupts only pins 2 and 3.
```
attachInterrupt(pin, ISR, mode);

     pin: 2 or 3
     ISR: Interrupt Service Routine, function that will be triggered when interrupted.
     mode:
          LOW to trigger the interrupt whenever the pin is low,
          CHANGE to trigger the interrupt whenever the pin changes value
          RISING to trigger when the pin goes from low to high,
          FALLING for when the pin goes from high to low.
```
Be carefull with interrupts and buttons, there are some risk moments. One button pushing can provide multiple events, for this you have to add capacitor, like i used in my scheme. When button is not pushed down, circuit is open and connected to input, nice antenna effect. There is one solution with internal/external PULL UP / PULL DOWN resistors.

### Communication protocol
When comes to data sending you need to specify order, start or end of your data frame, and idealy some data check value.
Of course there is deal with second side of communication.
I like implementation of strucuture protocol like:
```
typedef struct {
      uint8_t START;
      uint8_t data_check;
      uint8_t data_type;
      
      uint16_t data_len;
      uint8_t *data;
      uint8_t  END;
} Protocol_t;
```
### Data transmitting
Now is control packet ready to send. I am sending it periodacally using timer and UART.
```
Protocol_t packet;
SoftwareSerial rf(RF_RX, RF_TX);

void init {
        rf.begin(9600);
        Timer1.initialize(50000);               
        Timer1.attachInterrupt(UART_IRQ);       //periodic handler for data transfer
}

void UART_IRQ() {
        packet.data_check = calc_crc8((uint8_t *)&packet, sizeof(packet));
        rf.write((uint8_t *)&packet, sizeof(packet));
}
```
