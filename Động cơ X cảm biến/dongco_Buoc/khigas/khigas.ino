#include <Stepper.h>

// Số bước cần thiết để quay một vòng (360 độ) của động cơ bước
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 12, 10, 11, 9); //IN1, IN3, IN2, IN4

#define  cambien  A0

int val;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(cambien);
  Serial.print("Giá trị cảm biến: ");
  Serial.println(val);
  
  if (val > 700){
      Serial.println("Co GAS");
      myStepper.step(0.25 * stepsPerRevolution); //45/360 = 0.25
      delay(200);
    }
  else{
      Serial.println("Khong co gas");
      myStepper.step(-0.25 * stepsPerRevolution); //45/360 = 0.25
      delay(200);
    }
  delay(500);
}

