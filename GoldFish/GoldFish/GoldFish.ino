/*
 * project:   GoldFish0.1           [Acoustic bait]
 * author:    Zahorack              [Oliver Hollý]
 * date:      28.5.2018
 * 
 * Throwback:
 *      Pretty bad program. No communication protocol!
 *      
 *      Git shared only for source code safe management. Awkward.
 *      
 * Next version: 
 *      TODO complete program remake!
 */

#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <TimerOne.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>

static const uint8_t baterryPin = 0;  /*analog A0*/
static const uint8_t SignalPin  = 6;
static const uint8_t WakeUpPin  = 3;
static const uint8_t OneWireBus  = 2;
static const uint8_t InterLed    = 13;

static const uint8_t Uref  = 5;
static const uint8_t Ulow  = 3.3;        /*for Lion baterries discharged state*/
static const uint8_t Uhigh = 4.2;        /*for Lion baterries fullcharged state*/
static const uint16_t lower = Ulow*1024/Uref;
static const uint16_t upper = Uhigh*1024/Uref;

SoftwareSerial mySerial(15, 16);
OneWire oneWire(OneWireBus);
DallasTemperature thermometer(&oneWire);

static uint16_t charglevel;
static uint16_t temperature;
static uint16_t frequency;
static String rx_string;
static bool state;

static const uint16_t sinTable[] = {
        0x7d,0x89,0x95,0xa1,0xad,0xb8,0xc2,0xcc,
        0xd5,0xde,0xe5,0xeb,0xf0,0xf5,0xf8,0xf9,
        0xfa,0xf9,0xf8,0xf5,0xf0,0xeb,0xe5,0xde,
        0xd5,0xcc,0xc2,0xb8,0xad,0xa1,0x95,0x89,
        0x7d,0x71,0x65,0x59,0x4d,0x42,0x38,0x2e,
        0x25,0x1c,0x15,0xf,0xa,0x5,0x2,0x1,
        0x0,0x1,0x2,0x5,0xa,0xf,0x15,0x1c,
        0x25,0x2e,0x38,0x42,0x4d,0x59,0x65,0x71,
};


void wakeUpNow(){// here the interrupt is handInterLed after wakeup
  ;
}    
      
typedef enum { mode_pc = 1,
               mode_controler
             } modes;
uint8_t   mode            = 0;



void setup()
{
        Serial.begin(9600);
        mySerial.begin(9600);
        mySerial.setTimeout(200);
        thermometer.begin();
        
        pinMode(WakeUpPin, INPUT);
        pinMode(SignalPin, OUTPUT);
        mode == mode_controler;
        
        noInterrupts();           // disable all interrupts
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1  = 0;
        OCR1A = 65535;                      //max 65535
        TCCR1B |= (1 << WGM12);                 // turn on CTC mode for timer1             
        // TCCR1B |= (1 << CS12) | (1 << CS10);     // Set bits for 1024 prescaler    
        // TCCR1B |= (1 << CS10);                   // Set bits for 1 prescaler     
        TCCR1B |= (1 << CS12);                     // Set bits for 256 prescaler              
        TIMSK1 |= (1 << OCIE1A);                // enable timer compare interrupt
        interrupts();
}

ISR(TIMER1_COMPA_vect){ 
        
        if(state){
                digitalWrite(SignalPin, !digitalRead(SignalPin));
        }
}

void loop()
{
        //flash (160);
        if(mySerial.available()){
                rx_string= mySerial.readStringUntil(';');
                
                if(rx_string == "#"){
                        switch_mode();
                }
                
                if(mode == mode_pc){
                        PC_SerialManager();
                }
                else{
                        Controler_SerialManager();
                }
        }

} /*End of loop */

void checkTemperature()
{
        thermometer.requestTemperatures();
        temperature = thermometer.getTempCByIndex(0);
}

/*
void SerialEvent(){
      if(mySerial.available()){
        
        rx_string= mySerial.readStringUntil(';');
        
        //mySerial.readBytesUntil(';', rx_buff, 5);
        //mySerial.readBytes(no_sense_buffer, mySerial.available());
       // rx_string= mySerial.read();

        if(rx_string == "#") switch_mode();

        if(mode == mode_pc) PC_SerialManager();
         else if(mode == mode_controler) Controler_SerialManager();
    }
}*/
/*----------------------------------Controler_mySerialManager---------------------------*/


