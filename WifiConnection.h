/*
  WifiConnection.h - Class to encapsulate the wifi connection
  
*/
#ifndef WifiConnection_h
#define WifiConnection_h

#include "Arduino.h"
#include <ESP8266WiFi.h>

class WifiConnection
{
  public:
    WifiConnection(const char* ssid, const char* password);
    String exchangeHttp(char *confServer, int port, String verb,  String url, String data);
};

#endif
