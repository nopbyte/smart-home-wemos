/*
  SensorConfiguration.h - Class to encapsulate the configuration files

*/

#include "Arduino.h"
#include "SensorConfiguration.h"


SensorConfiguration::SensorConfiguration(String up, String type)
{
  _successor = NULL;
  _confValues = NULL;
  _kind = type;
  //_uploader = up;
  _location = "unknown location";
}
void SensorConfiguration::setKind(String k){
   _kind = k;
   _kind.trim();
}
void SensorConfiguration::setPin(String p){
   _pin = p;
   _pin.trim();
}
void SensorConfiguration::setLocation(String l){
   _location = l;
   _location.trim();
}
    
void SensorConfiguration::setSuccessor(SensorConfiguration* suc){
  _successor = suc;
}
SensorConfiguration* SensorConfiguration::next(){
  return _successor;
}
void SensorConfiguration::execute()
{
  Serial.println(" should not happened... this execute is happening for apbstract class with type "+_kind);
}
void SensorConfiguration::init()
{
  Serial.println(" should not happened... this init is happening for apbstract class with type "+_kind);
}
void SensorConfiguration::setConfigurationValues(ConfigurationValue* confs){
  _confValues = confs;
}

