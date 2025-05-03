#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int arrayval[8];
int i = 0;

void setup() {
  Serial.begin(9600);          // Also initialize the main serial monitor
  mySerial.begin(9600);        // Initialize SoftwareSerial
  randomSeed(analogRead(0));   // Seed randomness
}

void loop() {
  String arraystring = ""; // Arduino String class

  for (i = 0; i < 8; i++) {
    arrayval[i] = random(0, 168);
    arraystring += String(arrayval[i]);
    if (i != 7) {
      arraystring += ", ";
    }
  }
  mySerial.println(arraystring);
  Serial.println("transmitting " + arraystring);
  delay(1000);
}