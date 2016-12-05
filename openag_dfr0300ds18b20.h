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
 
#define startConvert 0
#define readTemp 1
 
class Dfr0300Ds18b20: public Module{
 public:
 // Public Functions
 Dfr0300Ds18b20(int pin);
 void begin();
 void update();
 float getWT(bool ch);
 bool get_water_temperature(std_msgs::Float32 &msg);
 bool get_water_electrical_conductivity(std_msgs::Float32 &msg);
 // Public Variables
 int _pin;
 const int numReadings = 40;     //the number of sample times
 unsigned int AnalogSampleInterval=25,printInterval=700,tempSampleInterval=850;  //analog sample interval;serial print interval;temperature sample interval
 unsigned int readings[40];      // the readings from the analog input
 byte index = 0;                  // the index of the current reading
 unsigned long AnalogValueTotal = 0;                  // the running total
 unsigned int AnalogAverage = 0,averageVoltage=0;                // the average
 unsigned long AnalogSampleTime,printTime,tempSampleTime;
 float temperature;
 
 private: 
 // Private Variables
 bool _send_water_temperature;
 float _water_temperature;
 bool _send_water_electrical_conductivity;
 float _water_electrical_conductivity; 
 uint32_t _time_of_last_query; 
 const static uint32_t _min_update_interval = 2000;
 };
#endif
