#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 2; // Chân kết nối với bộ thu IR
//done tuong tu voi cam bien khac
// Định nghĩa chân
const int motorPin1 = 12; // IN1
const int motorPin2 = 11; // IN2
const int enablePin = 4; // ENA (PWM)
//done
// Hàm setup
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Đặt tốc độ ban đầu cho động cơ
  analogWrite(enablePin, 0); // Tắt động cơ lúc đầu
}

// Hàm loop
void loop() {
  Serial.println("waiting");
  if (IrReceiver.decode()) {
    handleReceiver();
    IrReceiver.resume();
  }
  delay(500);
}


void handleReceiver()  {
  Serial.println("Receive Signal!");
  Serial.print("Mã nhận được: 0x");
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  if (IrReceiver.decodedIRData.decodedRawData == 0x101) {
      Serial.println("Xoay động cơ theo chiều kim đồng hồ");
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      analogWrite(enablePin, 200); // Tốc độ 200/255
  }
  else if (IrReceiver.decodedIRData.decodedRawData == 0x102) {
        Serial.println("Xoay động cơ theo ngược chiều kim đồng hồ");
        // Xoay động cơ ngược chiều kim đồng hồ
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        analogWrite(enablePin, 200); // Tốc độ 200/255
  }
  

//  // Dừng động cơ
//  analogWrite(enablePin, 0);
//  delay(2000); // Dừng 2 giây
//
//
//
//  // Dừng động cơ
//  analogWrite(enablePin, 0);
//  delay(2000); // Dừng 2 giây
}
