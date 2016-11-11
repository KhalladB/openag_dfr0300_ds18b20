 #ifndef OPENAG_DRF0300_DS18B20_H
 #define OPENAG_DFR0300_DS18B20_H


 #if ARDUINO >= 100
 #include "Arduino.h"
 #else
 #include "WProgram.h"
 #endif

 #include <OneWire.h>
 #include <openag_module.h>
 #include <std_msgs/Float32.h>
 #include <DallasTemperature.h>
 
 
 class Dfr0300_Ds18b20: public Module{
  public:
    Dfr0300(int _pin);
    void begin();
    void update();
    bool get_water_electrical_conductivity(std_msgs::Float32 &msg);
    bool get_water_temperature(std_msgs::Float32 &msg);
    
  private:
    float getWEC();
    float _water_electrical_conductivity;
    bool _send_water_electrical_conductivity;
    float _ec_calibration_coefficient;
    float _ec_calibration_offset;
    
    float getWT();
    OneWire _oneWire;
    DeviceAddress _address;
    DallasTemperature _sensors;
    bool _send_water_temperature;
    float _water_temperature;
    bool _waiting_for_conversion;
    
    const static uint32_t _min_update_interval = 2500;
