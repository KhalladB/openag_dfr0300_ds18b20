# openag_dfr0300_ds18b20
- This is a code for both Water Temperature Sensor (ds18b20) and Water Electric Conductivity (dfr0300).
- In dfr0300 in order to get the value of electric conductivity, temperature of water is needed.
- Connect dfr0300 to Analog Pin 2. Connect ds18b20 to Digital Pin 5.

    {
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
    }
