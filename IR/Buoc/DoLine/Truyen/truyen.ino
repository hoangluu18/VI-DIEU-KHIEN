#include <IRremote.hpp>  // Thư viện IRremote

const int LINE_SENSOR_PIN = 2;  // Chân kết nối cảm biến dò line
const int IR_SEND_PIN = 3;      // Chân gửi tín hiệu IR



void setup() {
    Serial.begin(9600);          // Khởi tạo giao tiếp Serial
    pinMode(LINE_SENSOR_PIN, INPUT);  // Thiết lập chân cảm biến dò line là đầu vào
    IrSender.begin(IR_SEND_PIN);    // Khởi tạo module IR tại chân IR_SEND_PIN
    Serial.println("Line Sensor + IR System Started");
}

void loop() {
    int lineSensorValue = digitalRead(LINE_SENSOR_PIN);  // Đọc giá trị từ cảm biến dò line

    // Hiển thị giá trị cảm biến dò line
    Serial.print("Line Sensor Value: ");
    Serial.println(lineSensorValue);

    // Chọn mã tín hiệu IR tùy thuộc vào giá trị cảm biến dò line
    unsigned long signalCode;
    if (lineSensorValue == HIGH) {
        signalCode = 1;  // Cảm biến dò line phát hiện vật cản (HIGH)
        Serial.println("Line detected! Sending '1' IR signal...");
    } else {
        signalCode = 0;  // Không có vật cản (LOW)
        Serial.println("No line detected. Sending '0' IR signal...");
    }

    // Gửi tín hiệu IR
    IrSender.sendRC5(signalCode, 8);  // Gửi mã tín hiệu IR với 8 bit
    Serial.print("Sent IR Signal: ");
    Serial.println(signalCode, HEX);

    delay(500);  // Tạm dừng nửa giây trước khi lặp lại
}
