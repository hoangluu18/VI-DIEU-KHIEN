#include "DHT.h" // Sử dụng thư viên DHT
#define DHT11Pin 4 // Chọn chân kết nối với DHT11 là chân số 4
#define DHTType DHT11 // Chọn loại cảm biến DHT11

#include <Stepper.h>

// Số bước cần thiết để quay một vòng (360 độ) của động cơ bước
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 12, 10, 11, 9); //IN1, IN3, IN2, IN4

DHT HT(DHT11Pin, DHTType);
//DA TEST
float humi; // Biến để lưu giá trị độ ẩm
float tempC; // Biến để lưu giá trị nhiệt độ theo độ C
float tempF; // Biến để lưu giá trị nhiệt độ theo độ F



void setup() {
  Serial.begin(9600);
  HT.begin(); // Khởi động cảm biến DHT
  myStepper.setSpeed(15);
}

void loop() {
  humi = HT.readHumidity(); // Đọc giá trị độ ẩm từ cảm biến
  tempC = HT.readTemperature(); // Đọc giá trị nhiệt độ theo độ C từ cảm biến
  tempF = HT.readTemperature(true); // Đọc giá trị nhiệt độ theo độ F từ cảm biến
  
  // In giá trị độ ẩm và nhiệt độ ra Serial Monitor với độ chính xác 1 chữ số thập phân
  Serial.print(" Độ ẩm:");
  Serial.print(humi, 1);
  Serial.print("%,\n");
  Serial.print("Nhiệt đô:");
  Serial.print(tempC, 1);
  Serial.print("°C ~ ");
  Serial.print(tempF, 1);
  Serial.print("°F");
  
  if (humi > 80 && tempC > 25){
       myStepper.step(0.25 * stepsPerRevolution); //45/360 = 0.25
      delay(200);
  }else{
        myStepper.step(-0.25 * stepsPerRevolution); //45/360 = 0.25
        delay(200);
  }
      delay(500);
}

