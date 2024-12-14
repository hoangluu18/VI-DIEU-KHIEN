#include <SoftwareSerial.h>
#include <Stepper.h>

// Cấu hình Bluetooth
SoftwareSerial BTSerial(10, 11);
char currentCommand = '\0'; // Lệnh hiện tại
char lastCommand = '\0';    // Lệnh trước đó

// Định nghĩa số bước cho một vòng quay (28BYJ-48: 2048 bước/vòng)
#define STEPS_PER_REV 2048

// Tạo đối tượng Stepper
Stepper myStepper(STEPS_PER_REV, 2, 4, 3, 5); // Chân IN1, IN3, IN2, IN4

void setup() {
  // Khởi tạo Serial
  Serial.begin(38400);
  BTSerial.begin(38400);

  // Thiết lập tốc độ động cơ (RPM)
  myStepper.setSpeed(10); // 10 vòng/phút

  Serial.println("Stepper motor ready");
}

void loop() {
  // Kiểm tra lệnh từ Bluetooth
  if (BTSerial.available()) {
    currentCommand = BTSerial.read(); // Đọc lệnh
    Serial.print("Received command: ");
    Serial.println(currentCommand);

    // Cập nhật lệnh nếu khác lệnh trước đó
    if (currentCommand != lastCommand) {
      lastCommand = currentCommand;
      Serial.print("Executing new command: ");
      Serial.println(currentCommand);
    }

    // Xóa dữ liệu trong buffer của Bluetooth
    while (BTSerial.available()) {
      BTSerial.read();
    }
  }

  // Thực hiện xoay động cơ theo lệnh hiện tại
  if (lastCommand != '\0') {
    executeCommand(lastCommand);
  }
}

// Hàm thực hiện lệnh
void executeCommand(char cmd) {
  switch (cmd) {
    case '0': // Quay 45 độ theo chiều kim đồng hồ
      myStepper.step(STEPS_PER_REV / 8); // 1/8 vòng (45 độ)
      break;
    case '1': // Quay 90 độ ngược chiều kim đồng hồ
      myStepper.step(-STEPS_PER_REV / 4); // -1/4 vòng (90 độ)
      break;

    default:
      Serial.println("Invalid command");
      break;
  }

  // Thêm quãng nghỉ sau khi quay
  delay(500); // Dừng 500ms
}
