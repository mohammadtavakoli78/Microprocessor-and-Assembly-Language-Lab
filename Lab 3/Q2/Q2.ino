#include <LiquidCrystal.h>

#define RS_PIN 13
#define EN_PIN 12
#define D4_PIN 11
#define D5_PIN 10
#define D6_PIN 9
#define D7_PIN 8


LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] {26, 27, 28, 29};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String inputPassword = "";
String correctPassword = "1378";

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() {  
  char key = keypad.waitForKey();
  
  switch (key) {
    case 'C':
      inputPassword = "";
      lcd.clear();
      break;
    case '*':
      if (inputPassword == correctPassword){
        lcd.clear();
        lcd.print("Correct Password!");
      }
      else{
        lcd.clear();
        lcd.print("Wrong Password!");
      }
      break;
    default:
      inputPassword += key;
      lcd.clear();
      lcd.print(inputPassword);
      break;
  }
}
