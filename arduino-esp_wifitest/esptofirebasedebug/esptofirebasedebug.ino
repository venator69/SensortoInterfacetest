#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace with your network credentials
#define WIFI_SSID "clement gay"
#define WIFI_PASSWORD "clement69"

// Replace with your Firebase project credentials
#define FIREBASE_HOST "your-project-id.firebaseio.com"
#define FIREBASE_AUTH "YOUR_WEB_API_KEY"

FirebaseData fbdo;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 — adjust as needed

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Send data to Firebase
  if (Firebase.setInt(fbdo, "/sensor/value", 123)) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Failed to send data: " + fbdo.errorReason());
  }
}

void loop() {
  // Optional: read back value
  if (Firebase.getInt(fbdo, "/sensor/value")) {
    Serial.print("Value from Firebase: ");
    Serial.println(fbdo.intData());
  }
  delay(5000);
}
