/*
 * project:   MultiController     
 * 
 * author:    Zahorack      
 * date:      10.8.2018
 * board:     Arduino Nano 168
 * use:       Rover
 */
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
#include <SoftwareSerial.h>

/*GPIO interpretation*/
#define   LEFT_BUTTON      4
#define   RIGHT_BUTTON     3
#define   TOP_BUTTON       2
#define   JOYSTICK_BUTTON  5
#define   RF_ENABLE        6
#define   RF_TX            7
#define   RF_RX            8
#define   BATTERY_PIN     A0
#define   POTENCIOMETER   A1
#define   JOYSTICK_X      A6
#define   JOYSTICK_Y      A7

/* Some maths for battery */
#define   MINVOLT         3.3
#define   UrefCorection   0.932             /* 4.66/5 */
#define   Uref            5
#define   Ulow            3.3               /*for Lion baterries discharged state*/
#define   Uhigh           4.2               /*for Lion baterries fullcharged state*/
#define   lower(Ur,Ul)    (Ul* 1024/ Ur)    /*3.3 V   725*/
#define   upper(Ur,Uh)    (Uh* 1024/ Ur)    /*4.2 V  923*/

uint32_t  time_top_pressed  = 0;
uint8_t   chargelevel       = 0;

/* Communication protocol*/
//TODO: Implement multiprotocol
struct {
        uint8_t  x_value   = 0x00;
        uint8_t  y_value   = 0x00;
        uint8_t  pot_value = 0x00;
        uint8_t  button_left = 0x00;
        uint8_t  button_right = 0x00;
        uint8_t  state     = 0x00;
        uint8_t  mode      = 0x00;
        uint8_t  data_crc  = 0x00;
        uint8_t  znak      = ';';
} ctrl;

struct {
        uint16_t x;
        uint16_t y; 
}axe;

/* Rover basic funcionality modes */
enum modes : uint8_t {
        rover_mode= 0,
        sunTracker_mode,
        printing_mode,
        simulation_mode,
        
        mode_size
};
uint8_t   mode = 0;

const uint8_t crc8_Table[ ] = {
        0,  94, 188, 226,  97,  63, 221, 131, 194, 156, 126,  32, 163, 253,  31,  65,
        157, 195,  33, 127, 252, 162,  64,  30,  95,   1, 227, 189,  62,  96, 130, 220,
        35, 125, 159, 193,  66,  28, 254, 160, 225, 191,  93,   3, 128, 222,  60,  98,
        190, 224,   2,  92, 223, 129,  99,  61, 124,  34, 192, 158,  29,  67, 161, 255,
        70,  24, 250, 164,  39, 121, 155, 197, 132, 218,  56, 102, 229, 187,  89,   7,
        219, 133, 103,  57, 186, 228,   6,  88,  25,  71, 165, 251, 120,  38, 196, 154,
        101,  59, 217, 135,   4,  90, 184, 230, 167, 249,  27,  69, 198, 152, 122,  36,
        248, 166,  68,  26, 153, 199,  37, 123,  58, 100, 134, 216,  91,   5, 231, 185,
        140, 210,  48, 110, 237, 179,  81,  15,  78,  16, 242, 172,  47, 113, 147, 205,
        17,  79, 173, 243, 112,  46, 204, 146, 211, 141, 111,  49, 178, 236,  14,  80,
        175, 241,  19,  77, 206, 144, 114,  44, 109,  51, 209, 143,  12,  82, 176, 238,
        50, 108, 142, 208,  83,  13, 239, 177, 240, 174,  76,  18, 145, 207,  45, 115,
        202, 148, 118,  40, 171, 245,  23,  73,   8,  86, 180, 234, 105,  55, 213, 139,
        87,   9, 235, 181,  54, 104, 138, 212, 149, 203,  41, 119, 244, 170,  72,  22,
        233, 183,  85,  11, 136, 214,  52, 106,  43, 117, 151, 201,  74,  20, 246, 168,
        116,  42, 200, 150,  21,  75, 169, 247, 182, 232,  10,  84, 215, 137, 107,  53
} ;

