#include <IRremote.hpp>  // Thư viện IRremote

const int GAS_SENSOR_PIN = A0;  // Chân kết nối với cảm biến khí gas (ví dụ MQ-2) 
const int IR_SEND_PIN = 3;      // Chân gửi tín hiệu IR
const int GAS_THRESHOLD = 700;  // Ngưỡng nồng độ khí gas để gửi tín hiệu IR



void setup() {
    Serial.begin(9600);          // Khởi tạo giao tiếp Serial
    IrSender.begin(IR_SEND_PIN); // Khởi tạo module IR tại chân IR_SEND_PIN
    Serial.println("Gas Sensor + IR System Started");
}

void loop() {
    int gasValue = analogRead(GAS_SENSOR_PIN);  // Đọc giá trị từ cảm biến khí gas (0 - 1023)

    Serial.print("Gas Sensor Value: ");
    Serial.println(gasValue);  // In giá trị cảm biến ra Serial Monitor

    // Chọn mã tín hiệu IR dựa trên mức độ khí gas
    unsigned long signalCode;
    if (gasValue > GAS_THRESHOLD) {
        signalCode = 2;  // Gửi tín hiệu cảnh báo nồng độ khí gas cao
        Serial.println("High gas concentration detected! Sending warning IR signal...");
    } else {
        signalCode = 1;  // Gửi tín hiệu nồng độ khí gas thấp
        Serial.println("Low gas concentration. Sending low-level IR signal...");
    }

    // Gửi tín hiệu IR
    IrSender.sendRC5(signalCode, 8);  // Gửi mã tín hiệu IR với 8 bit
    Serial.print("Sent IR Signal: ");
    Serial.println(signalCode, HEX);

    delay(500);  // Tạm dừng 500ms trước khi tiếp tục vòng lặp
}
