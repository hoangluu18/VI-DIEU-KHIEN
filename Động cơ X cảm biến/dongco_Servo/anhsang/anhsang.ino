#include <Servo.h>
// analogRead
int LIGHT = 0;
Servo servo;
int val;

void setup() {
  servo.attach(9, 500, 2400);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(LIGHT);
  
  // In giá trị cảm biến ánh sáng ra Serial
  Serial.print("Gia tri cam bien anh sang: ");
  Serial.println(val);
  
  if(val < 700){
    Serial.println("Anh sang manh, xoay servo 90 do");
    int angle = 90;
    servo.write(angle);
    delay(500);
    servo.write(0);
    delay(500);
  }
  else{
    Serial.println("Anh sang yeu, xoay servo 45 do");
    int angle = 45;
    servo.write(angle);
    delay(500);
    servo.write(0);
    delay(500);
  }
  delay(500);
}
