/*
  DataUploader.h - Class to encapsulate the cdata upload

  
*/
#ifndef DataUploader_h
#define DataUploader_h

#include "Arduino.h"
#include "WifiConnection.h"
#include "ConfigurationValue.h"


class DataUploader
{
  private:
   //necessary to navigate as linked list.  
   WifiConnection* _wifi;
   char* _host;
   int _port;
   ConfigurationValue* _additionalConfs;
  public:
    DataUploader(WifiConnection* wifi, char *host, int port, ConfigurationValue* additionalConfs);
};

#endif
