# openag_dfr0300ds18b20
- This is a code for both Water Temperature Sensor (ds18b20) and Water Electric Conductivity (dfr0300).
- In dfr0300 in order to get the value of electric conductivity, temperature of water is needed.
- Connect dfr0300 to Analog Pin 2. Connect ds18b20 to Digital Pin 5.
- On ChouchDB Firmware Module Type
 "{
   "_id": "dfr0300ds18b20",
   "_rev": "5-a011b347fd414a37687de70014387580",
   "description": "OpenAg driver for the DS18B20 temperature sensor & DFR0300 electric conductivity",
   "repository": {
       "url": "https://github.com/KhalladB/openag_dfr0300ds18b20.git",
       "type": "git"
   },
   "class_name": "Dfr0300Ds18b20",
   "outputs": {
       "water_temperature": {
           "type": "std_msgs/Float32"
       },
       "water_electrical_conductivity": {
           "type": "std_msgs/Float32"
       }
   },
   "header_file": "openag_dfr0300ds18b20.h",
   "arguments": [
       {
           "name": "pin",
           "type": "int",
           "default": 2
       }
   ],
   "dependencies": [
       {
           "url": "https://github.com/OpenAgInitiative/openag_firmware_module.git",
           "type": "git"
       }
   ]
}"
- On ChouchDB Firmware Module
    "{
   "_id": "dfr0300ds18b20_1",
   "environment": "environment_1",
   "type": "dfr0300ds18b20",
   "outputs": {
       "water_temperature": {
           "variable": "water_temperature"
       },
       "water_electrical_conductivity": {
           "variable": "water_electrical_conductivity"
       }
    }
  }"
