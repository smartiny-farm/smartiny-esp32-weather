#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
//#include <esp_wifi.h>
//#include <esp_wpa2.h>
#include <sensors.h>
#include <vector>
#include <string>
#include <InfluxDbClient.h>

#define INFLUXDB_URL "influxdb-url"
// InfluxDB 2 server or cloud API authentication token (Use: InfluxDB UI -> Load Data -> Tokens -> <select token>)
#define INFLUXDB_TOKEN "token"
// InfluxDB 2 organization name or id (Use: InfluxDB UI -> Settings -> Profile -> <name under tile> )
#define INFLUXDB_ORG "org"
// InfluxDB 2 bucket name (Use: InfluxDB UI -> Load Data -> Buckets)
#define INFLUXDB_BUCKET "bucket"



class SensorsHandler{
    private:
    std::vector<GenericSensor*> sensors_vector_;
    int sensors_quantity_;
    int version_;

    public:
    int ports_[4] = {32,26,2,4};
    int sensors_types_[4] = {1,2,3,3};
    float sensors_data_[4] = {0,0,0,0};
    int sensors_log_[4] = {0,0,0,0};
    SensorsHandler(int quantity){
        this->sensors_quantity_=quantity;
    }
    ~SensorsHandler(){
        sensors_vector_.erase(sensors_vector_.begin(), sensors_vector_.end());
        sensors_vector_.shrink_to_fit();
    }
    void ConfigureVector();
    void PortChangeVerify();
    void getSensorsData();
    void SendDataInfluxDB();

};

void WiFiSetup();

#endif