void Controler_SerialManager()
{
        char buff[20];
        char rx_buff[10];
        int rx_value;
        
        if(rx_string == "s"){
                mySerial.print("a;");
                delay(10);
                mySerial.print("a;");
                state = true;
        }
        
        else if(rx_string == "stop"){
                delay(100);
                mySerial.print("e;");
                delay(10);
                mySerial.print("e;");
                state=false;
                delay(100);   //needed
                sleepNow();
        }
        
        else if(rx_string == "info"){
                delay(100);
                checkBaterry();
                checkTemperature();
                sprintf(buff,"%4d%4d%4d;" ,charglevel, frequency, temperature);
                mySerial.print(buff);
                delay(10);
                mySerial.print(buff);
        }
        else {
                rx_string.toCharArray(rx_buff,5);
                rx_value= atoi(rx_buff);
                delay(100);
                
                if(rx_value < 9999 && rx_value > 0){
                        mySerial.print("g;");
                        delay(10);
                        mySerial.print("g;");
                        frequency = rx_value; 
                        OCR1A = 31250/frequency; 
                        state= true; 
                }    
        }
}
/*-------------------------------------PC_mySerialManager-------------------------------*/
void PC_SerialManager()
{
        char rx_buff[10];
        int rx_value;
        
        if(rx_string == "S" || rx_string == "s" || rx_string == "start" ||
           rx_string == "Start" || rx_string == "help" || rx_string == "Help") {
        
                mySerial.println("*********************************************");
                mySerial.println("*********Goldfish0.1 by Zahorack************");
                mySerial.println("*********************************************");
                mySerial.println("");
                mySerial.println("Enter requency in Hertz finished by semicolon: ");
                mySerial.println("");
        }
        else if(rx_string == "Stop" || rx_string == "stop"|| rx_string == "sleep" ||
        rx_string == "Sleep" || rx_string == "end") {
                
                mySerial.println("***Sleep mode***");
                mySerial.println(""); 
                mySerial.println("As you wish, good luck!"); 
                mySerial.println("Bye bye");    
                /*Enter sleep mode*/
                state=false;
                delay(100);   //needed
                sleepNow();
        }
        else if(rx_string == "check" || rx_string == "Check"|| rx_string == "batt" ||
                rx_string == "baterry" || rx_string == "info" || rx_string == "battery"){
                
                mySerial.println(""); 
                mySerial.println("***Goldfish INFO:***");
                mySerial.println(""); 
                checkBaterry();
                mySerial.print("Baterry: ");
                mySerial.print(charglevel); 
                mySerial.print(" [%]"); 
                mySerial.println("");
        }
        else {
                rx_string.toCharArray(rx_buff,5);
                rx_value= atoi(rx_buff);
                
                if(rx_value < 2000 && rx_value > 0){
                        mySerial.print("Got it!  [");
                        mySerial.print(rx_value);
                        mySerial.println(" Hz]");
                        frequency = rx_value;
                        state= true;
                }
        }
}

void switch_mode(void)
{
        mode++;    
        if (mode > mode_controler) {
                mode = mode_pc;
        }
        if(mode == mode_controler){
                mySerial.print("c;");
        }
        else if(mode == mode_pc){
                mySerial.print("p;");    
        }
}
  
void simply_play(int period)
{
        digitalWrite(SignalPin, HIGH);
        delay(period/10);
        digitalWrite(SignalPin,LOW);
        delay(period/10);
}

void checkBaterry()
{
        uint16_t voltage = analogRead(baterryPin);
        charglevel = map((voltage - lower), 0, upper-lower, 0, 100);
}

void flash(int timeVal) 
{
        pinMode (InterLed, OUTPUT);
        digitalWrite (InterLed, HIGH);
        delay (timeVal);
        digitalWrite (InterLed, LOW);
        delay (timeVal);
}

void sleepNow()
{
        digitalWrite(SignalPin, LOW);
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable(); // enables the sleep bit in the mcucr register
        
        power_adc_disable();
        power_spi_disable();
        power_timer0_disable();
        power_timer1_disable();
        power_timer2_disable();
        power_twi_disable();
        
        attachInterrupt(WakeUpPin,wakeUpNow, LOW);      
        sleep_mode(); // here the device is actually put to sleep!!
        
        // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
        sleep_disable(); // first thing after waking from sleep:
        // disable sleep...
        detachInterrupt(WakeUpPin);
        
        power_all_enable();
}

void  pwm_play(int period)
{
        for(int i=0; i<64; i+=4) {  
                analogWrite(SignalPin, sinTable[i]);
                delay(period);
        }
}
  /*      i+=4                   i+=2
 * delay 1 - 1.8 khz        5 - 324 Hz
 *      2 - 1.25 kHz
 *      3 - 936 Hz
 *      4 - 765 Hz
 *      5 - 650 hz
 *      6 - 547 Hz
 *      7 - 474 Hz
 *      8 - 424 Hz
 * 
 * 
 * http://www.daycounter.com/Calculators/Sine-Generator-Calculator2.phtml
 */
  
