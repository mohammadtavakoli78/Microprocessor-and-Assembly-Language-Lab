#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'.','0','=','+'}
};

byte rowPins[ROWS] = {37, 38, 39, 40};
byte colPins[COLS] = {41, 42, 43, 44};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int val;
Servo servo;
String entered = "";

void setup(){
  servo.attach(13, 1000, 2000);
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.waitForKey();  
    if (key == '='){
      val = entered.toInt();
      servo.write(val-90);
      delay(2000);
    }else if (key == '.') {
      entered = "";
    }else {
      entered += key;
    }
}
