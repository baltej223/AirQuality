#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = " ";
const char* password = " ";

//Your Domain name with URL path or IP address with path
String serverName = "http://dweet.io:80/dweet/for/B0x1324d47hc33";
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
HTTPClient http;
void loop() {
  // Send an HTTP POST request depending on timerDelay
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String serverPath = serverName +"?AirIndex="+String(analogRead(A0));

    // Your Domain name with URL path or IP address with path
    http.begin(client, serverPath.c_str());

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString(); //it has the json that has come as a reply from server 
      Serial.println(payload);
    } 
    else {
      Serial.print("Error code: ");
      Serial.println(int(http.GET()));
    }
    // Free resources
    http.end();
    delay(5000);
}
}
