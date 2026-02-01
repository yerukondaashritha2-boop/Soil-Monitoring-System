#include <WiFi.h>
#include <WebServer.h>

/* -------- WiFi Credentials -------- */
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

/* -------- Web Page with Fake Data -------- */
void handleRoot() {

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
    background:linear-gradient(135deg,#43cea2,#185a9d);
    min-height:100vh;
    display:flex;
    justify-content:center;
    align-items:center;
    color:#fff;
  }

  .card{
    background:rgba(255,255,255,0.15);
    backdrop-filter:blur(12px);
    width:90%;
    max-width:420px;
    padding:25px;
    border-radius:25px;
    box-shadow:0 20px 40px rgba(0,0,0,0.3);
    text-align:center;
  }

  h1{ margin-bottom:15px; }

  .circle{
    width:180px;
    height:180px;
    border-radius:50%;
    display:flex;
    align-items:center;
    justify-content:center;
    margin:20px auto;
    transition:0.5s;
  }

  .circle span{
    background:#111;
    width:140px;
    height:140px;
    border-radius:50%;
    display:flex;
    align-items:center;
    justify-content:center;
    font-size:30px;
    font-weight:bold;
  }

  .status{
    margin:10px 0;
    font-size:18px;
    font-weight:600;
  }

  .motor{
    margin:15px 0;
    font-size:18px;
  }

  button{
    width:85%;
    padding:14px;
    margin-top:10px;
    border:none;
    border-radius:40px;
    font-size:16px;
    font-weight:600;
    cursor:pointer;
    transition:0.3s;
  }

  .on{
    background:linear-gradient(135deg,#00c853,#64dd17);
    color:white;
  }

  .off{
    background:linear-gradient(135deg,#ff1744,#d50000);
    color:white;
  }

  footer{
    margin-top:15px;
    font-size:12px;
    opacity:0.8;
  }
</style>
</head>

<body>

<div class="card">
  <h1>🌱 Smart Irrigation (Demo)</h1>

  <div class="circle" id="circle">
    <span id="moisture">--%</span>
  </div>

  <div class="status" id="status">STATUS</div>

  <div class="motor">
    💧 Motor: <b id="motor">--</b>
  </div>

  <button id="motorBtn">---</button>

  <footer>ESP32 • Fake Data Preview</footer>
</div>

<script>
  function updateFakeData(){
    let moisture = Math.floor(Math.random() * 101);
    let motorOn = Math.random() > 0.5;

    document.getElementById("moisture").innerText = moisture + "%";

    document.getElementById("circle").style.background =
      `conic-gradient(
        #00e676 ${moisture}%,
        rgba(255,255,255,0.2) ${moisture}%
      )`;

    let statusText = moisture < 40 ? "DRY – Water Needed" : "GOOD – Moisture OK";
    let statusColor = moisture < 40 ? "#ff5252" : "#69f0ae";

    document.getElementById("status").innerText = statusText;
    document.getElementById("status").style.color = statusColor;

    document.getElementById("motor").innerText = motorOn ? "ON" : "OFF";

    let btn = document.getElementById("motorBtn");
    btn.innerText = motorOn ? "Turn Motor OFF" : "Turn Motor ON";
    btn.className = motorOn ? "off" : "on";
  }

  updateFakeData();
  setInterval(updateFakeData, 3000);
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

/* -------- Setup -------- */
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

/* -------- Loop -------- */
void loop() {
  server.handleClient();
}
