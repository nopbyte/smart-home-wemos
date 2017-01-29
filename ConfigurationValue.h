/*
  SensorConfiguration.h - Class to encapsulate the configuration files
  
*/
#ifndef ConfigurationValue_h
#define ConfigurationValue_h

#include "Arduino.h"

class ConfigurationValue
{
  public:
    ConfigurationValue(String key, String value);
    String key; 
    String value;
    void setSuccessor(ConfigurationValue* suc);
    ConfigurationValue* next();
  private:
    ConfigurationValue* _successor;
    

};

#endif
