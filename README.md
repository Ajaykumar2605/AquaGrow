# AquaGrow with Blynk

This project is a Green Irrigation System implemented using an ESP8266 microcontroller, Blynk for IoT control, and various sensors. The system monitors soil moisture and temperature, and controls a pump and relay based on the sensor readings.

## Features

- **Soil Moisture Monitoring**: Measures soil moisture percentage using an analog sensor.
- **Temperature Monitoring**: Reads temperature using a Dallas Temperature sensor.
- **Humidity and Temperature Display**: Shows humidity and temperature from a DHT11 sensor on the Blynk app.
- **Pump Control**: Controls a water pump based on soil moisture levels.
- **Relay Control**: Manages a relay through the Blynk app.

## Requirements

- ESP8266 microcontroller
- Soil Moisture Sensor
- Dallas Temperature Sensor (DS18B20)
- DHT11 Temperature and Humidity Sensor
- Blynk App Account
- Required Libraries: `Blynk`, `SimpleTimer`, `DHT`, `OneWire`, `DallasTemperature`
