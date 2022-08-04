#include<Keypad.h>
#include <LiquidCrystal.h> 
#include <Servo.h>

#define RS_PIN 5
#define EN_PIN 4
#define D4_PIN 3
#define D5_PIN 2
#define D6_PIN 1
#define D7_PIN 0
LiquidCrystal lcd(RS_PIN, EN_PIN,D4_PIN, D5_PIN,D6_PIN, D7_PIN );

const int ROW_NUM = 4;
const int COLUMN_NUM = 3;
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte pin_rows[ROW_NUM] = {48, 49, 50, 51};
byte pin_column[COLUMN_NUM] = {43, 42, 41};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

Servo servo;

String password = "1378";
String inputPassword;
bool isOpen = false;
int closeTime = 10;
unsigned long currentTime;

void setup() {
  lcd.begin(16, 2);

  //set pins for RED-LED and BLUE-lED
  pinMode(16,OUTPUT);
  pinMode(20,OUTPUT);

  digitalWrite(20, HIGH);
  
  // set pin for SOUNDER
  pinMode(13,OUTPUT);

  servo.attach(25);

  lcd.setCursor(0,5);
  lcd.print("Closed!");
}

void loop() {
  settimer();
  
  char key = keypad.getKey();
  if(key) {
    if(key == '#' and !isOpen) {
      if(inputPassword == password) {
        lcd.clear();
        lcd.print("correct!");
        lcd.setCursor(0,5);
        lcd.print("Open!");
        servo.write(180);
        digitalWrite(16, HIGH);
        digitalWrite(20, LOW);
        tone(13, 1000, 100);
        isOpen = true;
        inputPassword = "";
        currentTime = millis();
      } else {
        lcd.clear();
        lcd.print("wrong!");
        lcd.setCursor(0,5);
        lcd.print("Closed!");
        inputPassword = "";
      }
    }
    else if(key == '#' and isOpen) {
        servo.write(0);
        digitalWrite(16, LOW);
        digitalWrite(20, HIGH);
        tone(13, 1000, 100);
        lcd.clear();
        lcd.setCursor(0,5);
        lcd.print("Closed!");
        isOpen = false;
        inputPassword = "";
    }
    else if(key == '*' and !isOpen) {
        if(inputPassword.length() == 4) {
          password = inputPassword;
          inputPassword = "";
          lcd.print("password changed!");
          lcd.setCursor(0,5);
          lcd.print("Closed!");
        } else if(inputPassword.length() < 4) {
          closeTime = inputPassword.toInt();
          inputPassword = "";
          lcd.print("closeTime changed!");
          lcd.setCursor(0,5);
          lcd.print("Closed!");
        }
    }
    else {
      inputPassword += key;
      lcd.clear();
      lcd.print(inputPassword);
      lcd.setCursor(0,5);
      lcd.print("Closed!");
    }
  }
}

void settimer() {
  if(isOpen) {
    if( millis() - currentTime > closeTime*1000) {
      servo.write(0);
      digitalWrite(16, LOW);
      digitalWrite(20, HIGH);
      tone(13, 1000, 100);
      lcd.clear();
      lcd.setCursor(0,5);
      lcd.print("Closed!");
      isOpen = false;
      inputPassword = "";  
    } else {
        lcd.setCursor(14,0);
        int reminder = closeTime - ( (millis() - currentTime) / 1000 );
        char reminderString[3];
        sprintf(reminderString,"%02d",reminder);
        lcd.print(reminderString);
    }
  }
}
