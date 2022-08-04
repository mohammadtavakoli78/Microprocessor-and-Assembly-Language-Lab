#include "pitches.h"
#include "TheImperialMarch.h"

int tempo = 120;
int buzzer = 10;
float scale = 0;
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

void setup() {
  pinMode(20, OUTPUT);
}

void loop() {
  if(digitalRead(20) == HIGH) {
     for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      if(digitalRead(20) == LOW) {
        noTone(10);
      } else { 
        divider = melody[thisNote + 1];
        if (divider > 0) {
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; 
        }
        scale = analogRead(A3)/512.0;
        tone(buzzer, (int)(melody[thisNote]*scale), noteDuration*0.9);
        delay(noteDuration);  
      }  
     }
  } else{
      noTone(10);
  }
}
