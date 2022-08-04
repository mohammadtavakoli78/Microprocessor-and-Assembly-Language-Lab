#include <Servo.h>

Servo servo; 
int val;

void setup() {
  servo.attach(13, 1000, 2000);
}

void loop() {
  val = analogRead(A0);
  val = map(val, 0, 1023, 0, 180);
  servo.write(val);
  delay(1000);
}
