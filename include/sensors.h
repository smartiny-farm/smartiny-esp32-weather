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

    protected:
    void setPin(const int);
    void setType(const int);
    void setData(const float);
    int getPin() const;
    int getType() const;

    public:
    GenericSensor();
    GenericSensor(int pin, int type, float data);
    GenericSensor(const GenericSensor &);
    virtual ~GenericSensor();
    virtual float getData();

};

class SoilTemperatureSensor : public GenericSensor{
    
    private:
    OneWire *onewire_pointer_ = NULL;
    DallasTemperature *dallas_handler_ = NULL;
    
    void setOneWirePointer(const int);
    void setDallasHandler();
    void DallasBegin();
    void deleteHandler();
    void deleteOneWirePointer();

    public:
    SoilTemperatureSensor(int pin, int type, float data);
    ~SoilTemperatureSensor();
    virtual float getData();

};

class SoilMoistureSensor : public GenericSensor{
    public:
    SoilMoistureSensor(int pin, int type, float data);
    ~SoilMoistureSensor();
    virtual float getData();

};

class DHTSensor : public GenericSensor{
    private:
    DHT *dht_handler_ = NULL;
    float temperature_;
    float humidity_;

    void setDHTHandler(int);
    void DHTBegin();
    void deleteDHTHandler();

    public:
    DHTSensor(int, int, float);
    ~DHTSensor();
    virtual float getData();

};

class LightSensor : public GenericSensor{
    public:
    LightSensor(int pin, int type, float data);
    ~LightSensor();
    virtual float getData();
};

#endif