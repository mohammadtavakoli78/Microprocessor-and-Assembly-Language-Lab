#include <Wire.h>
#include<Keypad.h>
#include <LiquidCrystal.h> 

int eepromRead(int type);
void eepromWrite(int data, int type);

#define DEVICE_ADDRESS 0b1010000
#define MODE_ADDRESS 0
#define TIME_ADDRESS 1

int read_data;
int read_data2;
int mode;
int timer = 5; 
String input;
bool isOpen = false;
unsigned long currentTime;

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

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  read_data = eepromRead(0);
  if(read_data != 1 && read_data != 2 && read_data != 3 && read_data != 4) {
    eepromWrite(1, 0);
    delay(100);
  }
  read_data = eepromRead(0);
  mode = read_data; 
  lcd.setCursor(0, 5);

  timer = eepromRead(1);
  if(timer == 0) {
    eepromWrite(5, 1);
    delay(100);
  }
  timer = eepromRead(1);
  lcd.clear();
  
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);

  set(mode);
}

void loop() {
  settimer();
  char key = keypad.getKey();

  if(key) {
    if(key == '#') {
      eepromWrite(input.toInt(), 0);
      delay(100);
      mode = eepromRead(0);
      input = "";
      set(mode);
      isOpen = true;
      currentTime = millis();
    }
    else if(key == '0') {
      eepromWrite(1, 0);
      delay(100);
      mode = eepromRead(0);
      
      eepromWrite(5, 1);
      delay(100);
      timer = eepromRead(1);
      
      input = "";
    }
    else if(key == '*') {
      eepromWrite(input.toInt(), 1);
      delay(100);
      timer = eepromRead(1);
      input = "";
    }
    else {
      input += key;
    }
  }
}

void eepromWrite(int data, int type){
  if(type == 0){
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(data);
    Wire.endTransmission();
  }else if(type == 1) {
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x00);
    Wire.write(0x0A);
    Wire.write(data);
    Wire.endTransmission();
  }
}

int eepromRead(int type){
  int data;
  if(type == 0){
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();
    
    Wire.requestFrom(DEVICE_ADDRESS, 1);
    data = Wire.read();
  }else if(type == 1) {
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x00);
    Wire.write(0x0A);
    Wire.endTransmission();
    
    Wire.requestFrom(DEVICE_ADDRESS, 1);
    data = Wire.read();
  }
  return data;
}

void set(int mode) {
  if(mode == 1) {
    digitalWrite(22, HIGH);
    digitalWrite(23, LOW);
    digitalWrite(24, LOW);
    digitalWrite(25, LOW);
    lcd.setCursor(0, 0);
    lcd.print(1);
  }
  else if(mode == 2) {
    digitalWrite(22, LOW);
    digitalWrite(23, HIGH);
    digitalWrite(24, LOW);
    digitalWrite(25, LOW);
    lcd.setCursor(0, 0);
    lcd.print(2);
  }
  else if(mode == 3) {
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(25, LOW);
    lcd.setCursor(0, 0);
    lcd.print(3);
  }
  else if(mode == 4) {
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    digitalWrite(24, LOW);
    digitalWrite(25, HIGH);
    lcd.setCursor(0, 0);
    lcd.print(4);
  }
}

void settimer() {
  if(isOpen) {
    if( millis() - currentTime > timer*1000) {
      isOpen = false;
    } else {
        lcd.setCursor(0,5);
        int reminder = timer - ( (millis() - currentTime) / 1000 );
        char reminderString[3];
        sprintf(reminderString,"%02d",reminder);
        lcd.print(reminderString);
    }
  }
}
