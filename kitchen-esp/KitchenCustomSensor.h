#include "esphome.h"
#include "LCD1602Display.h"

#define BUTTON 14 //D5 = GPIO14

class KitchenCustomSensor : public Component, public CustomMQTTDevice {
public:

    KitchenCustomSensor()         
    {
        ds18b20TempBalconyStreet = new Sensor();
    }

    void setup() override { 
        Display::LCD1602.Init();
        pinMode(BUTTON, INPUT);
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
        int buttonState = digitalRead(BUTTON); 
        if (buttonState != _oldButtonState) {
            _oldButtonState = buttonState;
            if (buttonState == HIGH)
            {
                Display::LCD1602.OnTap();
            }
        }        
        float vals[3];
        vals[0] = _tempBalcony;
        vals[1] = _tempStreet;
        vals[2] = _humidityBalcony;
        Display::LCD1602.UpdateValues(vals);
        Display::LCD1602.ShowStoragedData();
    }

public:
    Sensor* ds18b20TempBalconyStreet;

private:
    int _oldButtonState = 0;
        
    float _tempBalcony = 0.f;
    float _tempStreet = 0.f;
    float _humidityBalcony = 0.f;

    const String TEMP_TAG = String("temperature");
    const String PRESSURE_TAG = String("pressure");
    const String HUMIDITY_TAG = String("humidity"); 
    const String TEMP_STREET_TAG = String("temperature.street");
};
