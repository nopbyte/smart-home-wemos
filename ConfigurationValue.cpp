/*
  Configuration.h - Class to encapsulate the configuration files

*/

#include "Arduino.h"
#include "ConfigurationValue.h"


ConfigurationValue::ConfigurationValue(String k, String v)
{
  _successor = NULL;
  key = k;
  key.trim();
  value = v;
  v.trim();
}
void ConfigurationValue::setSuccessor(ConfigurationValue* suc){
  Serial.print("setting successor as "+suc->key+" " +suc->value);
  _successor = suc;
}
ConfigurationValue* ConfigurationValue::next(){
  return _successor;
}

