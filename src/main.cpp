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
  /*InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
  Point sensor("wifi_status_tw");
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  //Point pointDevice("device_status");
  sensor.addTag("device", DEVICE);
  sensor.addTag("SSID", WiFi.SSID());
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
  sensor.clearFields();
  sensor.addField("rssi", WiFi.RSSI());
  client.writePoint(sensor);*/
  while(1){
    sensors.ConfigureVector();
    sensors.getSensorsData();
    sensors.SendDataInfluxDB();
  }
}