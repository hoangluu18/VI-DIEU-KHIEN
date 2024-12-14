#include <Servo.h>
#include "DHT.h" // Sử dụng thư viên DHT
#define DHT11Pin 4 // Chọn chân kết nối với DHT11 là chân số 4
#define DHTType DHT11 // Chọn loại cảm biến DHT11

DHT HT(DHT11Pin, DHTType);

Servo servo_9;


float tmprVal; // Biến để lưu giá trị độ ẩm
float tempC; // Biến để lưu giá trị nhiệt độ theo độ C


int pos;
void setup() {
  servo_9.attach(9, 500, 2400);
  Serial.begin(9600);
  HT.begin();
}

void loop() {

  tmprVal= HT.readHumidity(); 
  tempC = HT.readTemperature(); 

//  Serial.print(" do am :");
//  Serial.print(tmprVal, 1);
//  Serial.print("%, ");
  Serial.print("nhiet do :");
  Serial.print(tempC, 1);
  Serial.print("°C ~ ");

  
  if( tempC > 33){
    Serial.println("nhiet do > 29 do quay 90 do");
    pos = 90;
      servo_9.write(pos);
      delay(500);
      pos = 0;
      servo_9.write(pos);
      delay(500);
  }
  else{
    Serial.println("nhiet do <= 29 do quay 45 do");
    pos = 45;
      servo_9.write(pos);
      delay(500);
      pos = 0;
      servo_9.write(pos);
      delay(500);
  }
  delay(500);
}
