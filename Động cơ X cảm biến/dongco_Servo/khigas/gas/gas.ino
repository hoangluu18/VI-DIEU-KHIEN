
// Khii gas
#include <Servo.h>

const int cambien = A0;

Servo servo;
int pos, val;

void setup() {
  servo.attach(9, 500, 2400);
  pinMode(cambien, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(cambien);
  Serial.println(val);

  if(val > 700){
    Serial.println("co khi gas quay 90 do ");
    int angle = 90;
    servo.write(angle);
    delay(500);
    servo.write(0);
    delay(500);
  }
   else{
    Serial.println("khong co khi gas quay 45 do");
     int angle = 45;
     servo.write(angle);
     delay(500);
     servo.write(0);
     delay(500);
   }
  delay(500);
}