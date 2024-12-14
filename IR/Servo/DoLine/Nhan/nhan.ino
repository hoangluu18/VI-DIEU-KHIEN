#include <IRremote.hpp>
#include <Servo.h>

const int IR_RECEIVE_PIN = 2; // Chân kết nối với bộ thu IR
const int SERVO_PIN = 9;      // Chân kết nối với servo
Servo myServo;
//done
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
  delay(500);
}

void handleReceiver() {
  Serial.println("Receive Signal!");
  Serial.print("Mã nhận được: 0x");
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  if (IrReceiver.decodedIRData.decodedRawData == 0x101) {
    myServo.write(90); // Xoay servo 90 độ
    Serial.println("Servo quay 90 độ.");
    delay(200);
    myServo.write(0);
  } else if (IrReceiver.decodedIRData.decodedRawData == 0x100) {
    myServo.write(120); // Xoay servo 120 độ
    Serial.println("Servo quay 120 độ.");
    delay(200);
    myServo.write(0);
  }
}