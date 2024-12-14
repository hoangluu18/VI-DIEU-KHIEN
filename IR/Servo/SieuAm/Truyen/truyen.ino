#include <IRremote.hpp>  // Thư viện IRremote

const int TRIGGER_PIN = 8;   // Chân Trigger của cảm biến siêu âm
const int ECHO_PIN = 9;      // Chân Echo của cảm biến siêu âm
const int IR_SEND_PIN = 3;   // Chân gửi tín hiệu IR
const int DISTANCE_THRESHOLD = 10; // Ngưỡng khoảng cách (cm) để gửi tín hiệu IR



void setup() {
  Serial.begin(9600);         // Khởi tạo giao tiếp Serial
  IrSender.begin(IR_SEND_PIN); // Khởi tạo module IR tại chân IR_SEND_PIN
  pinMode(TRIGGER_PIN, OUTPUT); // Chân Trigger là output
  pinMode(ECHO_PIN, INPUT);    // Chân Echo là input
  Serial.println("Ultrasonic Sensor + IR System Started");
}

void loop() {
  // Gọi hàm để đọc khoảng cách từ cảm biến siêu âm
  long distance = readUltrasonicDistance();
  
  // In khoảng cách ra Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Chọn mã tín hiệu IR dựa trên khoảng cách
  unsigned long signalCode;
  if (distance < DISTANCE_THRESHOLD) {
    signalCode = 2;  // Gửi tín hiệu cảnh báo khi khoảng cách nhỏ hơn ngưỡng
    Serial.println("Object detected! Sending warning IR signal...");
  } else {
    signalCode = 1;  // Gửi tín hiệu khi không có vật thể gần
    Serial.println("No object detected. Sending low-level IR signal...");
  }

  // Gửi tín hiệu IR
  IrSender.sendRC5(signalCode, 8);  // Gửi mã tín hiệu IR với 8 bit
  Serial.print("Sent IR Signal: ");
  Serial.println(signalCode, HEX);

  delay(500);  // Tạm dừng 500ms trước khi tiếp tục vòng lặp
}

// Hàm đọc khoảng cách từ cảm biến siêu âm
long readUltrasonicDistance() {
  digitalWrite(TRIGGER_PIN, LOW);  // Đảm bảo Trigger là LOW trước khi phát tín hiệu
  delayMicroseconds(2);            // Đợi một chút để đảm bảo ổn định

  digitalWrite(TRIGGER_PIN, HIGH); // Kích hoạt cảm biến (phát sóng)
  delayMicroseconds(10);           // Phát sóng trong 10 micro giây
  digitalWrite(TRIGGER_PIN, LOW);  // Tắt Trigger

  // Đo thời gian nhận sóng phản xạ từ vật thể (Echo)
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Tính toán khoảng cách theo công thức: distance = (time * speed_of_sound) / 2
  // Với tốc độ âm thanh ~ 343m/s, tương đương 0.0343 cm/us
  long distance = duration * 0.0343 / 2;

  return distance;
}
