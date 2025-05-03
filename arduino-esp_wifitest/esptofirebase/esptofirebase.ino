#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace with your Wi-Fi credentials
#define WIFI_SSID "clement gay"
#define WIFI_PASSWORD "clement69"

// Replace with your Firebase Realtime Database credentials
#define FIREBASE_HOST "https://fir-dataflow-a29b9-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "of4Nc0Ijz8OjKW6UMzP0eO7Wx0khNw9CoT0UqnPL"  // Or Web API Key if using token-based auth

FirebaseData fbdo;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17

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
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    data.trim();  // Remove any extra spaces or newlines
    Serial.println("Received: " + data);

    // Upload to Firebase
    if (Firebase.setString(fbdo, "/sensor/value", data)) {
      Serial.println("Data sent to Firebase: " + data);
    } else {
      Serial.println("Firebase error: " + fbdo.errorReason());
    }
  }
}
