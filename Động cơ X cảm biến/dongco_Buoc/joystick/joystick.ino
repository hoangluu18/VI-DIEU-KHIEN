#include <Stepper.h>

// Số bước cần thiết để quay một vòng (360 độ) của động cơ bước
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 12, 10, 11, 9); //IN1, IN3, IN2, IN4

// Pin definitions
int VRX_pin = A0; // Joystick X axis
int VRY_pin = A1; // Joystick Y axis
int SW_pin = 5;   // Joystick button


int VRX_value, VRY_value;


void setup() {
  pinMode(VRX_pin, INPUT);
  pinMode(VRY_pin, INPUT);
  pinMode(SW_pin, INPUT_PULLUP);
  myStepper.setSpeed(15);
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
    Serial.println("BUTTON");
      myStepper.step(0.125 * stepsPerRevolution); //45/360 = 0.25
      delay(200);
  }
  // Then check joystick directions
  else {
    // Xác định hướng dựa vào giá trị analog
    if (VRY_value < 400) {         // UP
       Serial.println("UP");
      myStepper.step(0.25 * stepsPerRevolution); //90/360 = 0.25
      delay(200);
     
    }
    else if (VRY_value > 600) {    // DOWN
      Serial.println("DOWN");
      myStepper.step(-0.25 * stepsPerRevolution); //90/360 = 0.25
      delay(200);
    }
    else if (VRX_value > 600) {    // RIGHT
      Serial.println("RIGHT");
       myStepper.step(0.5 * stepsPerRevolution); //180/360 = 0.25
      delay(500200);
    }
    else if (VRX_value < 400) {    // LEFT
      Serial.println("LEFT");
      myStepper.step(-0.5 * stepsPerRevolution); //180/360 = 0.25
      delay(200);
    }

    delay(500);
  }


}

