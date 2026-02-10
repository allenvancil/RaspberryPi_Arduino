#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "chicken2_4";
const char* password = "Pashinka10!";

// Try a safer pin than GPIO2 if you can: 25, 26, 27, 32, 33 are great PWM pins.
// If you MUST use 2, keep it, but note it's often the onboard LED / boot strap.
const int output = 2;

String sliderValue = "0";

// PWM properties
const int freq = 300;        // was 1 Hz
const int ledChannel = 0;
const int resolution = 8;

const char* PARAM_INPUT = "value";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP Web Server</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; }
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  <p><span id="textSliderValue">%SLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="0" max="255" value="%SLIDERVALUE%" step="1" class="slider"></p>
<script>
function updateSliderPWM(element) {
  var sliderValue = document.getElementById("pwmSlider").value;
  document.getElementById("textSliderValue").innerHTML = sliderValue;
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value="+sliderValue, true);
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

String processor(const String& var){
  if (var == "SLIDERVALUE") return sliderValue;
  return String();
}

void setup(){
  Serial.begin(115200);

  // Setup PWM and attach to pin
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(output, ledChannel);
  ledcWrite(ledChannel, 0);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html, processor);
  });

  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;

      int duty = sliderValue.toInt();
      if (duty < 0) duty = 0;
      if (duty > 255) duty = 255;

      ledcWrite(ledChannel, duty);   // <-- FIX: write to channel, not pin
    } else {
      inputMessage = "No message sent";
    }
    Serial.print("Duty: ");
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {}
