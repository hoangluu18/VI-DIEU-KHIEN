
#include <Servo.h>

// Khai báo chân kết nối cho các cảm biến và đèn LED
// analog
int VRX_pin = A0; // Joystick trục X
int VRY_pin = A1; // Joystick trục Y
// digital
int SW_pin = 5; // Nút nhấn trên joystick

// Các hướng có thể của joystick
const int NORTH = 0;
const int NORTH_EAST = 1;
const int EAST = 2;
const int SOUTH_EAST = 3;
const int SOUTH = 4;
const int SOUTH_WEST = 5;
const int WEST = 6;
const int NORTH_WEST = 7;
const int CENTER = 8;

// Các biến để lưu giá trị đọc từ joystick và hướng hiện tại
int VRX_value, VRY_value;
int direction = -1, direction_cache;

// Hàm chuyển đổi giá trị từ joystick sang hướng
int coor_to_direction(int VRX_value, int VRY_value);

// Các hàm kiểm tra phạm vi giá trị của joystick
bool is_large_coor(int coor);
bool is_middle_coor(int coor);
bool is_small_coor(int coor);

Servo servo;
int pos, val;

void setup() {
  servo.attach(9, 500, 2400);
    pinMode(VRX_pin, INPUT);
  pinMode(VRY_pin, INPUT);
  pinMode(SW_pin, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
    // Đọc giá trị từ joystick
  VRX_value = analogRead(VRX_pin);
  VRY_value = analogRead(VRY_pin);

  // Xác định hướng từ giá trị joystick
  direction = coor_to_direction(VRX_value, VRY_value);

  // In giá trị đọc từ trục Y của joystick ra Serial Monitor
  
  // Xoay động cơ tương ứng với hướng của joystick
  if (direction == WEST) {
    int angle = 45;
    Serial.println("WEST: xoay goc 45 do");
    servo.write(angle);
    delay(500);
    servo.write(0);
    delay(500);
  } else if (direction == NORTH) {
    Serial.println("NORTH: xoay goc 90 do");
    int angle = 90;
    servo.write(angle);
    delay(500);
    servo.write(0);
    delay(500);
  } else if (direction == EAST) {
    Serial.println("EAST: xoay goc 120 do");
    int angle = 120;
    servo.write(angle);
    delay(500);
    servo.write(0);
    delay(500);
  } else if (direction == SOUTH) {
    Serial.println("SOUTH: xoay goc 180 do");
    int angle = 180;
    servo.write(angle);
    delay(500);
    servo.write(0);
    delay(500);
  }

  // Đọc giá trị từ nút nhấn trên joystick
  int SW_value = digitalRead(SW_pin);


  if (SW_value == LOW) {
    Serial.println("Center: xoay goc 60 do");
    int angle = 60;
    servo.write(angle);
    delay(500);
    servo.write(0);
    delay(500);
  }

  delay(500);
}


// Hàm chuyển đổi giá trị từ trục X và Y của joystick sang hướng
int coor_to_direction(int VRX_value, int VRY_value) {
  if (is_large_coor(VRX_value) && is_middle_coor(VRY_value))
    return NORTH;
  if (is_large_coor(VRX_value) && is_large_coor(VRY_value))
    return NORTH_EAST;
  if (is_middle_coor(VRX_value) && is_large_coor(VRY_value))
    return EAST;
  if (is_small_coor(VRX_value) && is_large_coor(VRY_value))
    return SOUTH_EAST;
  if (is_small_coor(VRX_value) && is_middle_coor(VRY_value))
    return SOUTH;
  if (is_small_coor(VRX_value) && is_small_coor(VRY_value))
    return SOUTH_WEST;
  if (is_middle_coor(VRX_value) && is_small_coor(VRY_value))
    return WEST;
  if (is_large_coor(VRX_value) && is_small_coor(VRY_value))
    return NORTH_WEST;
  return CENTER; // Trả về hướng trung tâm nếu không phát hiện hướng nào khác
}

// Các hàm kiểm tra phạm vi giá trị của joystick
bool is_large_coor(int coor) {
  return coor > 614;
}
bool is_middle_coor(int coor) {
  return (coor <= 614) && (coor >= 400);
}
bool is_small_coor(int coor) {
  return coor < 400;
}






// //
// #include <IRremote.hpp>

// // Pin definitions
// int VRX_pin = A0; // Joystick X axis
// int VRY_pin = A1; // Joystick Y axis
// int SW_pin = 5;   // Joystick button
// const int IR_SEND_PIN = 3;

// // Direction codes
// const int UP = 1;    
// const int RIGHT = 2;  
// const int DOWN = 3;   
// const int LEFT = 4;   
// const int BUTTON = 5; 

// int VRX_value, VRY_value;
// int direction = -1;

// void setup() {
//   pinMode(VRX_pin, INPUT);
//   pinMode(VRY_pin, INPUT);
//   pinMode(SW_pin, INPUT_PULLUP);
  
//   IrSender.begin(IR_SEND_PIN);
//   Serial.begin(9600);
// }

// void loop() {
//   VRX_value = analogRead(VRX_pin);  // Đọc giá trị trục X
//   VRY_value = analogRead(VRY_pin);  // Đọc giá trị trục Y
//   int buttonState = digitalRead(SW_pin);  // Đọc trạng thái nút nhấn joystick

//   // Hiển thị giá trị cảm biến lên Serial Monitor
//   Serial.print("VRX: ");
//   Serial.print(VRX_value);  // In giá trị trục X
//   Serial.print(" | VRY: ");
//   Serial.print(VRY_value);  // In giá trị trục Y
//   Serial.print(" | Button State: ");
//   Serial.println(buttonState == LOW ? "Pressed" : "Not Pressed");  // In trạng thái nút

//   // Check button press first
//   if (buttonState == LOW) {
//     sendIR(BUTTON);
//     Serial.println("BUTTON: Sending IR signal 5");
//   }
//   // Then check joystick directions
//   else {
//     // Xác định hướng dựa vào giá trị analog
//     if (VRY_value < 400) {         // UP
//       sendIR(UP);
//       Serial.println("UP: Sending IR signal 1");
//     }
//     else if (VRY_value > 600) {    // DOWN
//       sendIR(DOWN);
//       Serial.println("DOWN: Sending IR signal 3");
//     }
//     else if (VRX_value > 600) {    // RIGHT
//       sendIR(RIGHT);
//       Serial.println("RIGHT: Sending IR signal 2");
//     }
//     else if (VRX_value < 400) {    // LEFT
//       sendIR(LEFT);
//       Serial.println("LEFT: Sending IR signal 4");
//     }
//   }

//   delay(500);  // Reduced delay for better responsiveness
// }

// void sendIR(int signalCode) {
//   IrSender.sendRC5(signalCode, 8);  // Gửi mã IR với định dạng RC5
//   Serial.print("Sent IR Signal: ");
//   Serial.println(signalCode, HEX);  // In mã tín hiệu IR đã gửi
// }






