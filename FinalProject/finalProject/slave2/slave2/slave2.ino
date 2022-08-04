#include <Wire.h>

const int SOUNDER_PORT = 5;
const int LED_PORT = 10;
int number = -1;
bool flag = false;

void setup() {

  pinMode(LED_PORT, OUTPUT);

  pinMode(SOUNDER_PORT, OUTPUT);
  analogReference(INTERNAL1V1);

  Wire.begin(2);
  Wire.onReceive(temp);
}

void loop() {  
  if(flag) {
    tone(SOUNDER_PORT, 1000, 100);
    digitalWrite(LED_PORT, HIGH);
  } else {
        noTone(SOUNDER_PORT);
        digitalWrite(LED_PORT, LOW);
   }
}

void temp(int n) {
  number = Wire.read();
  if(number == 1) {
    flag = true; 
  } else if(number == 0) {
    flag = false;
  }
}
