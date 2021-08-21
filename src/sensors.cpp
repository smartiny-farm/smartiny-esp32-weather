#include <sensors.h>

float SoilTemperatureSensor::getData(){
    float temperature;
    dallas_handler_->requestTemperatures();
    temperature=dallas_handler_->getTempCByIndex(0);
    setData(temperature);
    return(temperature);
}

float SoilMoistureSensor::getData(){
    float moisture;
    moisture = analogRead(getPin());
    setData(moisture);
    return(moisture);
}

float DHTSensor::getData(){
    float t=dht_handler_->readTemperature();
    float h=dht_handler_->readHumidity();
    if (isnan(t) || isnan(h)) {
        Serial.println("Failed to read from DHT sensor!");
        h=1;
        t=1;
    }
    if(h<=0){
        h=1;
    }
    if(h>=100){
        h=99;
    }
    if(t<=0){
        t=1;
    }
    if(t>=100){
        t=99;
    }
    setData(h*1000+t*10);
    return(h*1000+t*10);
}