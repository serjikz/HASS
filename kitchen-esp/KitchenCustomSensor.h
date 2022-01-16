#include "esphome.h"
#include <printf.h>
#include "LCD1602Display.h"

class KitchenCustomSensor : public Component, public CustomMQTTDevice {
public:

    KitchenCustomSensor()         
    {
        ds18b20TempBalconyStreet = new Sensor();
    }

    void setup() override { 
        Display::LCD1602.Init();
        subscribe("balcony-esp/sensor/street_temperature/state", &KitchenCustomSensor::onBalconyStreetMsg);     
        subscribe("balcony-esp/sensor/balcony_temperature/state", &KitchenCustomSensor::onBalconyTempMsg);     
        subscribe("balcony-esp/sensor/balcony_humidity/state", &KitchenCustomSensor::onBalconyHuidityMsg);               
    } 

    void onBalconyStreetMsg(const std::string &payload) { 
        _tempStreet = ::atof(payload.c_str());
        ds18b20TempBalconyStreet->publish_state(_tempStreet);
    }

    void onBalconyTempMsg(const std::string &payload) { 
        _tempBalcony = ::atof(payload.c_str());
    }

    void onBalconyHuidityMsg(const std::string &payload) { 
        _humidityBalcony = ::atof(payload.c_str());
    }

    void onBalconyTempJsonMsg(JsonObject &root) {
        if (!root.containsKey("key"))
            return;
        int value = root["key"];
    }

    void loop() override {
        Display::LCD1602.Update();
        float vals[3];
        vals[0] = _tempBalcony;
        vals[1] = _tempStreet;
        vals[2] = _humidityBalcony;
        Display::LCD1602.UpdateValues(vals);
        Display::LCD1602.ShowStoragedData();
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
    float _tempBalcony = 0.f;
    float _tempStreet = 0.f;
    float _humidityBalcony = 0.f;
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
