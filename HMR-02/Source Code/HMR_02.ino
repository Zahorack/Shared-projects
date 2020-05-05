#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <TimerOne.h>

#define   baterryPin          0           /*analog A0*/
#define   trigPin             3
#define   echoPin             2

#define   maxdeep             10000
#define   MINVOLT             3.3
#define   UrefCorection       0.932       /* 4.66/5 */
#define   Uref                5

#define   Ulow                3.3         /*for Lion baterries discharged state*/
#define   Uhigh               4.2         /*for Lion baterries fullcharged state*/

#define   lower(Ur,Ul)        (Ul* 1024/ Ur)   /*3.3 V   725*/
#define   upper(Ur,Uh)        (Uh* 1024/ Ur)   /*4.2 V  923*/
float deep;
float voltage;
int charglevel;
int cnt;
int baterry_cnt;
int main_cnt;

NewPing sonar(trigPin, echoPin, maxdeep);
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(baterryPin, INPUT);


    Serial.begin(115200);
    lcd.init();
    lcd.begin(16,2);
    lcd.backlight();

    intro();
    noInterrupts();           // disable all interrupts

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    OCR1A = 255;                      //max 65535
    TCCR1B |= (1 << WGM12);                 // turn on CTC mode for timer1
    TCCR1B |= (1 << CS12) | (1 << CS10);    // Set bits for 1024 prescaler
    TIMSK1 |= (1 << OCIE1A);                // enable timer compare interrupt
    interrupts();                // enable all interrupts

    checkBaterry();
    showBaterry();


}

ISR(TIMER1_COMPA_vect)          
{ 
    baterry_cnt++;

}

void loop() {
 
    if(baterry_cnt>1000){
        checkBaterry();
        showBaterry();
        baterry_cnt=0;
    }

    if(main_cnt >= 100){
        showBottom();
        cnt=0;
        main_cnt=0;
    }
    main_cnt++;

    deep = sonar.ping();
    deep= deep/1024;


    if(deep !=0){
        showDeep();
        cnt++;
    }
}

void showDeep(){
    lcd.home();
    lcd.print("H: ");
    lcd.print(deep,1);
    lcd.print("m  ");
}


void intro() {
    lcd.setCursor(4,0);
    lcd.print("HMR_02");
    delay(1000);
    lcd.clear();
}


void showBottom(){
    lcd.setCursor(0,1);
    lcd.print("D: ");
    //lcd.setCursor(10,1);
    lcd.print(cnt);
    lcd.print("%   ");
}


void showBaterry(){
    lcd.setCursor(11,0);
    //lcd.backlight();
    lcd.print("B:");
    lcd.print(charglevel);
    lcd.print("%  ");
}

void checkBaterry(){
    voltage= analogRead(baterryPin);
    voltage = voltage - lower(Uref,Ulow);
    charglevel = map(voltage, 0, upper(Uref,Uhigh)-lower(Uref,Ulow), 0, 100);
}

float kalman_filter(int z_measured) {
    static float x_est_last = 0;
    static float P_last = 0;
    float K;
    float P;
    float P_temp;
    float x_temp_est;
    float x_est;
    float Q = 0.25;
    float R = 0.7;

    // predpoklad
    x_temp_est = x_est_last;
    P_temp = P_last + Q;

    // vypocet Kalmanovho zosilnenia
    K = P_temp * (1.0/(P_temp + R));

    // korekcia
    x_est = x_temp_est + K * ((int)z_measured - x_temp_est);
    P = (1- K) * P_temp;

    // aktualizacia poslednych vzoriek
    P_last = P;
    x_est_last = x_est;

    return (int)x_est;
}
