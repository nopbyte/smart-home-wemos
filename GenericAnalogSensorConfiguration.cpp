/*
  GenericAnalogSensorConfiguration.h - Class to encapsulate the configuration files

*/

#include "Arduino.h"
#include "GenericAnalogSensorConfiguration.h"



void GenericAnalogSensorConfiguration::init(ConfigurationValue* val){
  Serial.println("getting configuration value in Generic Sensor");
  Serial.println("k "+val->getKey());
  Serial.println("v "+val->getValue());
  
  if(val->getKey() == "measurementName"){
    _measurementName = val->getValue();
  }
  if(val->getKey() == "minRange"){
    _minRange = val->getValue().toInt();
  }
  if(val->getKey() == "maxRange"){
    _maxRange = val->getValue().toInt();
  }
  
}
void GenericAnalogSensorConfiguration::execute()
{
  int pin = getPinByString(_pin);
  float percentage = 0;
  int sensorValue = analogRead(pin);   
  percentage = (sensorValue*100)/(_maxRange-_minRange);
  _uploader->uploadDataFloat(_measurementName, _location, percentage);
}
