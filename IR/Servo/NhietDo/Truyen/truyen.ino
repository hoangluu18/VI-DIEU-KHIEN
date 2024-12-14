#include <DHT.h>
#include <IRremote.hpp>  // Thư viện IRremote

const int DHT_PIN = 9;         // Chân kết nối cảm biến DHT11
const int DHT_TYPE = DHT11;    // Loại cảm biến DHT
const int IR_SEND_PIN = 3;     // Chân gửi tín hiệu IR
const float TEMP_THRESHOLD = 30.0; // Ngưỡng nhiệt độ để gửi tín hiệu IR đặc biệt

DHT dht(DHT_PIN, DHT_TYPE);    // Khởi tạo đối tượng DHT

void setup() {
    Serial.begin(9600);          // Khởi tạo giao tiếp Serial
    dht.begin();                 // Khởi tạo cảm biến DHT
    IrSender.begin(IR_SEND_PIN); // Khởi tạo module IR tại chân 9
    Serial.println("DHT + IR System Started");
}

void loop() {
   float t = dht.readTemperature(); // Đọc giá trị nhiệt độ

   if ( isnan(t)) {
       Serial.println("Failed to read from DHT sensor");
       return; // Nếu cảm biến không đọc được, thoát hàm
   }

   Serial.print(t);
   Serial.println(" °C");

    // Chọn mã tín hiệu IR dựa trên nhiệt độ
    unsigned long signalCode;
   if (t > TEMP_THRESHOLD) {
       signalCode = 2; // Gửi tín hiệu cảnh báo nhiệt độ cao
       Serial.println("High temperature detected! Sending warning IR signal...");
   } else {
       signalCode = 1; // Gửi tín hiệu nhiệt độ thấp
       Serial.println("Low temperature. Sending low-level IR signal...");
   }


    // Gửi tín hiệu IR
    IrSender.sendRC5(signalCode, 8); // Gửi mã tín hiệu IR với 8 bit
    Serial.print("Sent IR Signal: ");
    Serial.println(signalCode, HEX);

    delay(500); // Tạm dừng 2 giây trước khi lặp lại
}