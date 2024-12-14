#include <IRremote.hpp>
#include <Servo.h>

const int IR_RECEIVE_PIN = 2; // Chân kết nối với bộ thu IR
const int SERVO_PIN = 9;      // Chân kết nối với servo
Servo myServo;
//tam on
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  myServo.attach(SERVO_PIN);  // Gắn servo vào chân SERVO_PIN
  myServo.write(0);           // Đặt servo về vị trí 0 độ ban đầu
}

void loop() {
  Serial.println("waiting");
  if (IrReceiver.decode()) {
    handleReceiver();
    IrReceiver.resume();
  }
  delay(1000);
}

void handleReceiver() {
  Serial.println("Receive Signal!");
  Serial.print("Mã nhận được: 0x");
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  if (IrReceiver.decodedIRData.decodedRawData == 0x101) {
    Serial.println("Servo quay 90 độ.");
    myServo.write(90); // Xoay servo 90 độ
    delay(500);
    myServo.write(0);
    delay(500);
  } else if (IrReceiver.decodedIRData.decodedRawData == 0x102) {
    Serial.println("Servo quay 120 độ.");
    myServo.write(120); // Xoay servo 120 độ
    delay(500);
    myServo.write(0);
    delay(500);
  } else if (IrReceiver.decodedIRData.decodedRawData == 0x103) {
    Serial.println("Servo quay 45 độ.");
    myServo.write(45); // Xoay servo 45 độ
    delay(500);
    myServo.write(0);
    delay(500);
  } else if (IrReceiver.decodedIRData.decodedRawData == 0x104) {
    Serial.println("Servo quay 180 độ.");
    myServo.write(180); // Xoay servo 180 độ
    delay(500);
    myServo.write(0);
    delay(500);
  } else if (IrReceiver.decodedIRData.decodedRawData == 0x105) {
    Serial.println("Servo quay 60 độ.");
    myServo.write(60); // Xoay servo 60 độ
    delay(500);
    myServo.write(0);
    delay(500);
  }
}