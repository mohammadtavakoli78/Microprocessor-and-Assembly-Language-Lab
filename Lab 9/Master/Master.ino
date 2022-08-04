#include <SPI.h>

#define Sensor A1
#define Resistor A0

int temperature;
int fotosel;

byte fotosles[2];
byte tempratures[2];


const int SS1 = 48;
const int SS2 = 49;

void setup(){
  Serial3.begin(9600);
  
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  
  analogReference(INTERNAL1V1);
  
  SPI.begin();
  
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop(){
  
    fotosel = analogRead(Resistor)/2-2;
    
    temperature = analogRead(Sensor)/10*2+6;
    
    temperature = map(temperature, 0, 308, 0, 150);
    
    Serial3.print("---- TEMPRATURE is : ");
    Serial3.println(temperature);
    Serial3.print("---- FOTOSEL is : ");
    Serial3.println(fotosel);
    
    fotosles[0] = fotosel;
    fotosles[1] = fotosel >> 8;
    
    tempratures[0] = temperature;
    tempratures[1] = temperature >> 8;
    
    digitalWrite(SS1, LOW);
    
    delay(10);
    
    for (int i = 0 ; i < 2 ; i++){
      SPI.transfer(fotosles[i]);
    }
    
    delay(10);
    
    digitalWrite(SS1, HIGH);
    
    delay(200);
    
    digitalWrite(SS2, LOW);
    
    delay(10);
    
    for (int i = 0 ; i < 2 ; i++){
      SPI.transfer(tempratures[i]);
    }
    
    delay(10);
    
    digitalWrite(SS2, HIGH);
    
    delay(200);
}
