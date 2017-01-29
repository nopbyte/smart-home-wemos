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
    void setKey(String k);
    void setValue(String v);
    String getKey();
    String getValue();
    void setSuccessor(ConfigurationValue* suc);
    ConfigurationValue* next();
  private:
    String _key; 
    String _value;
    ConfigurationValue* _successor;
    

};

#endif
