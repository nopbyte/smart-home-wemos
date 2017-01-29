/*
  SensorConfiguration.h - Class to encapsulate the configuration files

*/

#include "Arduino.h"
#include "DHT11SensorConfiguration.h"

/*DHT11SensorConfiguration::DHT11SensorConfiguration(){

}
*/
void DHT11SensorConfiguration::init(){
  
}
void DHT11SensorConfiguration::execute()
{
  //Serial.println(" ------sensor of type ------ "+_kind);

  ConfigurationValue* tmp = _confValues;
  while(tmp!=NULL){
    Serial.println(" -- key"+tmp->key+", "+tmp->value);
    tmp = tmp->next();
  }
  Serial.println("reading sensor!");
}