/* LCD display configuration...
    - you need to check I2C address, your device has probably diferent from my
    use something like this to find correct:
    
        for(address = 1; address < 127; address++ ) {
                Wire.beginTransmission(address);
                error = Wire.endTransmission();
                if (error == 0) {
                        Serial.print("I2C device address: 0x");
                        if (address<16){
                                Serial.print("0");
                        }
                Serial.print(address,HEX);
                }
        }
*/
LiquidCrystal_I2C lcd(0x27,16,2);   //params.: I2C device address, count of columns and rows

/* New UART interface configuration for radio transciever...
        necessary when you want programing and testing at the same time 
*/
SoftwareSerial rf(RF_RX, RF_TX);

void setup() {
        rf.begin(9600);         //baud rate depends on intern modul configuration, must be same
        Serial.begin(9600);     //used for debug
        
        lcd.init();     
        lcd.begin(16,2);
        lcd.backlight();
        
        pinMode(LEFT_BUTTON, INPUT);
        pinMode(RIGHT_BUTTON, INPUT);
        pinMode(TOP_BUTTON, INPUT);
        pinMode(JOYSTICK_BUTTON, INPUT);
        pinMode(RF_ENABLE, OUTPUT);
        pinMode(BATTERY_PIN, INPUT);
        pinMode(POTENCIOMETER, INPUT);
        pinMode(JOYSTICK_X, INPUT);
        pinMode(JOYSTICK_Y, INPUT);
        
        Timer1.initialize(50000);               
        Timer1.attachInterrupt(UART_IRQ);       //periodic handler for data transfer
        mode = rover_mode;
        
        digitalWrite(RF_ENABLE, HIGH);
        Intro();
        checkBaterry();
        showBaterry();
}
/*--------------------------Main loop-------------------------------*/
void loop()
{
        read_buttons();
        read_joystick();
        read_potenciometer();
        battery_update();
        lcd_routine();
        
        if(mode == rover_mode) {
                roverLoop();
        }   
        else if (mode == printing_mode ){
                printingLoop();
        }
        else if (mode == sunTracker_mode){
                sunTrackerLoop();
        }
        else if (mode == simulation_mode){
                simulationLoop();
        }
}

/*--------------------Functions declaration--------------------------*/
void UART_IRQ()
{
        ctrl.data_crc = calc_crc8((uint8_t *)&ctrl, sizeof(ctrl) -2);
        rf.write((uint8_t *)&ctrl, sizeof(ctrl));
}

void roverLoop()
{
        uint16_t x = axe.y - axe.x + 512;
        uint16_t y = axe.y + axe.x - 512;
        x= clamp(x, 0, 1023);
        y = clamp(y, 0, 1023);
        
        ctrl.x_value = map(x, 0, 1023, 0, 200);
        ctrl.y_value = map(y, 0, 1023, 0, 200);
        
        lcd.setCursor(7, 1);
        lcd.print("RV");
}

void  sunTrackerLoop()
{
        ctrl.x_value = map(axe.x, 0, 1023, 100, 0);
        ctrl.y_value = map(axe.y, 0, 1023, 0, 100);
        lcd.setCursor(7, 1);
        lcd.print("Sun");
}

void  printingLoop()
{
        ctrl.x_value = map(axe.x, 0, 1023, 0, 200);
        ctrl.y_value = map(axe.y, 0, 1023, 0, 200);
        lcd.setCursor(7, 1);
        lcd.print("3D");
}

void  simulationLoop(){
        lcd.setCursor(7, 1);
        lcd.print("Sim");
}

void lcd_routine()
{
        if(ctrl.state){
                lcd.setCursor(6,0);
                lcd.print("START");
        }
        else{
                lcd.setCursor(6,0);
                lcd.print("STOP");
        }
}
uint8_t calc_crc8(uint8_t  * data, uint16_t len){
        uint8_t   crc = 0;
        uint16_t  n;
        
        for(n = 0; n < len; n++){
                crc = crc8_Table[ crc ^ data[n] ] ;
        }
        return crc;
}

