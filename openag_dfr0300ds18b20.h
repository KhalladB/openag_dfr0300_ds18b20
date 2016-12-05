 #ifndef OPENAG_DRF0300DS18B20_H
 #define OPENAG_DFR0300DS18B20_H


 #if ARDUINO >= 100
 #include "Arduino.h"
 #else
 #include "WProgram.h"
 #endif

 #include <OneWire.h>
 #include <openag_module.h>
 #include <std_msgs/Float32.h>
 //#include <DallasTemperature.h>
 
 #define startConvert 0
 #define readTemp 1
 
 class Dfr0300Ds18b20: public Module{
  public:
    Dfr0300Ds18b20(int pin);
    void begin();
    void update();
    bool get_water_temperature(std_msgs::Float32 &msg);
    bool get_water_electrical_conductivity(std_msgs::Float32 &msg);
    
    int _pin;
    /*Dfr0300Ds18b20(int ec_pin);
    void begin();
    void update();
    bool get_water_electrical_conductivity(std_msgs::Float32 &msg);
    bool get_water_temperature(std_msgs::Float32 &msg);
    
    int _pin;
    int _wt_pin;
    //_wt_pin = 2;
    //OneWire ds(_wt_pin);
    int _ec_pin;*/
    const int numReadings = 40;     //the number of sample times
    //byte ECsensorPin = A1;  //EC Meter analog output,pin on analog 1
    //byte DS18B20_Pin = 2; //DS18B20 signal, pin on digital 2
    unsigned int AnalogSampleInterval=25,printInterval=700,tempSampleInterval=850;  //analog sample interval;serial print interval;temperature sample interval
    unsigned int readings[40];      // the readings from the analog input
    byte index = 0;                  // the index of the current reading
    unsigned long AnalogValueTotal = 0;                  // the running total
    unsigned int AnalogAverage = 0,averageVoltage=0;                // the average
    unsigned long AnalogSampleTime,printTime,tempSampleTime;
    float temperature;
    float temp;
    float ECcurrent; 
    
    float getWT(bool ch);
    bool _send_water_temperature;
    float _water_temperature;
    bool _send_water_electrical_conductivity;
    float _water_electrical_conductivity; 
    uint32_t _time_of_last_query; 
    const static uint32_t _min_update_interval = 2000;
  private: 
 
  //unsigned int readings[numReadings];      // the readings from the analog input
    /*unsigned long AnalogSampleTime,printTime,tempSampleTime;
  
    float getWEC();
    float _water_electrical_conductivity;
    bool _send_water_electrical_conductivity;
    float _ec_calibration_coefficient;
    float _ec_calibration_offset;
    float temp;
  
    float getWT(bool ch);
    //OneWire _oneWire;
    //DeviceAddress _address;
    //DallasTemperature _sensors;
    bool _send_water_temperature;
    float _water_temperature;
    bool _waiting_for_conversion;
      
    uint32_t _time_of_last_query; 
    const static uint32_t _min_update_interval = 2000;*/
  
 };

#endif
