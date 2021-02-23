#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 145); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "dkWork";
const char* password = "d152535k";
const char* deviceName = "Hehehehe";
String serverUrl = "192.168.1.100:5000";
String payload;
String device_key = "rfid_secret";
String command = "rfid_sensor";


ESP8266WebServer server(80);

String stream;


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



void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
 
  WiFi.mode(WIFI_STA);
 
//  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
//  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/ping/", handlePong);
  
  server.on("/door/", handleDoorAction);
 
  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
  sendDataFromMaster();
}


void sendDataFromMaster(){
  stream="";
  if (Serial.available()!=0){
    stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length()>0){
      Serial.println(stream);
      String argument_data = "?device_key="+device_key+"&command="+command+"&data="+String(stream);
      sendRequest("http://"+serverUrl+"/esp/door/",argument_data);
    }
  }
}


void sendRequest(String path, String sendingData){
  if(WiFi.status()== WL_CONNECTED){
    String serverPath = path+sendingData;
    Serial.println(serverPath);
    payload = httpGETRequest(serverPath.c_str());
    Serial.println(payload);
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}


String httpGETRequest(const char* serverName) {
  HTTPClient http;
  http.begin(serverName);
  int httpResponseCode = http.GET();  
  String payload = "{}"; 
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}