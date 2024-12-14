#include <IRremote.hpp>
#include <Stepper.h>

const int IR_RECEIVE_PIN = 2; // Chân kết nối với bộ thu IR

// Số bước cần thiết để quay một vòng (360 độ) của động cơ bước
const int stepsPerRevolution = 2048;



Stepper myStepper(stepsPerRevolution, 12, 10, 11, 9); //IN1, IN3, IN2, IN4

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  myStepper.setSpeed(15);  // Đặt tốc độ quay của động cơ (15 vòng/phút)
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
      Serial.println("Xoay cùng chiều kim đồng hồ 90 độ");
      myStepper.step(0.25 * stepsPerRevolution); //90/360 = 0.25
      delay(200);
  } else if (IrReceiver.decodedIRData.decodedRawData == 0x102) {
      Serial.println("Xoay ngược chiều kim đồng hồ 90 độ");
      myStepper.step(-0.25 * stepsPerRevolution);
      delay(200);  
  }
}



