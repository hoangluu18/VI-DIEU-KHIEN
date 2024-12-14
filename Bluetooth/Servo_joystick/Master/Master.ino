//sửa lại nhưng chưa test


#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);

// Pin definitions
int VRX_pin = A0; // Joystick X axis
int VRY_pin = A1; // Joystick Y axis
int SW_pin = 5;   // Joystick button

int VRX_value, VRY_value;



void setup() {

  pinMode(VRX_pin, INPUT);
  pinMode(VRY_pin, INPUT);
  pinMode(SW_pin, INPUT_PULLUP);

  BTSerial.begin(38400);
  Serial.begin(38400);
}

void loop() {

  VRX_value = analogRead(VRX_pin);  // Đọc giá trị trục X
  VRY_value = analogRead(VRY_pin);  // Đọc giá trị trục Y
  int buttonState = digitalRead(SW_pin);  // Đọc trạng thái nút nhấn joystick

  // Hiển thị giá trị cảm biến lên Serial Monitor
  Serial.print("VRX: ");
  Serial.print(VRX_value);  // In giá trị trục X
  Serial.print(" | VRY: ");
  Serial.print(VRY_value);  // In giá trị trục Y
  Serial.print(" | Button State: ");
  Serial.println(buttonState == LOW ? "Pressed" : "Not Pressed");  // In trạng thái nút
  
  // Check button press first
  if (buttonState == LOW) {
    BTSerial.write('4');
    Serial.println("BUTTON: Sending  5");
  }

  // Then check joystick directions
  else {
    // Xác định hướng dựa vào giá trị analog
    if (VRY_value < 400) {         // UP
      BTSerial.write('0');
          Serial.println("UP: Sending  1");
    }
    else if (VRY_value > 600) {    // DOWN
      BTSerial.write('1');
          Serial.println("DOWN: Sending  3");
    }
    else if (VRX_value > 600) {    // RIGHT
      BTSerial.write('2');
          Serial.println("RIGHT: Sending  2");
    }
    else if (VRX_value < 400) {    // LEFT
      BTSerial.write('3');
          Serial.println("LEFT: Sending  4");
    }
  }

  delay(2000);  // Reduced delay for better responsiveness
}