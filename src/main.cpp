#include <config.h>
#include <sensors.h>

void setup() {
  Serial.begin(115200);
  WiFiSetup();
}

void loop() {
  SensorsHandler sensors(4);
  while(sensors.getInit()){
    sensors.ConfigureVector();
    sensors.getSensorsData();
    sensors.SendDataInfluxDB();
  }
}