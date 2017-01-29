/*
  DataUploader.cpp.

*/
#include "Arduino.h"
#include "DataUploader.h"

DataUploader::DataUploader(WifiConnection* wifi, char *host, int port,  ConfigurationValue* additionalConfs){
  _wifi = wifi;
  _host = host;
  _port = port;
  _additionalConfs = additionalConfs;
}

