/*
 * project:   HMR0.2 + GoldFish0.1  [Acoustic bait]
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

#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <TimerOne.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
         
static const uint8_t baterryPin = 0;  /*analog A0*/
static const uint8_t trigPin = 3;
static const uint8_t echoPin = 2;
static const uint8_t RF_RX = 15;
static const uint8_t RF_TX = 16;

static const uint16_t DeepMeasVolume = 50;

static const uint8_t Uref  = 5;
static const uint8_t Ulow  = 3.3;        /*for Lion baterries discharged state*/
static const uint8_t Uhigh = 4.2;        /*for Lion baterries fullcharged state*/
static const uint16_t lower = Ulow*1024/Uref;
static const uint16_t upper = Uhigh*1024/Uref;

/*-------------------KeyBoard------------------------*/
static const byte ROWS = 4; //four rows
static const byte COLS = 4; //three columns

static char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};
static byte rowPins[ROWS] = {8,7,6,5}; 
static byte colPins[COLS] = {9,10,11,12}; 
static char key;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


/*------------------Modes--------------------------*/
typedef enum {
        mode_sonar = 1,
        mode_controler
        } modes;
             
static uint8_t mode = 0;

static volatile String rx_string;
static uint16_t frequency;
static bool readyToSend = false;

NewPing sonar(trigPin, echoPin, 10000);
LiquidCrystal_I2C lcd(0x3F,16,2);
SoftwareSerial rf(RF_RX, RF_TX);

void setup()
{
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
        pinMode(baterryPin, INPUT);
        
        rf.begin(9600);
        Serial.begin(9600);
        lcd.init();     
        lcd.begin(16,2);
        lcd.backlight();
        //keypad.addEventListener(keypadEvent); //add an event listener for this keypad
        
        mode = mode_controler;
        sendInfo();
        intro();
        showInfo();
}

void keypadEvent(KeypadEvent key){
        //if((key = keypad.getKey())== 'A') switch_mode();
}

void loop()
{        
        if(rf.available()){ 
                rx_string = rf.readStringUntil(';');
                SerialManager();   
        }
        
        if((key = keypad.getKey())== 'A') {
                switch_mode();   
        }
        
        if(mode == mode_sonar) {
                sonarMode();   
        }
        else if(mode == mode_controler) {
                controlerMode();    
        }
}

void SerialManager()
{
        if(rx_string == "e")           confirmedStop();
        else if(rx_string == "a")      confirmedStart();
        else if (rx_string == "c")     confirmed_Controler_mode();
        else if (rx_string == "p")     confirmed_PC_mode();
        else if (rx_string == "g")     confirmedNumber();
        
        else showInfo();
}

void sonarMode()
{
        static float sum =0;
        static uint32_t sum_cnt = 0;
        static uint32_t baterry_cnt = 0;
        float deep = sonar.ping()/1024;
          
        if(deep !=0){
                sum = sum + deep;
                sum_cnt++;
        }
        
        if(sum_cnt >= DeepMeasVolume){
                showDeep(sum /DeepMeasVolume);
                sum_cnt=0;
                sum = 0;
        }
               
        /*-----Baterry measurment----------*/
        if(baterry_cnt>1000){
                checkBaterry();
                baterry_cnt=0;
        }
        baterry_cnt++;
}

void controlerMode()
{ 
        switch(key)
        {        
                case NO_KEY : ;break;
                case 'A': ;break;
                case 'B': sendStart();break;
                case 'C': sendStop();break;
                case 'D': sendInfo();break;
                case '*': sendFrequency();break;
                case '#': sendMode();break;
                
                default: getFrequency();break;
        }
}
/*---------------------Controler Functions--------------------*/
void controlerIntro()
{
        lcd.setCursor(0,1);
        lcd.print("Controller mode ");
        delay(1000);
        lcd.clear();
        readyToSend = false;
}
void sendStart()
{
        rf.print("s;");
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("Start Goldfish.");
}
void sendStop()
{
         rf.print("stop;");      //zmensi na byte
         lcd.clear();
         lcd.setCursor(0,0);  
         lcd.print("Stop Goldfish.");
}
void sendInfo()
{
        rf.print("info;");
}

