#include <Stepper.h>

// Số bước cần thiết để quay một vòng (360 độ) của động cơ bước
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 12, 10, 11, 9); //IN1, IN3, IN2, IN4

//DA TEST
// Khai báo các chân kết nối cảm biến siêu âm, đèn LED và loa còi
const int trigPin = 3;
const int echoPin = 6;
// Biến để lưu thời gian phản hồi và khoảng cách
long duration;
float distance;

int val;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myStepper.setSpeed(15);
}

void loop() {
  // Gửi xung siêu âm
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Đọc thời gian phản hồi để tính toán khoảng cách
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2.0;

  // In ra giá trị khoảng cách trên Serial Monitor
  Serial.print("khoang cach = ");
  Serial.print(distance);
  Serial.print("cm\n");
  
  if (distance < 10){
            myStepper.step(0.25 * stepsPerRevolution); //45/360 = 0.25
      delay(200);
  }else{
            myStepper.step(-0.25 * stepsPerRevolution); //45/360 = 0.25
      delay(200);
  }
      delay(500);
}

