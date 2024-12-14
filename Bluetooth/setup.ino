#include <SoftwareSerial.h>

SoftwareSerial BTSerial (10, 11); // RX | TX
//nghia la chan RX o bluetooth se cam vao chan 11 của arduino
//chan TX o bluetooth se cam vao chan 10 cua arduino

void setup () {
 pinMode (9, OUTPUT); 
 digitalWrite(9, HIGH);
 Serial.begin(9600);
 Serial.println ("Enter AT commands:");
 BTSerial.begin (38400); // HC-05 default speed in AT command

}
void loop () {
// Keep reading from HC-05 and send to Arduino Serial Monitor
if (BTSerial.available())
Serial.write(BTSerial.read());



// Keep reading from Arduino Serial Monitor and send to HC-05
if (Serial.available())
 BTSerial.write(Serial.read());
}

////chua cam nguon arrduino  -> cam nguon, chua cam day 5v => cam day 5v dong thoi giu 2 giay => vao che do at mode