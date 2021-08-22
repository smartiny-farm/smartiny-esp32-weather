#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <sensors.h>
#include <vector>
#include <string>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define DEVICE "ESP32"
#define INFLUXDB_URL "http://192.168.1.103:7788"
#define INFLUXDB_TOKEN "zNAfTyXoyiHIWR0SXcji6cGmsFSyKbskTJPucEItyihZ5raKwpvaqedkxN_stE5xsKPgrtfPp9OXWOJoulL79w=="
#define INFLUXDB_ORG "TEste"
#define INFLUXDB_BUCKET "Teste"
#define TZ_INFO "GMT-4"

class SensorsHandler{
    private:
    std::vector<GenericSensor*> sensors_vector_;
    int sensors_quantity_;
    int version_;
    bool init_;

    public:
    int ports_[4] = {35,33,2,4};
    int sensors_types_[4] = {1,4,3,2};
    float sensors_data_[4] = {0,0,0,0};
    int sensors_log_[4] = {0,0,0,0};
    SensorsHandler(int quantity){
        this->sensors_quantity_=quantity;
        init_ = true;
    }
    ~SensorsHandler(){
        sensors_vector_.erase(sensors_vector_.begin(), sensors_vector_.end());
        sensors_vector_.shrink_to_fit();
    }
    void setInit(bool init){
        this->init_=init;
    }
    bool getInit(){
        return(init_);
    }
    void ConfigureVector();
    void PortChangeVerify();
    void getSensorsData();
    void SendDataInfluxDB();

};

void WiFiSetup();

#endif