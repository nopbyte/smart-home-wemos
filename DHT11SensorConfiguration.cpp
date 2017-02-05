/*
  SensorConfiguration.h - Class to encapsulate the configuration files

*/

#include "Arduino.h"
#include "DHT11SensorConfiguration.h"


/*DHT11SensorConfiguration::DHT11SensorConfiguration(){

}
*/
void DHT11SensorConfiguration::init(ConfigurationValue* val){
  //no additional configuration values
}
void DHT11SensorConfiguration::execute()
{
  int pin = getPinByString(_pin);
  //in the future... make the DHT11 or 22,,, etc configurable
  DHT dht(pin, DHT11);    
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else{
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("connecting to ");
    Serial.println("kind: "+_kind);
    Serial.println("pin: "+_pin);
    Serial.println("Actual pin as int: "+String(pin));
    Serial.println("location: "+_location);
    Serial.println("reading sensor!");
    _uploader->uploadDataFloat("temperature", _location, t);
    _uploader->uploadDataFloat("humidity", _location, h);

  
  }

  
}
