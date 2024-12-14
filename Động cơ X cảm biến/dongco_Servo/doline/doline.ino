#include <Servo.h>
// Định nghĩa chân cảm biến line (digital input)
#define LINE 2

Servo servo;
int val;

void setup() {
  // Gắn servo vào chân 9 và thiết lập phạm vi góc từ 500 đến 2500 microseconds
  servo.attach(9, 500, 2400);
  
  // Khởi động giao tiếp Serial để theo dõi trạng thái
  Serial.begin(9600);
  
  // Đảm bảo rằng chân LINE được thiết lập là INPUT
  pinMode(LINE, INPUT);
}

void loop() {

  val = digitalRead(LINE);
  

  Serial.print("Gia tri cam bien LINE: ");
  Serial.println(val);

  
  if(val == HIGH){
    Serial.println("Phat hien line: Di chuyen servo den 90 do");
    int angle = 90;  // Di chuyển servo đến góc 90 độ
    servo.write(angle);
    delay(500);  
    servo.write(0); 
    delay(500);  
  }
  else{
   
    Serial.println("Khong phat hien line: Di chuyen servo den 45 do");
    int angle = 45;  
    servo.write(angle);
    delay(500);  
    servo.write(0); 
    delay(500);  
  }

  
  delay(500);
}
