#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[ROWS] = {3, 2, 8, 7}; 
byte colPins[COLS] = {4, 5, 6}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
}

void loop(){
  char key = keypad.getKey();
  char tk = Serial.read();
  if(key != NO_KEY){
    Serial.println(key);
  }
  if (key == '1' || tk == '1'){
    digitalWrite(A0, HIGH);
  }
  else if(key == '2' || tk == '2') {
    digitalWrite(A1, HIGH);
  }
   else if(key == '3' || tk == '3') {
    digitalWrite(A2, HIGH);
  }
   else if(key == '4' || tk == '4') {
    digitalWrite(A3, HIGH);
  }
   else if(key == '5' || tk == '5') {
    digitalWrite(A4, HIGH);
  }
   else if(key == '6' || tk == '6') {
    digitalWrite(A5, HIGH);
  }
   else if(key == '7' || tk == '7') {
    digitalWrite(A6, HIGH);
  }
   else if(key == '8' || tk == '8') {
    digitalWrite(A7, HIGH);
  }
   else if(key == '9' || tk == '9') {
    digitalWrite(A8, HIGH);
  }
   else if(key == '0') {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
    digitalWrite(A5, HIGH);
    digitalWrite(A6, HIGH);
    digitalWrite(A7, HIGH);
    digitalWrite(A8, HIGH);
  }
}
