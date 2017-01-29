#include <ESP8266WiFi.h>
#include "configuration.h"
#include "SensorConfiguration.h"
#include "DHT11SensorConfiguration.h"
#include "ConfigurationValue.h"
#include "DataUploader.h"
#include "WifiConnection.h"

/* These variables come from the definitions in the configuration.h and are required to 
  reach the confServer that will serve the actual configuration information, i.e. sensors and locations
*/
const char* ssid     = SSID;
const char* password = WIFIPASS;
bool configured = false;
String confSeparator = ":"; 
/* 
  These variables are set once the configuration confServer has replied
*/

/* Configuration loading... update the configuration.h file*/
char* confServer = SERVER;
int confServerPort = PORT;
char * dataServer = SERVER;
int dataPort = 0;
WifiConnection* wifi = NULL;
DataUploader *uploader = NULL;

/* To be configured after fetchiing configuration info*/
int myDelay = 1000;//

SensorConfiguration* headConf = NULL;
/* 
  PINS used for the sensors
*/

//DO NOT USE D4... this is the LED!
//DO NOT USE D4... this is the LED!
//DO NOT USE D4... this is the LED!




void setup() {
  
  //use built in led for information
  pinMode(BUILTIN_LED, OUTPUT);  // initialize onboard LED as output
  digitalWrite(BUILTIN_LED, 1);   // turn off LED with voltage LOW
  Serial.begin(9600);
  String id  = String(ESP.getChipId(),HEX);
  String res;
  Serial.print("device id" + id);
  while(!configured){
    Serial.println("not configured");
    errorBlink(200);
    delay(2000);
    wifi = new WifiConnection(ssid, password);
    res = wifi->exchangeHttp(confServer, confServerPort, "GET","/conf/?id="+id, "");  
    delay(10);
    configured =  setConf(res);
    ConfigurationValue* additionalUploaderConfs = NULL;
    //set up data uploader
    //set username and password for data upload
    ConfigurationValue* username = new ConfigurationValue("username",DATAUSERNAME);    
    ConfigurationValue* password = new ConfigurationValue("password",DATAPASSWORD);
    additionalUploaderConfs = appendToConfigurationValues( additionalUploaderConfs, username);
    additionalUploaderConfs = appendToConfigurationValues( additionalUploaderConfs, password);    
    uploader = new DataUploader(wifi, dataServer, dataPort, additionalUploaderConfs );
  }
}


void loop() {
  SensorConfiguration* tmp = headConf;
  while(tmp !=NULL){
     tmp->execute();
     delay(myDelay);
     tmp=tmp->next();
  
  }  
}


/* 
    Functions! 
*/
void errorBlink(int d){
  digitalWrite(BUILTIN_LED, 0);  // turn on LED with voltage HIGH
  delay(d);                       
  digitalWrite(BUILTIN_LED, 1);   // turn off LED with voltage LOW
  delay(d);                       
}


/* Linking the SensorConfigurations together*/

void appendToSensorConfs(SensorConfiguration* current){
  if(headConf == NULL){
    headConf = current;
  }
  if(headConf == current){
    return;
  }
  else{
    SensorConfiguration* tmp = headConf;
    while(tmp->next()!=NULL){
      tmp = tmp->next();
     }
     tmp->setSuccessor(current);
  }
}

/* Linking the ConfigurationValues together */

ConfigurationValue* appendToConfigurationValues(ConfigurationValue* head, ConfigurationValue* current){
  if(head == current){
    return head;
  }
  if(head == NULL){
    return current;
  }
  else{
    ConfigurationValue* tmp = head;
    while(tmp->next()!=NULL){
      tmp = tmp->next();
     }
     tmp->setSuccessor(current);
     return head;
  }
}


/* 
  Sets the configuration for the connected sensors
  res includes the http headers and the body... etc. a.k.a what goes through the TCP socke :)
  This function essentially parses the HTTP response and creates the relevant sensor configuration objects.
*/
bool setConf(String res){
  //Serial.println("Received this from configuration server \n"+res);    
  if(res == "" || res.indexOf("HTTP/1.1 404 ")>=0){
    return false;
  }
  else{
    int nexti = 0;
    String line;
    String sensorType = "";
    boolean body = false;
    ConfigurationValue* conf = NULL;
    SensorConfiguration* current = NULL;
    //nexti = res.indexOf("\n");
    do{
      nexti = res.indexOf("\n");
      line = res.substring(0,nexti);
      res.remove(0,nexti+1);
      if(nexti==0){
         body = true;
         continue;
      }
      if(body){//marks body and end of message
        
        if(line.startsWith("delay")){
          line.remove(0,line.indexOf(":")+1);
          myDelay = line.toInt(); 
          Serial.println("delay "+String(myDelay));
        }
        else if(line.startsWith("host")){
          //TODO, for this we need to convert things to char * and try the library... later
        }
        else if(line.startsWith("port")){
          line.remove(0,line.indexOf(":")+1);
          dataPort = line.toInt(); 
          Serial.println("data port "+String(line.toInt()) );
        }
        else{
           if(line == ""){
                  //Serial.println("flush configuration");
                  current->setConfigurationValues(conf);
                  appendToSensorConfs(current);
                  break; //this prevents the second \n of HTTP to enter again
           }
           //seems to be part of a config*/
           if(line.startsWith(" ")){
             String key = line.substring(0,line.indexOf(":"));
             line.remove(0,line.indexOf(":")+1);
             String value = line;
             ConfigurationValue* n = new ConfigurationValue(key,value);
             conf = appendToConfigurationValues(conf,n);

           }else{//top level, i.e. a new sensor
                if(current != NULL){
                  //flush the conf 
                  //Serial.println("flush configuration");
                  current->setConfigurationValues(conf);
                  appendToSensorConfs(current);
                }
                conf = NULL;
                sensorType = line.substring(0,line.indexOf(":"));
                current = new DHT11SensorConfiguration(uploader, sensorType);
                
           }
        }
      }
      else{
        continue;
      }
      

    }while(0 <= nexti);
    return true; 
  }
}


