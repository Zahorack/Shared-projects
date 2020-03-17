#include <Wire.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <Ticker.h>
#include <NewPing.h>

namespace I2C {
        static const uint8_t SDA = 2;
        static const uint8_t SCL = 0;
}

namespace SHT21 {
        static const uint8_t ADDR = 0x40;
        static const uint8_t TRIGGER_TEMP_HM  =  0b11100011;
        static const uint8_t TRIGGER_RH_HM    =  0b11100101;
        static const uint8_t TRIGGER_TEMP_NHM =  0b11110011;
        static const uint8_t TRIGGER_RH_NHM   =  0b11110101;
}

namespace US {
        static const uint8_t TRIGGER_PIN = 12;
        static const uint8_t ECHO_PIN   =  13;
        static const uint16_t MAX_DISTANCE = 5000;
}

static const unsigned long myChannelNumber = 783703;
static const char * myWriteAPIKey = "4FVWE2XRBN9KZQ7O";

static const char ssid[] = "OSK-11e1";   // your network SSID (name)
static const char pass[] = "Ud9nC7eP";   // your network password
//static const char ssid[] = "dqidron";   // your network SSID (name)
//static const char pass[] = "dron12345";   // your network password
WiFiClient  client;

static const uint32_t sleepTimeInSeconds = 900;         //900s = 15 minutes
Ticker ticker;

NewPing sonar(US::TRIGGER_PIN, US::ECHO_PIN, US::MAX_DISTANCE);

void setup() {
        Serial.begin(256000);
        Serial.println("Boot");
        Wire.begin(I2C::SDA, I2C::SCL);
        WiFi.mode(WIFI_STA);
        ThingSpeak.begin(client);
        //ticker.attach(0.5, tick);
        
        if (WiFi.status() != WL_CONNECTED) {
                static uint8_t cnt = 0;
                while (WiFi.status() != WL_CONNECTED) {
                        cnt++;
                        WiFi.begin(ssid, pass); 
                        Serial.print(".");
                        delay(5000);

                        if(cnt > 10) {
                                ESP.restart();
                        }
                }
                Serial.println("\nConnected.");
        }
        
}
void loop() {

        shareSonar();
        delay(20000);           //because of server maximum request rate
        shareTemperature();
        ESP.deepSleep(sleepTimeInSeconds * 1000000);

        if (WiFi.status() != WL_CONNECTED) {
                ESP.restart();
        }
}

void tick()
{
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

void shareSonar()
{
      long hlbka = sonar.ping_cm();
      hlbka = map(hlbka, 20, 100, 100,0);
      ThingSpeak.writeField(myChannelNumber, 2, hlbka, myWriteAPIKey);
}

void shareTemperature()
{
      long temperature = (long)(getTemeperature());
      ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);
}

void shareHumidity()
{
//        long humidity = (long)getHumidity();
//        ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);
}

float getTemeperature()
{
 return (float)(-52.5+(175.72*readSensor(SHT21::TRIGGER_TEMP_NHM))/65536.0);       
}

float getHumidity()
{
 return (float)(-6 + (125 * readSensor(SHT21::TRIGGER_RH_NHM))/65536.0);       
}

uint16_t readSensor(int reg)
{
        Wire.beginTransmission(SHT21::ADDR);
        Wire.write(reg);
        Wire.endTransmission(false);
        delay(100);     //sad but necessary
        Wire.requestFrom(SHT21::ADDR, 3);
        
        uint32_t timeout = millis() + 300;
        while (Wire.available() < 3) {
                if ((millis() - timeout) > 0) {
                        return 0;
                }
        }
        uint8_t H = Wire.read();
        uint8_t L = Wire.read();
        
        uint16_t result = (uint16_t)((H<<8) | L);
        result &= ~0x0003;   // clear two low bits (status bits)
        Wire.read();
        return (uint16_t)(result);
}