void read_potenciometer()
{
        static uint16_t old_value;
        int16_t val = analogRead(POTENCIOMETER);
        val = map(val, 0, 1023, 0, 100);
        ctrl.pot_value = val;
        
        if((old_value != val) && old_value == 100 || old_value == 10) {
                lcd.clear();  
        }
        old_value = val;
        potenciometer_event();
}

void right_button_event()
{

}

void left_button_event()
{

}

void joystick_button_event(){
  
}

void top_button_event()
{
        ctrl.state = 0x00;
        lcd.clear();
        lcd.setCursor(6,0);
        lcd.print("STOP");
        
        checkBaterry();
        showBaterry();
}

void hold_top_button_event()
{
        ctrl.state = 0xFF;
        lcd.clear();
        lcd.setCursor(6,0);
        lcd.print("START");
}

void potenciometer_event()
{
  lcd.setCursor(11,1);
  lcd.print("P:");
  lcd.print(ctrl.pot_value);
}

void read_buttons()
{
        bool right_button_state     = digitalRead(RIGHT_BUTTON);  
        bool left_button_state     = digitalRead(LEFT_BUTTON); 
        bool top_button_state      =  digitalRead(TOP_BUTTON);
        bool joystick_button_state =  digitalRead(JOYSTICK_BUTTON);  
        
        static  bool right_button_old    = true;
        static  bool left_button_old     = true;
        static  bool top_button_old      = false;
        static  bool joystick_button_old = true;

        if(!right_button_state) {
                ctrl.button_right = 0xFF;
        }
        else {
                ctrl.button_right = 0x00;
        }
        if(!left_button_state) {
                ctrl.button_left = 0xFF;
        }
        else {
                ctrl.button_left = 0x00;
        }
        
        if ((right_button_state != right_button_old) && (!right_button_state)) {
                right_button_event(); 
        }
        if ((left_button_state != left_button_old) && (!left_button_state)) {
                left_button_event();
        }
        if ((top_button_state != top_button_old) && (top_button_state)) {
                top_button_event();
                time_top_pressed = millis(); 
        }
        if ((joystick_button_state != joystick_button_old) && (joystick_button_state) ) {
                joystick_button_event();
        }
        if( !right_button_state && !left_button_state && top_button_state&& (top_button_state != top_button_old)) {
                switchMode();
        }
        if((millis() - time_top_pressed > 250) && top_button_state != top_button_old){
                hold_top_button_event();
        }
        
        right_button_old = right_button_state;
        left_button_old = left_button_state;
        top_button_old = top_button_state;
        joystick_button_old = joystick_button_state;
}

void read_joystick()
{
        axe.x = 1023 -  analogRead(JOYSTICK_X);
        axe.y  = 1023 - analogRead(JOYSTICK_Y);
}

int clamp(int val, int min, int max)
{
        return val < min ? min : (val > max ? max : val); 
}

void switchMode()
{
        ctrl.state = 0x00;
        
        mode++;
        if(mode >= mode_size){
                mode = rover_mode;
        }
        ctrl.mode = mode;
        //checkBaterry();
        //showBaterry();
}

void checkBaterry()
{
        int16_t voltage= analogRead(BATTERY_PIN);
        voltage = voltage - lower(Uref,Ulow);
        chargelevel = map(voltage, 0, upper(Uref,Uhigh)-lower(Uref,Ulow), 0, 100);
}

void showBaterry()
{
        lcd.setCursor(0,1);
        lcd.print("B:");
        lcd.print(chargelevel);
        lcd.print("%  ");
}     
void battery_update()
{
        static uint32_t  battery_cnt = 0;
        
        battery_cnt++;
        if(battery_cnt > 1000)
        {
                checkBaterry();
                showBaterry();
                battery_cnt=0;
        }
}
void Intro()
{
        lcd.setCursor(2,0);
        lcd.print("MultiController ");
        delay(1000);
        lcd.clear();
}

/* NOTES:
 *  
 *  I recommended to use Arduino Nano 328p, because now we have memory warning due to large CRC table
 */
