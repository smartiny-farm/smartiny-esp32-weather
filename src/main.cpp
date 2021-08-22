#include <config.h>
#include <sensors.h>
//using namespace std;

void setup() {
  Serial.begin(115200);
  WiFiSetup();
  //InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
}

void loop() {
  SensorsHandler sensors(4);
  while(1){
    sensors.ConfigureVector();
    sensors.getSensorsData();
    sensors.SendDataInfluxDB();
  }
}