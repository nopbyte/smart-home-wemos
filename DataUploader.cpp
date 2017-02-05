/*
  DataUploader.cpp.

*/
#include "Arduino.h"
#include "DataUploader.h"

DataUploader::DataUploader(WifiConnection* wifi, char *host, int port,  ConfigurationValue* additionalConfs){
  _wifi = wifi;
  _host = host;
  _port = port;
  _database = "unconfigured";
  _username = "unconfigured";
  _password = "unconfigured";
  _additionalConfs = additionalConfs;
  parseConfs();
}
void DataUploader::setDataPort(int port){
  _port = port;
}
    
void DataUploader::parseConfs(){
    ConfigurationValue* tmp = _additionalConfs;
    while(tmp!=NULL){
      if(tmp->getKey()=="username"){
        _username = tmp->getValue();
      }
      else if(tmp->getKey()=="password"){
        _password = tmp->getValue();
      }
      else if(tmp->getKey()=="database"){
        _database = tmp->getValue();
      }
      tmp = tmp->next();
    }    
}

void DataUploader::uploadDataString(String measurementName, String location, String value){
  
  String url = "/write?db="+_database+"&u="+_username+"&p="+_password;
  String data = measurementName+",room="+location+" value="+value+"\n";
  //data = data + "u=" + _username+"\n";
  //data = data + "p=" +_password;
  //data = data + "humidity,room=kitchen value="+String(h);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  String result =  _wifi->exchangeHttp(_host, _port, "POST",url, data);  
  Serial.println("result from data upload");
  Serial.println(result);
}

void DataUploader::uploadDataFloat(String measurementName, String location, float value){
  return uploadDataString(measurementName, location, String(value));
}

void DataUploader::uploadDataInt(String measurementName, String location, int value){
  return uploadDataString(measurementName, location, String(value));
}

