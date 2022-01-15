#include "esphome.h"
#include <printf.h>

class KitchenCustomSensor : public Component, public CustomMQTTDevice {
public:

    KitchenCustomSensor()         
    {
        ds18b20TempBalconyStreet = new Sensor();
    }

    void setup() override { 
        subscribe("balcony-esp/sensor/balcony_temperature/state", &KitchenCustomSensor::onBalconyTempMsg);        
    } 

    void onBalconyTempMsg(const std::string &payload) {
        ESP_LOGD("FROM BALCONY TO KITCHEN ", "SMTHG");  
        ds18b20TempBalconyStreet->publish_state(777);
    }

    void onBalconyTempJsonMsg(JsonObject &root) {
        if (!root.containsKey("key"))
            return;
        int value = root["key"];
    }

public:
    Sensor* aht10Temp;
    Sensor* aht10Humidity;
    Sensor* ds18b20TempBalconyStreet;

private:


    Adafruit_AHT10 _aht10Main;
    Adafruit_Sensor* _aht_humidity;
    Adafruit_Sensor* _aht_temp;
    bool _aht10Inited = false;
    
    String _dataBuf;
    float _temp;
    float _tempStreet;
    float _humidity;
    int _ahtTimer;
    const int RADIO_DELAY = 10;

    const int AHT_INIT_DELAY = 200;
    const int AHT_DELAY = 5000;
    const int GLOBAL_DELAY = 20;
    const String TEMP_TAG = String("temperature");
    const String PRESSURE_TAG = String("pressure");
    const String HUMIDITY_TAG = String("humidity"); 
    const String TEMP_STREET_TAG = String("temperature.street");
};
