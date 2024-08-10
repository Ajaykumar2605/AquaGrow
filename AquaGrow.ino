
#define BLYNK_PRINT Serial  
#define BLYNK_TEMPLATE_ID "TMPL3wERcgRRL"
#define BLYNK_TEMPLATE_NAME "MOBILE GREEN IRRIGATION"
#define BLYNK_AUTH_TOKEN "EwAH1PuhYhFgJ4EmX-CqzhjYJ2-SaAZT"
#include <SPI.h>  
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>  
#include <Simpletimer.h>
 #include <DHT.h>    
 #include <OneWire.h>  
 #include <DallasTemperature.h>  
 #define ONE_WIRE_BUS D2  
 OneWire oneWire(ONE_WIRE_BUS);  
 DallasTemperature sensors(&oneWire);  
 char auth[] = "EwAH1PuhYhFgJ4EmX-CqzhjYJ2-SaAZT";   
 char ssid[] = "Username";   
 char pass[] = "9843481584";   
 
//#define SOIL_MOISTURE_PIN A0 // Analog pin for soil moisture sensor
#define PUMP_PIN D3
#define RELAY_PIN_1  D6  
#define VPIN_BUTTON_1  V0 
#define DHTPIN 2    
#define DHTTYPE DHT11   // DHT11 SENSOR CONNECT D4 PIN  
 DHT dht(DHTPIN, DHTTYPE);  
 SimpleTimer timer;  
 
BLYNK_WRITE(V1) { // Virtual pin to control the pump from Blynk app
  int pumpControl = param.asInt();
  digitalWrite(PUMP_PIN, pumpControl);
}
BLYNK_WRITE(VPIN_BUTTON_1) {  
  int relay1State = param.asInt();  
  digitalWrite(RELAY_PIN_1, relay1State); // Change this value to control LED on Arduino
  Serial.println(relay1State); // Send the value over serial  
 }  
 BLYNK_CONNECTED() {  
  // Request the latest state from the server  
  Blynk.syncVirtual(VPIN_BUTTON_1);  
 }  
 void sendSensor()  
 {  
  float h = dht.readHumidity();  
  float t = dht.readTemperature();  
  if (isnan(h) || isnan(t)) {  
   Serial.println("Failed to read from DHT sensor!");  
   return;  
  }  
  Blynk.virtualWrite(V5, h); //V5 is for Humidity  
  Blynk.virtualWrite(V6, t); //V6 is for Temperature  
 }  
 int relay1State = LOW;  
 void setup()  
 {  
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1,relay1State);     
  Serial.begin(9600);  
  Blynk.begin(auth, ssid, pass);  
  dht.begin();  
  timer.setInterval(1000L, sendSensor);  
  Serial.begin(115200);  
  Blynk.begin(auth, ssid, pass);  
   sensors.begin();   
 }  
 int sensor=0;  
 void sendTemps()  
 {  
 sensor=analogRead(A0);  
 sensors.requestTemperatures();  
 float temp = sensors.getTempCByIndex(0);  
 int soilMoisturePercentage = map(sensor, 0, 1023, 100, 0); // Map the analog value to percentage
 Serial.print("Soil Moisture: ");
 Serial.print(soilMoisturePercentage);
 Serial.println("%"); 
 Serial.println(temp);  
 Serial.println(sensor);  
 Blynk.virtualWrite(V1, temp);  
 Blynk.virtualWrite(V2,sensor);  
 delay(1000);
 // You can set your own threshold for activating the pump
  if (sensor < 500) { // Example threshold, adjust as needed
    digitalWrite(PUMP_PIN, HIGH); // Turn on pump
    Blynk.virtualWrite(V1, "Pump is ON"); // Virtual pin to display pump status on Blynk app
  } else {
    digitalWrite(PUMP_PIN, LOW); // Turn off pump
    Blynk.virtualWrite(V1, "Pump is OFF");
  }
 }   
 void loop()  
 {  
  Blynk.run();   
  timer.run();   
  sendTemps();  
 }  
