#include <LiquidCrystal.h> 
#define RS_PIN 13
#define EN_PIN 12
#define D4_PIN 11
#define D5_PIN 10
#define D6_PIN 9
#define D7_PIN 8
LiquidCrystal lcd(RS_PIN, EN_PIN,D4_PIN, D5_PIN,D6_PIN, D7_PIN );

#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'#','0','=','+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int flagChar = 0;
double finalAnswer;
int op1;
int op2;
String operand1 = "";
String operand2 = "";
char action;

void setup() {
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  char key = keypad.waitForKey();
  switch(key){
    case '#':
      flagChar = 0;
      operand1 = "";
      operand2 = "";
      action = "";
      lcd.clear();
      break;
    case '*':
      action = '*';
      lcd.print(action);
      op1 = operand1.toInt();
      flagChar = 1;
      break;
    case '+':
      action = '+';
      lcd.print(action);
      op1 = operand1.toInt();
      flagChar = 1;
      break;
    case '-':
      action = '-';
      lcd.print(action);
      op1 = operand1.toInt();
      flagChar = 1;
      break;
    case '/':
      action = '/';
      lcd.print(action);
      op1 = operand1.toInt();
      flagChar = 1;
      break;
    case '=':
      op2 = operand2.toInt();
      finalAnswer = Action(op1,op2,action);
      lcd.clear();
      flagChar = 0;
      lcd.print(operand1);
      lcd.print(action);
      lcd.print(operand2);
      lcd.setCursor(0,1);
      lcd.print("=");
      lcd.print(finalAnswer);
      operand1 = "";
      operand2 = "";
      action = "";
      break;
    default:
      if(flagChar == 0){
        lcd.clear();
        operand1 += key;
        lcd.print(operand1);
        }
      else{
        lcd.clear();
        operand2 += key;
        lcd.print(operand1);
        lcd.print(action);
        lcd.print(operand2);
        }
      break;
    }
}

double Action(int op1, int op2, char action){
  switch(action){
    case '*':
      return op1 * op2;
    case '+':
      return op1 + op2;
    case '-':
      return op1 - op2;
    case '/':
      return op1 / op2;
  }
}
