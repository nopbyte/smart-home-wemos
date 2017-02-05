/*
  SensorConfiguration.h - Class to encapsulate the configuration files

*/

#include "Arduino.h"
#include "SensorConfiguration.h"


SensorConfiguration::SensorConfiguration(DataUploader* up, String type)
{
  _successor = NULL;
  _confValues = NULL;
  _kind = type;
  _uploader = up;
  _location = "unknown location";
}

// Translates the pin name as a string for the actual pin value in the current board
int SensorConfiguration::getPinByString(String pinName){
  
   for(int i = 0; i<PINLENGTH; i++){
      if(_pinStrings[i] == pinName){
        return _pins[i]; 
      }
   }
   return -1;
   
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
void SensorConfiguration::init(ConfigurationValue* val)
{
  Serial.println(" should not happened... this init is happening for apbstract class with type "+_kind);
}

//configures the protected attributes, and calls the subclass when there is an attribute not recognized, so that the subclass can handle it.
void SensorConfiguration::setConfigurationValues(ConfigurationValue* confs){
  _confValues = confs;
  ConfigurationValue* tmp = _confValues;
  while(tmp != NULL){
    if(tmp->getKey() == "pin"){
      _pin = tmp->getValue();
    }
    else if(tmp->getKey() == "location"){
      _location = tmp->getValue();
    }
    else{
      init(tmp);
    }
    tmp = tmp->next();
  }
}

