#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

IPAddress staticIP(192, 168, 31, 102);
IPAddress gateway(192, 168, 31, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "Door";
String serverUrl = "192.168.1.100:5000";
String payload;
String device_key = "rfid_secret";
String command = "rfid_sensor";
String validation_key = "key";
String stream;

ESP8266WebServer server(80);

String key_input = "<input style=\"height: 200px;width: 600px;font-size: 50px;\" type=\"text\" name=\"key_input\" placeholder=\"ID Key\"></br>";
String submit_input = "<input type=\"submit\" style=\"border-radius: 50px 50px 50px 50px;text-align:center;height:150px;font-size:50px;width:400px;color:white;background-color: #00A8A9\" value=\"Validate\">";


String div_view = "<div>";
String form_view = "<form style=\"margin-top: 180px;display:flex;flex-direction: column;align-items: center;\" action=\"/validate_key\" method=\"POST\">";
String form_end_view = "</form></div>";
String html_view = div_view + form_view + key_input + submit_input + form_end_view;


void handlePong() {
  server.send(200, "text/html", device_key);
}


void handleDoorAction() {
  String command = server.arg("command");
  command.trim();

  String secret = server.arg("secret");
  secret.trim();

  if (secret == device_key){
    if(command == "open_door"){
      Serial.println("open_door");
    }
  }
  server.send(200, "text/html", "OK");
}

void handleRoot(){
  server.send(200, "text/html", html_view);
}

void handleValidation(){
  if( !server.hasArg("key_input") || server.arg("key_input") == NULL) {
    server.send(200, "text/html", html_view);
    return;
  }
  if(server.arg("key_input") == validation_key) {
    Serial.println("open_door");
    server.send(200, "text/html", html_view);
  } else {
    server.send(200, "text/html", html_view);
  }
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  delay(500);
  Serial.println(WiFi.localIP());

  server.on("/ping/", handlePong);
  server.on("/door/", handleDoorAction);
  server.on("/validation/", handleRoot);
  server.on("/validate_key", handleValidation);
  server.begin();
}


void loop() {
  server.handleClient();
  // sendDataFromMaster();
}


// void sendDataFromMaster(){
//   stream="";
//   if (Serial.available()!=0){
//     stream = Serial.readStringUntil('\n');
//     stream.trim();
//     if (stream.length()>0){
//       Serial.println(stream);
//       String argument_data = "?device_key="+device_key+"&command="+command+"&data="+String(stream);
//       sendRequest("http://"+serverUrl+"/esp/door/",argument_data);
//     }
//   }
// }


// void sendRequest(String path, String sendingData){
//   if(WiFi.status()== WL_CONNECTED){
//     String serverPath = path+sendingData;
//     Serial.println(serverPath);
//     payload = httpGETRequest(serverPath.c_str());
//     Serial.println(payload);
//   }
//   else {
//     Serial.println("WiFi Disconnected");
//   }
// }


// String httpGETRequest(const char* serverName) {
//   HTTPClient http;
//   http.begin(serverName);
//   int httpResponseCode = http.GET();
//   String payload = "{}";
//   if (httpResponseCode>0) {
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);
//     payload = http.getString();
//   }
//   else {
//     Serial.print("Error code: ");
//     Serial.println(httpResponseCode);
//   }
//   http.end();
//   return payload;
// }
