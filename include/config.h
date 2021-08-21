#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <sensors.h>
#include <vector>

class SensorsHandler{
    private:
    std::vector<GenericSensor*> sensors_vector_;
    int sensors_quantity_;

    public:
    int ports_[4] = {32,26,2,4};
    int sensors_types_[4] = {0,0,0,0};
    int sensors_data_[4] = {0,0,0,0};
    float sensors_log_[4] = {0,0,0,0};
    SensorsHandler(int quantity){
        this->sensors_quantity_=quantity;
    }
    ~SensorsHandler(){
        sensors_vector_.erase(sensors_vector_.begin(), sensors_vector_.end());
        sensors_vector_.shrink_to_fit();
    }
    void ConfigureVector();
    void PortChangeVerify();

};

void WiFiSetup();

#endif