void getFrequency()
{
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("To send:");
        
        frequency= (key- 48)*1000;
        lcd.setCursor(0,1);
        lcd.print("f= ");  
        lcd.print(key);
        
        key = keypad.waitForKey();
        frequency= frequency+(key- 48)*100;
        lcd.print(key);
        
        key = keypad.waitForKey();
        frequency= frequency+(key- 48)*10;
        lcd.print(key);
        
        key = keypad.waitForKey();
        frequency= frequency+(key- 48)*1;
        lcd.print(key);
        lcd.print(" [Hz]"); 
        
        readyToSend = true;
  }

void sendFrequency()
{
        if(readyToSend){
                lcd.clear();
                lcd.setCursor(0,0);  
                lcd.print("Sent..");
                
                rf.print(frequency);
                rf.print(";");
        }
}

void  sendMode()
{
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("Switch mode");
        
        rf.print('#');
        rf.print(';');
}

void confirmedStop()
{
        lcd.setCursor(0,1);  
        lcd.print("confirmed!");
}

void confirmedStart()
{
        lcd.setCursor(0,1);  
        lcd.print("confirmed!");
}

void confirmed_PC_mode()
{
        lcd.setCursor(0,1);  
        lcd.print("PC Mode");
}

void confirmed_Controler_mode()
{
        lcd.setCursor(0,1);  
        lcd.print("Controler Mode");
}

void confirmedNumber()
{
        lcd.setCursor(0,1);  
        lcd.print("confirmed!");
}


void showInfo()
{
        char rx_buff[20];
        char baterry_buff[5];
        char frequency_buff[5];
        char temperature_buff[5];
        int temperature_2;
        int charglevel_2;
        int frequency_2;
        
        rx_string.toCharArray(rx_buff,20);
        memcpy(baterry_buff, &rx_buff[0], 4);
        memcpy(frequency_buff, &rx_buff[4], 4);
        memcpy(temperature_buff, &rx_buff[8], 4);
        
        charglevel_2= atoi(baterry_buff);
        frequency_2 = atoi(frequency_buff);
        temperature_2 = atoi(temperature_buff);
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("Info:");
        
        lcd.setCursor(10,0);
        lcd.print("B:");
        lcd.print(charglevel_2);
        lcd.print("%  ");
        
        lcd.setCursor(0,1);
        lcd.print("f:");
        lcd.print(frequency_2);
        lcd.print("[Hz]");
        
        lcd.setCursor(10,1);
        lcd.print("T:");
        lcd.print(temperature_2);
        lcd.print(" C");
}

/*-----------------------Sonar Functions----------------------*/
void sonarIntro()
{
        lcd.setCursor(0,3);
        lcd.print("Sonar mode ");
        delay(1000);
        lcd.clear();
}

void showDeep(float d)
{
        lcd.home();
        lcd.print("H: ");
        lcd.print(d,1);
        lcd.print("m  ");
}
void intro()
{
        lcd.setCursor(2,0);
        lcd.print("GoldFish0.1");
        delay(1000);
        lcd.clear();
}

/*-----------------------Baterry Functions----------------------*/
void checkBaterry()
{       
        uint16_t voltage = analogRead(baterryPin) ;
        uint16_t charglevel = map((voltage - lower), 0, upper-lower, 0, 100);
        
        showBaterry(charglevel);
}

void showBaterry(uint16_t level)
{
        lcd.setCursor(11,0);
        lcd.print("B:");
        lcd.print(level);
        lcd.print("%  ");
}

/*-----------------------Other Functions----------------------*/        
void switch_mode(void)
{
        mode++;
        lcd.clear();
        
        if (mode > mode_controler) {
                mode = mode_sonar;
        }
        if(mode == mode_controler) {
                controlerIntro();
                sendInfo();
                showInfo();
        }
        else if(mode == mode_sonar) {
                sonarIntro();
                checkBaterry();
        }
}
