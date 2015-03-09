#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h> 
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

/*
   Connections
   ===========
   >BMP085
   SCL to analog 5
   SDA to analog 4
   VDD to 3.3V DC [IMPORTANT, 3.3V, NOT 5V!]
   GROUND to common ground
   
   >DHT11
   LEFT PIN to 5V
   RIGHT PIN to GND
   DATA PIN (PIN ASIDE 5V) to analog 1   
*/

#define DHTPIN A1
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

uint32_t delayMS;

void setup() { 
  //Sensor DHT11
  dht.begin();
  
  //Sensor BMP085
  if(!bmp.begin())
  {
     Serial.print("BMP085 initialization error");
     while(1);
  }
  
  lcd.begin(16, 2);
}

void loop() {
  int dht11_temperature;
  int dht11_humidity;
  
  float bmp085_temperature;
  float bmp085_pressure;
  float bmp085_altitude;
  
  sensors_event_t event;  
  
  dht.temperature().getEvent(&event);
  dht11_temperature = event.temperature;
  
  dht.humidity().getEvent(&event);
  dht11_humidity = event.relative_humidity;
  
  bmp.getEvent(&event);
  bmp085_pressure = event.pressure;
  bmp.getTemperature(&bmp085_temperature);
  bmp085_altitude = bmp.pressureToAltitude(SENSORS_PRESSURE_SEALEVELHPA, event.pressure);
  
  lcd.print(bmp085_pressure);
  lcd.print("hPa ");
  lcd.print(bmp085_temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print(bmp085_altitude);
  lcd.print("m   ");
  lcd.print(dht11_humidity);
  lcd.print("%");
  
  delay(5000);
  
  lcd.clear();
}
