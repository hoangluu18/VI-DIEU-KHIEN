#include <IRremote.hpp>  // Thư viện IRremote

const int LDR_PIN = A0;         // Chân kết nối với cảm biến ánh sáng (LDR)
const int IR_SEND_PIN = 3;      // Chân gửi tín hiệu IR
const int LIGHT_THRESHOLD = 700; // Ngưỡng ánh sáng để gửi tín hiệu IR đặc biệt

void setup() {
    Serial.begin(9600);          // Khởi tạo giao tiếp Serial
    IrSender.begin(IR_SEND_PIN); // Khởi tạo module IR tại chân 3
    Serial.println("LDR + IR System Started");
}

void loop() {
   int lightValue = analogRead(LDR_PIN); // Đọc giá trị ánh sáng từ cảm biến LDR

   Serial.print("LDR Value: ");
   Serial.println(lightValue);

   // Chọn mã tín hiệu IR dựa trên giá trị ánh sáng
   unsigned long signalCode;
   if (lightValue > LIGHT_THRESHOLD) {
       signalCode = 1; // Gửi tín hiệu IR khi ánh sáng lớn hơn ngưỡng
       Serial.println("High light detected! Sending IR signal 1...");
   } else {
       signalCode = 2; // Gửi tín hiệu IR khi ánh sáng nhỏ hơn ngưỡng
       Serial.println("Low light detected. Sending IR signal 2...");
   }

   // Gửi tín hiệu IR
   IrSender.sendRC5(signalCode, 8); // Gửi mã tín hiệu IR với 8 bit
   Serial.print("Sent IR Signal: ");
   Serial.println(signalCode, HEX);

   delay(500); // Tạm dừng nửa giây trước khi lặp lại
}
