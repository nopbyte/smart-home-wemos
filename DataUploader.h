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
   //used for credentials in case they are needed
   String _database;
   String _username;
   String _password;
   //additional configurations
   ConfigurationValue* _additionalConfs;
   void parseConfs();

  protected:
    //this one can be reused in the future to send values as string and it used internally
    void uploadDataString(String measurementName, String location, String value);


  public:
    DataUploader(WifiConnection* wifi, char *host, int port, ConfigurationValue* additionalConfs);
    void setDataPort(int port);
    void uploadDataFloat(String measurementName, String location, float value);
    void uploadDataInt(String measurementName, String location, int value);
   
};

#endif
