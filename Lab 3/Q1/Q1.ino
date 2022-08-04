#include <LiquidCrystal.h>

#define RS_PIN 13
#define EN_PIN 12
#define D4_PIN 11
#define D5_PIN 10
#define D6_PIN 9
#define D7_PIN 8

LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

int x_cursor = 0;
int y_cursor = 0;

void setup() {
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(x_cursor, y_cursor);
  lcd.print("mohammad tavakoli");
  delay(2000);
}

void loop() {  
  lcd.scrollDisplayRight();
  x_cursor++;
  if (x_cursor == 5){
    x_cursor = 0;
    y_cursor++;
    lcd.clear();
    lcd.setCursor(x_cursor, y_cursor % 2);
    lcd.print("mohammad tavakoli");
  }
  delay(1000);
}
