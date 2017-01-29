/*
  SensorConfiguration.h - Class to encapsulate the configuration files
  This class must be able to interpret all the configurations possible and read from all the sensors which are supported.
  
*/
#ifndef DHT11SensorConfiguration_h
#define DHT11SensorConfiguration_h

#include "Arduino.h"
#include "SensorConfiguration.h"


class DHT11SensorConfiguration: public  SensorConfiguration
{

  public:
    explicit DHT11SensorConfiguration(String dataup, String type) : SensorConfiguration(dataup, type) { }
    void execute();
    void init();

};

#endif
