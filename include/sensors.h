#ifndef SENSORS_H
#define SENSORS_H

#include <iostream>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

class GenericSensor{
    
    private:
    int pin_, type_;
    mutable float data_;

    public:
    GenericSensor(){
        this->pin_ = 0;
        this->type_ = 0;
        this->data_ = 0;
    }
    GenericSensor(int pin, int type, float data){
        Serial.println("Creating new Generic Sensor");
        this->pin_ = pin;
        this->type_ = type;
        this->data_ = data;
    }
    GenericSensor(const GenericSensor & generic_sensor){
        this->pin_ = generic_sensor.pin_;
        this->type_ = generic_sensor.type_;
        this->data_ = generic_sensor.data_;
    }
    virtual ~GenericSensor(){
    }

    void setPin(const int pin){
        this->pin_ = pin;
    }
    void setType(const int type){
        this->type_ = type;
    }
    void setData(const float data){
        this->data_ = data;
    }
    int getPin() const{
        return(pin_);
    }
    int getType() const{
        return(type_);
    }
    virtual float getData(){
        return(data_);
    }

};

class SoilTemperatureSensor : public GenericSensor{
    
    private:
    OneWire *onewire_pointer_ = NULL;
    DallasTemperature *dallas_handler_ = NULL;
    
    void setOneWirePointer(const int pin){
        OneWire *wire = new OneWire(pin);
        onewire_pointer_ = wire;
    }
    void setDallasHandler(){
        DallasTemperature *sensor = new DallasTemperature(onewire_pointer_);
        dallas_handler_ = sensor;
    }
    void DallasBegin(){
        dallas_handler_->begin();
    }
    void deleteHandler(){
        delete dallas_handler_;
    }
    void deleteOneWirePointer(){
        delete onewire_pointer_;
    }

    public:
    SoilTemperatureSensor(int pin, int type, float data) : GenericSensor(pin,type,data){
        Serial.println("Creating new Soil Temperature Sensor");
        setOneWirePointer(pin);
        setDallasHandler();
        DallasBegin();
    }
    ~SoilTemperatureSensor(){
        deleteOneWirePointer();
        deleteHandler();
    }
    virtual float getData();

};

class SoilMoistureSensor : public GenericSensor{
    public:
    SoilMoistureSensor(int pin, int type, float data) : GenericSensor(pin,type,data){
        Serial.println("Creating new Soil Moisture Sensor");
    }
    ~SoilMoistureSensor(){
    }
    virtual float getData();

};

class DHTSensor : public GenericSensor{
    private:
    DHT *dht_handler_ = NULL;
    float temperature_;
    float humidity_;

    void setDHTHandler(int pin){
        DHT *dht_ = new DHT(pin,DHT11);
        dht_handler_=dht_;
    }
    void DHTBegin(){
        dht_handler_->begin();
    }
    void deleteDHTHandler(){
        delete dht_handler_;
    }
    float getTemperatureAndHumidity();

    public:
    DHTSensor(int pin, int type, float data) : GenericSensor(pin,type,data){
        Serial.println("Creating new DHT Sensor");
        setDHTHandler(pin);
        DHTBegin();
    }
    ~DHTSensor(){
        deleteDHTHandler();
    }
    virtual float getData();

};

class LightSensor : public GenericSensor{
    public:
    LightSensor(int pin, int type, float data) : GenericSensor(pin,type,data){
        Serial.println("Creating new Light Sensor");
    }
    ~LightSensor(){
    }
    virtual float getData();
};

#endif