#include <sensors.h>

GenericSensor::GenericSensor(){
        this->pin_ = 0;
        this->type_ = 0;
        this->data_ = 0;
}

GenericSensor::GenericSensor(int pin, int type, float data){
    Serial.println("Creating new Generic Sensor");
    this->pin_ = pin;
    this->type_ = type;
    this->data_ = data;
}

GenericSensor::GenericSensor(const GenericSensor & generic_sensor){
    this->pin_ = generic_sensor.pin_;
    this->type_ = generic_sensor.type_;
    this->data_ = generic_sensor.data_;
}

GenericSensor::~GenericSensor(){
}

void GenericSensor::setPin(const int pin){
    this->pin_ = pin;
}

void GenericSensor::setType(const int type){
    this->type_ = type;
}

void GenericSensor::setData(const float data){
    this->data_ = data;
}

int GenericSensor::getPin() const{
    return(pin_);
}

int GenericSensor::getType() const{
    return(type_);
}

///Virtual getData call
float GenericSensor::getData(){
    return(data_);
}


SoilTemperatureSensor::SoilTemperatureSensor(int pin, int type, float data) : GenericSensor(pin,type,data){
    Serial.println("Creating new Soil Temperature Sensor");
    setOneWirePointer(pin);
    setDallasHandler();
    DallasBegin();
}

SoilTemperatureSensor::~SoilTemperatureSensor(){
    deleteOneWirePointer();
    deleteHandler();
}

void SoilTemperatureSensor::setOneWirePointer(const int pin){
    OneWire *wire = new OneWire(pin);
    onewire_pointer_ = wire;
}

void SoilTemperatureSensor::setDallasHandler(){
    DallasTemperature *sensor = new DallasTemperature(onewire_pointer_);
    dallas_handler_ = sensor;
}

void SoilTemperatureSensor::DallasBegin(){
    dallas_handler_->begin();
}

void SoilTemperatureSensor::deleteHandler(){
    delete dallas_handler_;
}

void SoilTemperatureSensor::deleteOneWirePointer(){
    delete onewire_pointer_;
}

/**
 * Get Temperature Data via getTempCByIndex call
 * @return temperature in celsius
 */
float SoilTemperatureSensor::getData(){
    float temperature;
    dallas_handler_->requestTemperatures();
    temperature=dallas_handler_->getTempCByIndex(0);
    setData(temperature);
    return(temperature);
}


SoilMoistureSensor::SoilMoistureSensor(int pin, int type, float data) : GenericSensor(pin,type,data){
    Serial.println("Creating new Soil Moisture Sensor");
}

SoilMoistureSensor::~SoilMoistureSensor(){
}

/**
 * Get moisture via analogRead
 * @return value between 0 and 5000, higher is less humidity
 */
float SoilMoistureSensor::getData(){
    float moisture;
    moisture = analogRead(getPin());
    setData(moisture);
    return(moisture);
}


DHTSensor::DHTSensor(int pin, int type, float data) : GenericSensor(pin,type,data){
    Serial.println("Creating new DHT Sensor");
    setDHTHandler(pin);
    DHTBegin();
}

DHTSensor::~DHTSensor(){
    deleteDHTHandler();
}

void DHTSensor::setDHTHandler(int pin){
    DHT *dht_ = new DHT(pin,DHT11);
    dht_handler_=dht_;
}

void DHTSensor::DHTBegin(){
    dht_handler_->begin();
}

void DHTSensor::deleteDHTHandler(){
    delete dht_handler_;
}

/**
 * Get air humidity and temperature via DHT class temperature and humidity handle caller
 * @return single variable consist of temperature <data%1000/10> and humidity <data/1000>
 */
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


LightSensor::LightSensor(int pin, int type, float data) : GenericSensor(pin,type,data){
    Serial.println("Creating new Light Sensor");
}

LightSensor::~LightSensor(){
}

/**
 * Get light intensity via analogRead
 * @return value between 0 and 5000, higher is higher intensity
 */
float LightSensor::getData(){
    float light;
    light = analogRead(getPin());
    setData(light);
    return(light);
}
