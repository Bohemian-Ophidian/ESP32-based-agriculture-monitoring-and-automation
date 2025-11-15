#include "sensor.h"
#include <Arduino.h>
#include <DHT.h>


#define DHTPIN 12
#define DHTTYPE DHT22
#define SOIL_PIN 35


DHT dht(DHTPIN, DHTTYPE);

float temperature = 0.0;
float humidity  = 0.0;
int soilMoisture = 0;

void sensorsInit(){
    dht.begin();
}

void readSensors(){
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if(!isnan(t)) temperature = t;
    if(!isnan(h)) humidity = h;


    soilMoisture = analogRead(SOIL_PIN);
}