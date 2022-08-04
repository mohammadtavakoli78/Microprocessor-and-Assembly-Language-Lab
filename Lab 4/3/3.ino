#include <Keypad.h>
#include <Servo.h>

Servo servo;
int index = 0;
char receivedAngle[3];

void setup(){  
  servo.attach(13, 1000, 2000);
  Serial.begin(9600);
}
  
void loop(){
  if (Serial.available() > 0) {
    char inputChar = Serial.read();
    if (inputChar == '='){
      int angle = atoi(receivedAngle);
      servo.write(angle);                 
      delay(2000);                          
      index = 0;
    }
    else {
      receivedAngle[index] = inputChar;
      index++;
    }
  }
}
