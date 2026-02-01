#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

/* ------------ WiFi Credentials ------------ */
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

/* ------------ Pin Definitions ------------ */
#define SOIL_PIN   34
#define MOTOR_PIN  26
#define DHT_PIN    27
#define DHT_TYPE   DHT11

/* ------------ Objects ------------ */
WebServer server(80);
DHT dht(DHT_PIN, DHT_TYPE);

/* ------------ System Variables ------------ */
bool motorState = false;
bool autoMode = true;

int moisturePercent = 0;
float temperature = 0;
float humidity = 0;

const int MOISTURE_THRESHOLD = 40;  // Auto irrigation limit

/* ------------ Read Sensors ------------ */
void readSensors() {
  int soilRaw = analogRead(SOIL_PIN);
  moisturePercent = map(soilRaw, 4095, 0, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (autoMode) {
    if (moisturePercent < MOISTURE_THRESHOLD) {
      digitalWrite(MOTOR_PIN, HIGH);
      motorState = true;
    } else {
      digitalWrite(MOTOR_PIN, LOW);
      motorState = false;
    }
  }
}

/* ------------ Web UI ------------ */
void handleRoot() {
  readSensors();

  String status = moisturePercent < MOISTURE_THRESHOLD ? "DRY" : "GOOD";
  String statusColor = moisturePercent < MOISTURE_THRESHOLD ? "#ff5252" : "#00e676";

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>Smart Irrigation MVP</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>
body{
  margin:0;
  font-family:Segoe UI,sans-serif;
  background:linear-gradient(135deg,#43cea2,#185a9d);
  min-height:100vh;
  display:flex;
  justify-content:center;
  align-items:center;
  color:white;
}
.card{
  background:rgba(255,255,255,0.15);
  backdrop-filter:blur(12px);
  padding:25px;
  width:90%;
  max-width:420px;
  border-radius:25px;
  box-shadow:0 20px 40px rgba(0,0,0,0.3);
  text-align:center;
}
.circle{
  width:160px;height:160px;border-radius:50%;
  background:conic-gradient(#00e676 %MOISTURE%%,rgba(255,255,255,0.2) %MOISTURE%%);
  display:flex;align-items:center;justify-content:center;
  margin:15px auto;
}
.circle span{
  background:#111;width:120px;height:120px;border-radius:50%;
  display:flex;align-items:center;justify-content:center;
  font-size:26px;font-weight:bold;
}
button{
  width:90%;padding:14px;margin:8px 0;
  border:none;border-radius:40px;
  font-size:16px;font-weight:600;cursor:pointer;
}
.on{background:#00c853;color:white;}
.off{background:#d50000;color:white;}
.auto{background:#2979ff;color:white;}
</style>
</head>

<body>
<div class="card">
<h2>🌱 Smart Irrigation (MVP)</h2>

<div class="circle">
  <span>%MOISTURE%%</span>
</div>

<p style="color:%COLOR%;font-weight:bold;">STATUS: %STATUS%</p>

<p>🌡 Temp: <b>%TEMP% °C</b></p>
<p>💧 Humidity: <b>%HUM% %</b></p>

<p>🚿 Motor: <b>%MOTOR%</b></p>
<p>🤖 Mode: <b>%MODE%</b></p>

<form action="/toggleMotor"><button class="%BTNCLASS%">%BTNTEXT%</button></form>
<form action="/toggleMode"><button class="auto">Toggle Auto / Manual</button></form>

</div>
</body>
</html>
)rawliteral";

  html.replace("%MOISTURE%", String(moisturePercent));
  html.replace("%STATUS%", status);
  html.replace("%COLOR%", statusColor);
  html.replace("%TEMP%", isnan(temperature) ? "N/A" : String(temperature,1));
  html.replace("%HUM%", isnan(humidity) ? "N/A" : String(humidity,1));
  html.replace("%MOTOR%", motorState ? "ON" : "OFF");
  html.replace("%MODE%", autoMode ? "AUTO" : "MANUAL");
  html.replace("%BTNTEXT%", motorState ? "Turn Motor OFF" : "Turn Motor ON");
  html.replace("%BTNCLASS%", motorState ? "off" : "on");

  server.send(200, "text/html", html);
}

/* ------------ Controls ------------ */
void toggleMotor() {
  if (!autoMode) {
    motorState = !motorState;
    digitalWrite(MOTOR_PIN, motorState ? HIGH : LOW);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void toggleMode() {
  autoMode = !autoMode;
  server.sendHeader("Location", "/");
  server.send(303);
}

/* ------------ Setup ------------ */
void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggleMotor", toggleMotor);
  server.on("/toggleMode", toggleMode);
  server.begin();
}

/* ------------ Loop ------------ */
void loop() {
  server.handleClient();
}
