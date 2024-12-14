#include <Servo.h>

// Khai báo chân kết nối
const int trigPin = 3;
const int echoPin = 5;
const int servoPin = 9;

// Khai báo biến
Servo myServo;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Chân trigPin là OUTPUT
  pinMode(echoPin, INPUT); // Chân echoPin là INPUT
  myServo.attach(servoPin); // Gắn servo với chân servoPin
  Serial.begin(9600); // Khởi tạo Serial Monitor
}

void loop() {
  // Đo khoảng cách
  distance = calculateDistance();

  // In khoảng cách ra Serial Monitor
  Serial.print("Khoảng cách: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Điều khiển servo dựa trên khoảng cách
  if (distance < 10) {
    myServo.write(90); // Quay 90 độ nếu khoảng cách nhỏ hơn 7cm
    delay(500);
    myServo.write(0);
    delay(500);
  } else {
    myServo.write(45); // Quay 45 độ nếu khoảng cách lớn hơn hoặc bằng 7cm
    delay(500);
    myServo.write(0);
    delay(500);
  }


}

// Hàm tính khoảng cách
int calculateDistance(){ 
  // Phát xung siêu âm
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Tính toán khoảng cách dựa trên thời gian phản hồi
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}