#include <IRremote.hpp>

// Pin definitions
int VRX_pin = A0; // Joystick X axis
int VRY_pin = A1; // Joystick Y axis
int SW_pin = 5;   // Joystick button
const int IR_SEND_PIN = 3;

// Direction codes
const int UP = 1;    
const int RIGHT = 2;  
const int DOWN = 3;   
const int LEFT = 4;   
const int BUTTON = 5; 

int VRX_value, VRY_value;
int direction = -1;

void setup() {
  pinMode(VRX_pin, INPUT);
  pinMode(VRY_pin, INPUT);
  pinMode(SW_pin, INPUT_PULLUP);
  
  IrSender.begin(IR_SEND_PIN);
  Serial.begin(9600);
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
    sendIR(BUTTON);
    Serial.println("BUTTON: Sending IR signal 5");
  }
  // Then check joystick directions
  else {
    // Xác định hướng dựa vào giá trị analog
    if (VRY_value < 400) {         // UP
      sendIR(UP);
      Serial.println("UP: Sending IR signal 1");
    }
    else if (VRY_value > 600) {    // DOWN
      sendIR(DOWN);
      Serial.println("DOWN: Sending IR signal 3");
    }
    else if (VRX_value > 600) {    // RIGHT
      sendIR(RIGHT);
      Serial.println("RIGHT: Sending IR signal 2");
    }
    else if (VRX_value < 400) {    // LEFT
      sendIR(LEFT);
      Serial.println("LEFT: Sending IR signal 4");
    }
  }

  delay(500);  // Reduced delay for better responsiveness
}

void sendIR(int signalCode) {
  IrSender.sendRC5(signalCode, 8);  // Gửi mã IR với định dạng RC5
  Serial.print("Sent IR Signal: ");
  Serial.println(signalCode, HEX);  // In mã tín hiệu IR đã gửi
}
