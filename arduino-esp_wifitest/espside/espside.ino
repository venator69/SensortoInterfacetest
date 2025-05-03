void setup() {

}

void loop() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');  // Read a full line
    Serial.println("Received: " + data);
  }
}
