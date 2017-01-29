/*
  Configuration.h - Class to encapsulate the configuration files

*/

#include "Arduino.h"
#include "ConfigurationValue.h"


ConfigurationValue::ConfigurationValue(String k, String v)
{
  _successor = NULL;
  _key = k;
  _key.trim();
  _value = v;
  _value.trim();
}
void ConfigurationValue::setKey(String k){
  _key = k;
  _key.trim();
}
void ConfigurationValue::setValue(String v){
  _value = v;
  _value.trim();
}

String ConfigurationValue::getKey(){
  return _key;
}
String ConfigurationValue::getValue(){
  return _value;
}
void ConfigurationValue::setSuccessor(ConfigurationValue* suc){
  _successor = suc;
}
ConfigurationValue* ConfigurationValue::next(){
  return _successor;
}

