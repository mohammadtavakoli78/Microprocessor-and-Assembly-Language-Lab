#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h> 

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
byte pin_rows[ROW_NUM] = {50, 51, 52, 53};
byte pin_column[COLUMN_NUM] = {49, 48, 47};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

Servo servo;

const int SERVO_PORT = 25;
const int SOUNDER_PORT = 20;
const int TEMPERATURE_PORT = A0;  

String inputPassword;
String timer;
String temperature;
int temp = 0;
unsigned long currentTime;
bool isReady = false;
bool finish = false;
 
void setup() {
  
  lcd.begin(16, 2);
  
  pinMode(SOUNDER_PORT, OUTPUT);
  analogReference(INTERNAL1V1);

  servo.attach(SERVO_PORT);
  servo.write(180);
}

void loop() {
  settimer();
  char key = keypad.getKey();
  if(key) {
    if(key == '#') {
      timer = inputPassword; 
      inputPassword = "";
    }
    else if(key == '*') {
      temperature = inputPassword;
      inputPassword = "";
    }
    else {
      inputPassword += key;
      lcd.clear();
      lcd.print(temp);
      lcd.setCursor(0,5);
      lcd.print(inputPassword);
    }
  }
    
  long lmVal = analogRead(A0);
  temp = lmVal/10+2; 

  if(temp == temperature.toInt() && !isReady) {
    isReady = true;
    currentTime = millis();
    tone(SOUNDER_PORT, 1000, 100);
    delay(200);
  }
  
  delay(200);
  lcd.clear();
  lcd.print(temp); 
}

void settimer() {
  if(!finish) {
    if(isReady) {
      if( millis() - currentTime > timer.toInt() * 1000) {
        servo.write(0);
        lcd.clear(); 
        tone(SOUNDER_PORT, 1000, 100);
        delay(200);
        finish = true; 
        isReady = false;  
      } else {
          lcd.setCursor(14,0);
          int reminder = timer.toInt() - ( (millis() - currentTime) / 1000 );
          char reminderString[3];
          sprintf(reminderString,"%02d",reminder);
          lcd.print(reminderString);
      }
    }
  }
}
