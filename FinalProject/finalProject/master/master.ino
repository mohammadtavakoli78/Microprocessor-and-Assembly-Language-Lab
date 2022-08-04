#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal.h> 

const int SERVO1_PORT = 22;
const int SERVO2_PORT = 23;
const int SERVO3_PORT = 24;
const int SERVO4_PORT = 25;

const int TEMPERATURE_PORT = A0; 

int veryHotTemp = 40;
int maxTemp = 35;
int minTemp = 15;
int veryLowTemp = 10;
int temp = 25;

bool up = true;

Servo servo1, servo2, servo3, servo4;
 

#define RS_PIN 5
#define EN_PIN 4
#define D4_PIN 3
#define D5_PIN 2
#define D6_PIN 1
#define D7_PIN 0
LiquidCrystal lcd(RS_PIN, EN_PIN,D4_PIN, D5_PIN,D6_PIN, D7_PIN );

void setup() {

  lcd.begin(16, 2);
  
  Wire.begin();
  
  analogReference(INTERNAL1V1);
  
  servo1.attach(SERVO1_PORT);
  servo2.attach(SERVO2_PORT);
  servo3.attach(SERVO3_PORT);
  servo4.attach(SERVO4_PORT);

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  
  Wire.begin();
  
}

void loop() {

  changeTemp();
  if(temp > veryHotTemp) {
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
    temp = 25;
    up = false;
  } else if(temp >= maxTemp && temp <= veryHotTemp) {
    Wire.beginTransmission(1);  
    Wire.write(1);
    Wire.endTransmission();   
    
    delay(300);       
    
    Wire.beginTransmission(2); 
    Wire.write(1);
    Wire.endTransmission();
  } else if(temp > minTemp && temp < maxTemp) {
  
      Wire.beginTransmission(1);  
      Wire.write(0);
      Wire.endTransmission();   
      
      delay(300);       
      
      Wire.beginTransmission(2); 
      Wire.write(0);
      Wire.endTransmission();
    } else if(temp <= minTemp && temp >= veryLowTemp) {
      delay(250);
    } else if (temp < veryLowTemp) {
        servo1.write(90);
        servo2.write(90);
        servo3.write(90);
        servo4.write(90);
        temp = 25;
        up = true;
      }
}

void changeTemp() {
    if(up) {
      ++temp;
    } else {
      --temp;
    }
    servo1.write((temp-10)*5);
    servo2.write((temp-10)*5);
    servo3.write((temp-10)*5);
    servo4.write((temp-10)*5);
    lcd.clear();
    delay(50);
    lcd.print(temp);
    delay(50);
}
