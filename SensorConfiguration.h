/*
  SensorConfiguration.h - Class to encapsulate the configuration files
  This is meant to be used as an ABSTRACT class! Don't instantiate it!!!
  This class must be able to interpret all the configurations possible and read from all the sensors which are supported.
  
*/
#ifndef SensorConfiguration_h
#define SensorConfiguration_h

#include "Arduino.h"
#include "ConfigurationValue.h"
#include "DataUploader.h"



class SensorConfiguration
{
  private:
   //necessary to navigate as linked list.  
   SensorConfiguration* _successor;
   
  public:
    //Constructor
    SensorConfiguration(DataUploader* uploader, String type);
    //abstract method that subclasses should implement.
    //initialize. i.e. parse all the confValues and keep them in local variables
    virtual void init();
    //read and send data
    virtual void execute();

    //opperations to navigate as linked list
    void setSuccessor(SensorConfiguration* suc);
    SensorConfiguration* next();

    //setters for all attributes
    void setKind(String k);
    void setPin(String p);
    void setLocation(String l);
    void setConfigurationValues(ConfigurationValue* confs);
    
  protected:
   //all inherited attributes
   String _kind; //reflecting the class that has been loaded. this info is used to instantiate the propper subclass in the main .cc file in function setConf.
   String _pin; // string representation of the pin, i.e. A0;
   String _location; //location in your house :);
   ConfigurationValue* _confValues; //linkedlist of values to configure each sensor... these are just key value pairs
   DataUploader* _uploader;//object to upload data... can be seen as a connector towards a backend or gateway to store data
  
};

#endif
