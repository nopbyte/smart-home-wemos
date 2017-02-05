/*
  SensorConfiguration.h - Class to encapsulate the configuration files
  This class must be able to interpret all the configurations possible and read from all the sensors which are supported.
  
*/
#ifndef GenericAnalogSensorConfiguration_h
#define GenericAnalogSensorConfiguration_h

#include "Arduino.h"
#include "GenericAnalogSensorConfiguration.h"
#include "SensorConfiguration.h"
#include "DataUploader.h"
;

class GenericAnalogSensorConfiguration: public  SensorConfiguration
{
  private:
    int _minRange;
    int _maxRange;
    String _measurementName;
  public:
    explicit GenericAnalogSensorConfiguration(DataUploader* dataup, String type) : SensorConfiguration(dataup, type) {
        _minRange = 0;
        _maxRange = 0;
        _measurementName = "unkown name";
    }
    void execute();
    void init(ConfigurationValue* val);

};

#endif
