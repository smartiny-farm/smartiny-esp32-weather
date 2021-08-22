#include <config.h>
#define WIFI_AP_NAME        "hackerspace_2.4G_TURBO"
#define WIFI_PASSWORD       "98c6dff101"

void WiFiSetup(){
  Serial.println("Connecting to AP ...");
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void SensorsHandler::ConfigureVector(){
    if(sensors_vector_.empty()==1){
        for(int i=0;i<sensors_quantity_;i++){
            switch (sensors_types_[i])
            {
            case 0:
                sensors_vector_.push_back(new GenericSensor(0,0,0));
                break;
            case 1:
                sensors_vector_.push_back(new SoilMoistureSensor(ports_[i],sensors_types_[i],0));
                break;
            case 2:
                sensors_vector_.push_back(new SoilTemperatureSensor(ports_[i],sensors_types_[i],0));
                break;
            case 3:
                sensors_vector_.push_back(new DHTSensor(ports_[i],sensors_types_[i],0));
                break;
            }
        }
    }
}

void SensorsHandler::getSensorsData(){
    for(int i=0;i<sensors_quantity_;i++){
        sensors_data_[i]=sensors_vector_[i]->getData();
        switch (sensors_types_[i])
        {
        case 1:
            Serial.print("Umidade do solo em porta ");
            Serial.print(ports_[i]);
            Serial.print(": ");
            sensors_data_[i]=map(sensors_data_[i],3700,1700,0,100);
            Serial.println(sensors_data_[i]);
            break;
        case 2:
            Serial.print("Temperatura do solo em porta ");
            Serial.print(ports_[i]);
            Serial.print(": ");
            Serial.println(sensors_data_[i]);
            break;
        case 3:
            Serial.print("Umidade do ar em porta ");
            Serial.print(ports_[i]);
            Serial.print(": ");
            Serial.println(sensors_data_[i]/1000);
            Serial.print("Temperatura do ar em porta ");
            Serial.print(ports_[i]);
            Serial.print(": ");
            Serial.println((float(int((sensors_data_[i]))%1000))/10);
            break;
        default:
            break;
        }

    }
}

void SensorsHandler::SendDataInfluxDB(){
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
    Point sensor("wifi_status_ft");
    if (client.validateConnection()) {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(client.getServerUrl());
    } else {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(client.getLastErrorMessage());
    }
    //Point pointDevice("device_status");
    //sensor.addTag("device", DEVICE);
    //sensor.addTag("SSID", WiFi.SSID());
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
    sensor.clearFields();
    //sensor.addField("rssi", WiFi.RSSI());

    for(int i=0;i<sensors_quantity_;i++){
        if(sensors_types_[i]!=0){
            switch (sensors_types_[i])
            {
            case 1:
                sensor.addTag("Umidade do solo",static_cast<String>(sensors_data_[i]));
                break;
            case 2:
                sensor.addTag("Temperatura do solo",static_cast<String>(sensors_data_[i]));
                break;
            case 3:
                sensor.addTag("Umidade do ar",static_cast<String>(sensors_data_[i]/1000));
                sensor.addTag("Temperatura do ar",static_cast<String>((float(int((sensors_data_[i]))%1000))/10));
                break;
            default:
                break;
            }
        }
    }
    
    client.writePoint(sensor);
    
}

