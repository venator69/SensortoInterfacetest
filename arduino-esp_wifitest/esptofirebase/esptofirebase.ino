#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace with your Wi-Fi credentials
#define WIFI_SSID "clement gay"
#define WIFI_PASSWORD "clement69"

// Replace with your Firebase project credentials
#define FIREBASE_HOST "your-project-id.firebaseio.com"  // No "https://"
#define FIREBASE_AUTH "YOUR_FIREBASE_DATABASE_SECRET_OR_WEB_API_KEY"

FirebaseData fbdo;

void setup() {
  Serial.begin(115200);  // Serial Monitor
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 for external UART

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase initialized");
}

void loop() {
  // Read from Serial2 (e.g., data sent from Arduino)
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    data.trim();  // Remove newline or spaces
    Serial.println("Received: " + data);

    // Convert and send to Firebase
    if (Firebase(fbdo, "/sensor/value", data)) {
      Serial.println("Data sent to Firebase: " + String(data));
    } else {
      Serial.println("Failed to send data: " + fbdo.errorReason());
    }
  }
}
