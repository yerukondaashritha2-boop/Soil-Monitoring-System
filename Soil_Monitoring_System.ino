#include <WiFi.h>
#include <WebServer.h>

/* ---------- WiFi Credentials ---------- */
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

/* ---------- Pin Definitions ---------- */
#define SOIL_PIN   34
#define MOTOR_PIN  26

WebServer server(80);
bool motorState = false;

/* ---------- Web Page ---------- */
void handleRoot() {
  int soilValue = analogRead(SOIL_PIN);
  int moisturePercent = map(soilValue, 4095, 0, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  String moistureStatus = (moisturePercent < 40) ? "DRY" : "GOOD";
  String statusColor = (moisturePercent < 40) ? "#ff4d4d" : "#00c853";

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>Smart Irrigation</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>
  body{
    margin:0;
    font-family:'Segoe UI',sans-serif;
    background:linear-gradient(135deg,#a8e063,#56ab2f);
    color:#fff;
    text-align:center;
  }
  .card{
    background:#ffffff;
    color:#333;
    width:90%;
    max-width:400px;
    margin:30px auto;
    padding:25px;
    border-radius:20px;
    box-shadow:0 10px 30px rgba(0,0,0,0.2);
  }
  h1{
    margin-bottom:10px;
    color:#2e7d32;
  }
  .value{
    font-size:36px;
    font-weight:bold;
    margin:10px 0;
  }
  .status{
    font-size:18px;
    margin:10px 0;
    font-weight:600;
  }
  .motor{
    margin:15px 0;
    font-size:18px;
  }
  button{
    width:80%;
    padding:14px;
    margin:8px;
    border:none;
    border-radius:30px;
    font-size:16px;
    cursor:pointer;
    transition:0.3s;
  }
  .on{
    background:#00c853;
    color:white;
  }
  .off{
    background:#d50000;
    color:white;
  }
  button:hover{
    transform:scale(1.05);
    opacity:0.9;
  }
  footer{
    margin-top:15px;
    font-size:12px;
    color:#555;
  }
</style>
</head>
<body>

<div class="card">
  <h1>🌱 Smart Irrigation</h1>

  <div class="value">MOISTURE: %MOISTURE%%</div>
  <div class="status" style="color:%COLOR%;">
    STATUS: %STATUS%
  </div>

  <div class="motor">
    💧 Motor: <b>%MOTOR%</b>
  </div>

  <form action="/motorOn">
    <button class="on">Turn Motor ON</button>
  </form>

  <form action="/motorOff">
    <button class="off">Turn Motor OFF</button>
  </form>

  <footer>ESP32 Web Control</footer>
</div>

</body>
</html>
)rawliteral";

  html.replace("%MOISTURE%", String(moisturePercent));
  html.replace("%STATUS%", moistureStatus);
  html.replace("%COLOR%", statusColor);
  html.replace("%MOTOR%", motorState ? "ON" : "OFF");

  server.send(200, "text/html", html);
}

/* ---------- Motor Control ---------- */
void handleMotorOn() {
  digitalWrite(MOTOR_PIN, HIGH);
  motorState = true;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleMotorOff() {
  digitalWrite(MOTOR_PIN, LOW);
  motorState = false;
  server.sendHeader("Location", "/");
  server.send(303);
}

/* ---------- Setup ---------- */
void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/motorOn", handleMotorOn);
  server.on("/motorOff", handleMotorOff);
  server.begin();
}

/* ---------- Loop ---------- */
void loop() {
  server.handleClient();
}
