#include "esphome.h"
#include <ArduinoJson.h>
#include "NRF24Receiver.h"
#include <printf.h>

class KitchenCustomSensor : public PollingComponent, public Sensor {
public:
   
    KitchenCustomSensor(float val) 
        : PollingComponent(GLOBAL_DELAY) 
    {
        ds18b20TempBalconyStreet = new Sensor();
       _aht10Inited = false;
       _tempStreet = val;
    }

    void setup() override {
       
    }
  
    void update() override {
        ds18b20TempBalconyStreet->publish_state(_tempStreet);
        delay(GLOBAL_DELAY);
    }
 
public:
    Sensor* aht10Temp;
    Sensor* aht10Humidity;
    Sensor* ds18b20TempBalconyStreet;

private:

    StaticJsonDocument<200> _doc;
    Adafruit_AHT10 _aht10Main;
    Adafruit_Sensor* _aht_humidity;
    Adafruit_Sensor* _aht_temp;
    bool _aht10Inited = false;
    
    Radio::BalconyNRFDataParser _nrfBalconyDataParser;

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
