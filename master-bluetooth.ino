#include <Metro.h> // https://github.com/thomasfredericks/Metro-Arduino-Wiring
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(53, 51); // RX | TX
// Arduino MEGA 2650

const int a3 = 36;
const int a2 = 34;
const int a1 = 32;
const int a0 = 30;
const int startpin = 38;

int canEnterLED = 19;
int correctEnterLED = 20;

unsigned long getPasswordDuration = 15000; //30 seconds
unsigned long startTime = 0;
int validPassword = 10; // 1101 1000
int enteredPassword = 0;

void setup() {
 pinMode(a3, INPUT); pinMode(a2, INPUT); pinMode(a1, INPUT); pinMode(a0, INPUT);
 pinMode(startpin, INPUT);
 Serial.begin(9600);
 BTSerial.begin(9600);  // HC-05 default speed in AT command = 38400, HC 06 = 9600
 Serial.println("READY TO TRANSMIT");
 digitalWrite(canEnterLED, LOW);
 digitalWrite(correctEnterLED, LOW);
}

void loop() {

 if (digitalRead(startpin) == HIGH) {
   startTime = millis();
   while (millis() - startTime <= getPasswordDuration) {
      Serial.println("READY TO T");
      if (digitalRead(a3) == HIGH) {
         enteredPassword = enteredPassword | 8;
      }
      if (digitalRead(a2) == HIGH) {
         enteredPassword = enteredPassword | 4;
      }
      if (digitalRead(a1) == HIGH) {
         enteredPassword = enteredPassword | 2;
      }
      if (digitalRead(a0) == HIGH) {
         enteredPassword = enteredPassword | 1;
      }
      if (enteredPassword > validPassword) {
         BTSerial.write('0');
         Serial.println("wrong !!!! *********************************");
         enteredPassword = 0;
         break;
      }
      if (enteredPassword == validPassword) {
         BTSerial.write('1');
         Serial.println("correct*********************************");
         enteredPassword = 0;
         break;
      }
   }
   Serial.println("TIME IS UP");

 }
}
