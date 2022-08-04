void setup() {
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  if (digitalRead(12)==HIGH){
      digitalWrite(6,HIGH);
      delay(200);
      digitalWrite(5,HIGH);
      delay(200);
      digitalWrite(4,HIGH);
      delay(200);
      digitalWrite(3,HIGH);
  }
  if (digitalRead(11)==HIGH) {
      digitalWrite(3,HIGH);
      delay(200);
      digitalWrite(4,HIGH);
      delay(200);
      digitalWrite(5,HIGH);
      delay(200);
      digitalWrite(6,HIGH);
  }
  if (digitalRead(10)==HIGH){
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
  }
}
