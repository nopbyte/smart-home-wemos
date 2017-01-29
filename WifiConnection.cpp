/*
  WifiConnection.cpp - Class to encapsulate the wifi connection
  
*/

#include "Arduino.h"
#include "WifiConnection.h"

WifiConnection::WifiConnection(const char* ssid, const char* password)
{
   Serial.print("Connecting to ");
   Serial.println(ssid);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BUILTIN_LED, 0);  // turn on LED with voltage HIGH
    delay(500);                       
    digitalWrite(BUILTIN_LED, 1);   // turn off LED with voltage LOW
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
/* 
  This sends an HTTP request to confServer and port
  verb is the HTTP verb GET, POST, etc... 
  url is just the path (/some/?id=123) and data is the body as text.
*/


String WifiConnection::exchangeHttp(char *confServer, int port, String verb,  String url, String data)
{

  
   Serial.print("connecting to ");
   Serial.println(confServer);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  
  if (!client.connect(confServer, port)) {
    Serial.println("connection failed. Attempted to talk to "+String(confServer)+" and port " +port);
    return "";
  }

  Serial.print("Requesting URL: ");
  Serial.println(url);
  String http = verb + " "+ url + " HTTP/1.1\r\n" +
               "Content-Length: " +data.length() + "\r\n"+
               "Host: " + confServer + "\r\n" + 
               "Connection: close\r\n"+ "\r\n"+
               data + "\r\n";
  client.print(http);
  Serial.println(http);
  unsigned long timeout = millis();
  
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return "";
    }
  }
  String result = "";
  // Read all the lines of the reply from confServer and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    result = result +  line;
    
  }
  Serial.println("closing connection");
  Serial.println();
  return result;
}

