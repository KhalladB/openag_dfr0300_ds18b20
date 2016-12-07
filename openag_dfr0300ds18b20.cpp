/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
#include "openag_dfr0300ds18b20.h"      
int _wt_pin = 5;
OneWire ds(_wt_pin);
int _ec_pin = 2;
float Temp;
float ECcurrent;

Dfr0300Ds18b20::Dfr0300Ds18b20(int _pin){
 status_level = OK;
 status_msg = "";
}
  
void Dfr0300Ds18b20::begin(){
 for (byte thisReading = 0; thisReading < numReadings; thisReading++)
 readings[thisReading] = 0;
 getWT(startConvert);   //let the DS18B20 start the convert
 AnalogSampleTime=millis();
 printTime=millis();
 tempSampleTime=millis();
 _time_of_last_query = 0;
}

void Dfr0300Ds18b20::update(){
 if (millis() - _time_of_last_query > _min_update_interval){
  if(millis()-AnalogSampleTime>=AnalogSampleInterval){
   AnalogSampleTime=millis(); 
   AnalogValueTotal = AnalogValueTotal - readings[index]; // subtract the last reading
   readings[index] = analogRead(_ec_pin); // read from the sensor
   AnalogValueTotal = AnalogValueTotal + readings[index]; // add the reading to the total
   index = index + 1; // advance to the next position in the array:
   if (index >= numReadings){    // advance to the next position in the array
   index = 0;     // ...wrap around to the beginning:
   }
   AnalogAverage = AnalogValueTotal / numReadings; // calculate the average
  }
  /*
   Every once in a while,MCU read the temperature from the DS18B20 and then let the DS18B20 start the convert.
   Attention:The interval between start the convert and read the temperature should be greater than 750 millisecond,or the temperature is not accurate!
  */
  if(millis()-tempSampleTime>=tempSampleInterval){
   tempSampleTime=millis();
   temperature = getWT(readTemp);  // read the current temperature from the  DS18B20
   getWT(startConvert);                   //after the reading,start the convert for next reading
  }
   /*
   Every once in a while,print the information on the serial monitor.
  */
  //if(millis()-printTime>=printInterval){
   //printTime=millis();
   averageVoltage=AnalogAverage*(float)5000/1024;
   float TempCoefficient=1.0+0.0185*(temperature-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.0185*(fTP-25.0));
   float CoefficientVolatge=(float)averageVoltage/TempCoefficient;  
   
   if(CoefficientVolatge<150)//Serial.println("No solution!");   //25^C 1413us/cm<-->about 216mv  if the voltage(compensate)<150,that is <1ms/cm,out of the range
   else if(CoefficientVolatge>3300)//Serial.println("Out of the range!");  //>20ms/cm,out of the range
   else{ 
    if(CoefficientVolatge<=448)ECcurrent=6.84*CoefficientVolatge-64.32;   //1ms/cm<EC<=3ms/cm
    else if(CoefficientVolatge<=1457)ECcurrent=6.98*CoefficientVolatge-127;  //3ms/cm<EC<=10ms/cm
    else ECcurrent=5.3*CoefficientVolatge+2278;                           //10ms/cm<EC<20ms/cm
    ECcurrent/=1000;    //convert us/cm to ms/cm
    //Serial.print(ECcurrent,2);  //two decimal
    //Serial.println("ms/cm");
   //}
   _time_of_last_query = millis();
   _send_water_temperature = true;
   _send_water_electrical_conductivity = true;
   _water_temperature = Temp;
   _water_electrical_conductivity = ECcurrent;
  }
 }
}

bool Dfr0300Ds18b20::get_water_electrical_conductivity(std_msgs::Float32 &msg){
 msg.data = _water_electrical_conductivity;
 bool res = _send_water_electrical_conductivity;
 _send_water_electrical_conductivity = false;
 return res;
}
 
bool Dfr0300Ds18b20::get_water_temperature(std_msgs::Float32 &msg){
 msg.data = _water_temperature;
 bool res = _send_water_temperature;
 _send_water_temperature = false;
 return res;
}

float Dfr0300Ds18b20::getWT(bool ch){
 //returns the temperature from one DS18B20 in DEG Celsius
 static byte data[12];
 static byte addr[8];
 static float TemperatureSum;
 if(!ch){
  if ( !ds.search(addr)) {
   //Serial.println("no more sensors on chain, reset search!");
   ds.reset_search();
   return 0;
  }      
  if ( OneWire::crc8( addr, 7) != addr[7]) {
  //Serial.println("CRC is not valid!");
   return 0;
  }
  if ( addr[0] != 0x10 && addr[0] != 0x28) {
   //Serial.print("Device is not recognized!");
   return 0;
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end
 }
 else{
  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad            
  for (int i = 0; i < 9; i++){ // we need 9 bytes
  data[i] = ds.read();
  }
  ds.reset_search();
  byte MSB = data[1];
  byte LSB = data[0];
  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  TemperatureSum = tempRead / 16;
  Temp = TemperatureSum;
 }
 return (Temp);
}
