#include <SoftwareSerial.h>

SoftwareSerial BTSerial(53, 51); // RX | TX

char c = ' ';

void setup()
{
 Serial.begin(9600);
 Serial.println("Receiving from 05");
 BTSerial.begin(9600);  // HC-05 default speed in AT command more
}

void loop()
{
 // Keep reading from HC-05 and send to Arduino Serial Monitor
 if (BTSerial.available())
 {
   c = BTSerial.read();
   Serial.write(c);
 }
//
 // Keep reading from Arduino Serial Monitor and send to HC-05
 if (Serial.available())
   BTSerial.write(Serial.read());
}
