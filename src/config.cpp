#include <config.h>

#define WIFI_AP_NAME        "hackerspace"
#define WIFI_PASSWORD       "98c6dff101"

void WiFiSetup(){
  Serial.println("Connecting to AP ...");
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void SensorsHandler::ConfigureVector(){
    if(sensors_vector_.empty()){
        for(int i=0;i<sensors_quantity_;i++){
            switch (sensors_types_[i])
            {
            case 0:
                sensors_vector_.push_back(new GenericSensor(0,0,0));
                break;
            case 1:
                sensors_vector_.push_back(new SoilMoistureSensor(ports_[i],sensors_types_[i],0));
                break;
            case 2:
                sensors_vector_.push_back(new SoilTemperatureSensor(ports_[i],sensors_types_[i],0));
                break;
            case 3:
                sensors_vector_.push_back(new DHTSensor(ports_[i],sensors_types_[i],0));
                break;
            default:
                break;
            }
        }
    }
}

