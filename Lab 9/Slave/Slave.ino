#include <SPI.h>

#define input 51

int n;

byte index = 0;

byte data[5];

boolean finish = false;


void setup(){
  Serial3.begin (9600);
  
  pinMode(input, INPUT_PULLUP);
  
  SPCR |= _BV(SPE);
  
  SPCR |= _BV(SPIE);
  
  SPI.attachInterrupt();
}


void loop(){
  if (finish){
    
    finish = false;
    
    n = data[0] + (data[1] << 8);
    
    Serial3.println(n);
    
    index = 0;
    
  }
}

ISR(SPI_STC_vect){
  
  byte b = SPDR;
  
  if(index <= 1){
    
    data[index++] = b;
    
    if (index == 2)
    
      finish = true;
      
  }
  
}
