#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid     = "Itsme";
const char* password = "Letsfly1!";
const char* serverName = "http://192.168.41.72:3000/api/sensor-data"; // Use your server's IP address instead of localhost when testing with ESP32

void setup() {
  Serial.begin(115200);  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {  
  float temperature = 24.3; 
  float humidity = 60.2;  
  
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;    
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");    
    String httpRequestData = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
    Serial.print("Sending data: ");
    Serial.println(httpRequestData);   
    int httpResponseCode = http.POST(httpRequestData);
    String response = http.getString();    
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.print("Response: ");
    Serial.println(response);    
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }  
  delay(3000);
}

