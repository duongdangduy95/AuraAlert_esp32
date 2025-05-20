#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>
#include <Preferences.h>
#include <PubSubClient.h>
#include <time.h> // For SNTP time synchronization

#define PIR_PIN 19
#define ISD1820_PLAY_PIN 18
#define RESET_WIFI_PIN 0

const char* apSSID = "ESP32-Config";
const char* apPassword = "12345678";


const char* mqttServer = "1c96de2709a740a68e5b6d81365811b2.s1.eu.hivemq.cloud"; 
const int mqttPort = 8883;
const char* mqttUser = "duyduong"; 
const char* mqttPassword = "Duy10012004/"; 

//  Replace with your HiveMQ Cloud CA certificate!
const char* rootCACertificate = \
"-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"-----END CERTIFICATE-----\n";


Preferences preferences;
WebServer server(80);
WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);

String ssid, password;
bool wifiConnected = false;
String macAddr;
unsigned long lastReconnectAttempt = 0;

void sendMQTTAlert(String message) {
  if (!mqttClient.connected()) {
    return;
  }
  String topic = "/alert/motion"; // Keep the topic
  mqttClient.publish(topic.c_str(), message.c_str(), false);
  Serial.println("📤 Gửi MQTT đến " + topic + " với nội dung: " + message);
}

void handleRoot() {
  if (!server.authenticate("admin", "1234")) return server.requestAuthentication();

  String html = "<h1>Cấu hình Wi-Fi</h1><form action='/save' method='POST'>";
  html += "SSID: <input name='ssid'><br>";
  html += "Password: <input name='password' type='password'><br>";
  html += "<input type='submit' value='Lưu cấu hình'></form>";
  server.send(200, "text/html", html);
}

void handleSave() {
  if (!server.authenticate("admin", "1234")) return server.requestAuthentication();

  ssid = server.arg("ssid");
  password = server.arg("password");

  preferences.begin("config", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();

  server.send(200, "text/html", "<h2>Đã lưu cấu hình. Đang khởi động lại...</h2>");
  delay(2000);
  ESP.restart();
}

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(RESET_WIFI_PIN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);
  pinMode(ISD1820_PLAY_PIN, OUTPUT);
  digitalWrite(ISD1820_PLAY_PIN, LOW);

  preferences.begin("config", true);
  ssid = preferences.getString("ssid", "Redmi 10");  // Keep your defaults
  password = preferences.getString("password", "10012004"); // Keep your defaults
  preferences.end();

  macAddr = WiFi.macAddress();

  if (ssid.length() > 0 && password.length() > 0) {
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("⏳ Kết nối Wi-Fi...");
    unsigned long t = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - t < 10000) {
      delay(500); Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n✅ Wi-Fi thành công");
      wifiConnected = true;
    } else {
      Serial.println("\n❌ Wi-Fi thất bại, chuyển sang cấu hình AP");
    }
  }

  if (!wifiConnected) {
    WiFi.softAP(apSSID, apPassword);
    Serial.println("⚙️ Phát Wi-Fi cấu hình: " + String(apSSID));
    Serial.println("🔗 Truy cập: http://" + WiFi.softAPIP().toString());
    server.on("/", handleRoot);
    server.on("/save", handleSave);
    server.begin();
  }

  // Initialize MQTT
  secureClient.setCACert(rootCACertificate); // Use the CA certificate here
  mqttClient.setServer(mqttServer, mqttPort);

    // Initialize time for SSL
  if (wifiConnected) {
    configTime(0, 0, "pool.ntp.org");  // Get time from NTP server
    struct tm timeinfo;
     if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
     }
     else{
       Serial.println("Time synchronized");
     }
  }
}

void reconnectMQTT() {
  if (millis() - lastReconnectAttempt >= 5000) {
    lastReconnectAttempt = millis();
    if (!mqttClient.connected()) {
      Serial.println("Attempting MQTT connection...");
      if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {
        Serial.println("✅ MQTT connected");
      } else {
        Serial.print("❌ MQTT connect failed, rc=");
        Serial.println(mqttClient.state());
      }
    }
  }
}

void loop() {
  if (wifiConnected) {
    reconnectMQTT();
    mqttClient.loop();
  } else {
    server.handleClient();
  }

  if (digitalRead(PIR_PIN) == HIGH) {
    Serial.println("🚨 Phát hiện chuyển động!");
    digitalWrite(ISD1820_PLAY_PIN, HIGH);
    delay(2000);
    digitalWrite(ISD1820_PLAY_PIN, LOW);

    if (wifiConnected && mqttClient.connected()) {
      String msg = "{\"event\":\"motion_detected\",\"mac\":\"" + macAddr + "\",\"message\":\"Phát hiện xâm nhập!\"}";
      sendMQTTAlert(msg);
    } else {
      Serial.println("⚠️ Không gửi được MQTT: Chưa kết nối");
    }
    delay(3000);
  }
  delay(100);
}
