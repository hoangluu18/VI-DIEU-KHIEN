
// Pin definitions
int VRX_pin = A0; // Joystick X axis
int VRY_pin = A1; // Joystick Y axis
int SW_pin = 5;   // Joystick button

// Pin định nghĩa
#define IN1 6 // Chân IN1 của mô-đun H-Bridge
#define IN2 7 // Chân IN2 của mô-đun H-Bridge
#define ENA 9 // Chân ENA (PWM) để điều chỉnh tốc độ động cơ

int motorSpeed = 255; // Tốc độ động cơ, có thể thay đổi từ 0 đến 255 (PWM)

int VRX_value, VRY_value;

// Hàm quay động cơ theo chiều kim đồng hồ
void clockwise()
{
    digitalWrite(IN1, HIGH);      // IN1 = HIGH
    digitalWrite(IN2, LOW);       // IN2 = LOW
    analogWrite(ENA, motorSpeed); // Điều khiển tốc độ động cơ
}

// Hàm quay động cơ ngược chiều kim đồng hồ
void counterClockwise()
{
    digitalWrite(IN1, LOW);       // IN1 = LOW
    digitalWrite(IN2, HIGH);      // IN2 = HIGH
    analogWrite(ENA, motorSpeed); // Điều khiển tốc độ động cơ
}

// Hàm dừng động cơ
void stopMotor()
{
    digitalWrite(IN1, LOW); // Cắt điều khiển chiều quay
    digitalWrite(IN2, LOW); // Cắt điều khiển chiều quay
    analogWrite(ENA, 0);    // Đặt tốc độ về 0, dừng động cơ
}

// Hàm thay đổi tốc độ động cơ
void setMotorSpeed(int speed)
{
    motorSpeed = constrain(speed, 0, 255); // Đảm bảo giá trị tốc độ trong phạm vi 0-255
    analogWrite(ENA, motorSpeed);          // Thay đổi tốc độ động cơ
}

void setup()
{
    pinMode(VRX_pin, INPUT);
    pinMode(VRY_pin, INPUT);
    pinMode(SW_pin, INPUT_PULLUP);

    // Cấu hình các chân điều khiển động cơ
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    VRX_value = analogRead(VRX_pin);       // Đọc giá trị trục X
    VRY_value = analogRead(VRY_pin);       // Đọc giá trị trục Y
    int buttonState = digitalRead(SW_pin); // Đọc trạng thái nút nhấn joystick

    // Hiển thị giá trị cảm biến lên Serial Monitor
    Serial.print("VRX: ");
    Serial.print(VRX_value); // In giá trị trục X
    Serial.print(" | VRY: ");
    Serial.print(VRY_value); // In giá trị trục Y
    Serial.print(" | Button State: ");
    Serial.println(buttonState == LOW ? "Pressed" : "Not Pressed"); // In trạng thái nút

    // Check button press first
    if (buttonState == LOW)
    {
        Serial.println("BUTTON");
        Serial.println("Stop Motor");
        stopMotor();
        delay(2000); // Dừng 2 giây
    }
    // Then check joystick directions
    else
    {
        // Xác định hướng dựa vào giá trị analog
        if (VRY_value < 400)
        { // UP
            Serial.println("UP");
            Serial.println("Clockwise");
            clockwise();
            delay(2000); // Quay 2 giây
        }
        else if (VRY_value > 600)
        { // DOWN
            Serial.println("DOWN");
            Serial.println("Counter-Clockwise");
            counterClockwise();
            delay(2000); // Quay 2 giây
        }
        else if (VRX_value > 600)
        { // RIGHT
            Serial.println("RIGHT");
            Serial.println("Change Speed and Run Clockwise");
            setMotorSpeed(128);  // Giảm tốc độ xuống 50%
            clockwise();
            delay(2000);  // Quay 2 giây
        }
        else if (VRX_value < 400)
        { // LEFT
            Serial.println("Change Speed and Run Counter-Clockwise");
            setMotorSpeed(255);  // Tăng tốc độ lên 100%
            counterClockwise();
            delay(2000);  // Quay 2 giây
        }

        delay(500);
    }
}
