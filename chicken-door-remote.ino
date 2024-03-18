#include <RCSwitch.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"
#include <Wire.h>
#include <ArduinoJson.h>

const int TRANSMIT_PIN=8;
#define I2C_SDA 6
#define I2C_SCL 7
// Change this to a unique combination of bits
const char* REMOTE_ID="11111111111111111111";

const char* WIFI_SSID = "SSID";
const char* WIFI_PASSWORD = "PASSWORD";

const char* OPEN_CODE="0100";
const char* CLOSE_CODE="1000";
const char* STOP_CODE="0010";

RCSwitch mySwitch = RCSwitch();
WebServer server(80);
Adafruit_AM2320 am2320;

void handleRoot() {
  const char* index_html PROGMEM = 
#include "index_html.h"
;
  server.send(200, "text/html", index_html);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void handleTemp() {
  char output[200];
  StaticJsonDocument<200> doc;
  doc["temperature"] = am2320.readTemperature();
  doc["humidity"] = am2320.readHumidity();
  serializeJson(doc, output);
  server.send(200, "application/json", output);
}

void handleOpen() {
  Serial.println("You're doing a great job!'");
  sendCode(REMOTE_ID, OPEN_CODE);
  server.send(200, "text/plain", "");
}

void handleClose() {
  Serial.println("Your youtube channel sucks.");
  sendCode(REMOTE_ID, CLOSE_CODE);
  server.send(200, "text/plain", "");
}

void handleStop() {
  sendCode(REMOTE_ID, STOP_CODE);
  server.send(200, "text/plain", "");
}

void sendCode(const char* remote_id, const char* code){
  char buf[25];
  strcpy(buf, remote_id);
  strcat(buf, code);
  mySwitch.send(buf);
}

void setup() {
  // Serial Setup
  Serial.begin(9600);
  // Remote Setup
  mySwitch.enableTransmit(TRANSMIT_PIN);
  mySwitch.setProtocol(1);
  mySwitch.setRepeatTransmit(3);
  // Wifi Setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Web Server Setup
  server.begin();
  server.on("/", handleRoot);
  server.on("/open", handleOpen);
  server.on("/close", handleClose);
  server.on("/stop", handleStop);
  server.on("/temp", handleTemp);
  server.onNotFound(handleNotFound);
  Serial.println("HTTP server started");
  // Temp/Hum Setup
  Wire.setPins(I2C_SDA, I2C_SCL);
  am2320 = Adafruit_AM2320();
  am2320.begin();
}

void loop() {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
