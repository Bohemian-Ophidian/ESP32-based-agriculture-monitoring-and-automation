#define BLYNK_TEMPLATE_ID "TMPL31EdA9lED"
#define BLYNK_TEMPLATE_NAME "Agriculture Automation and Monitoring System"
#define BLYNK_AUTH_TOKEN "fRXvGbJ6Zj2vpkzd8n4NazYurfEBGhfO"

#include <WiFi.h>
#include "sensors.h"
#include <sensors.h>
#include <Arduino.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int output_value;
int moisturelevel;

int notified = 0;
int timedelay= 15000L;

float calculate_MS_Score(float MS) {
  if (MS >= 30.0 && MS <= 60.0) return 100.0;
  else if (MS >= 10.0 && MS < 30.0) return 5.0 * (MS - 10.0);
  else if (MS > 60.0 && MS <= 80.0) return -5.0 * (MS - 80.0);
  else return 0.0;
}

float calculate_AH_Score(float AH) {
  if (AH >= 40.0 && AH <= 70.0) return 100.0;
  else if (AH >= 20.0 && AH < 40.0) return 5.0 * (AH - 20.0);
  else if (AH > 70.0 && AH <= 90.0) return -5.0 * (AH - 90.0);
  else return 0.0;
}

float calculate_ST_Score(float ST) {
  // NOTE: You should use a separate soil temperature sensor for accuracy. 
  // We use airTemp_C (ST) as a placeholder here.
  if (ST >= 20.0 && ST <= 30.0) return 100.0;
  else if (ST >= 10.0 && ST < 20.0) return 10.0 * (ST - 10.0);
  else if (ST > 30.0 && ST <= 40.0) return -10.0 * (ST - 40.0);
  else return 0.0;
}

float calculate_soil_moisture(float sm){
    return (abs(4095-sm)/4095*100);
}

void Sensors(){
    float sm = calculate_soil_moisture(soilMoisture);
    float score_ST = calculate_ST_Score(temperature); // Using air temp placeholder
    float score_AH = calculate_AH_Score(humidity);
    float score_MS = calculate_MS_Score(sm);

  // Calculate Weighted Soil Health Score (SHS)
  // Example Weights: Soil Moisture (50%), Soil Temp (30%), Air Humidity (20%)
    float W_ST = 0.3;
    float W_AH = 0.2;
    float W_MS = 0.5;
  
    float SHS = (W_MS * score_MS) + (W_ST * score_ST) + (W_AH * score_AH);
    
  
    Blynk.virtualWrite(V0, sm);
    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V2, humidity);
    Blynk.virtualWrite(V3, SHS);
}

char ssid[] = "hello";
char password[] = "password";

BlynkTimer timer;

void startup(){
    Serial.begin(115200);
    Blynk.begin( BLYNK_AUTH_TOKEN,ssid, password);
    timer.setInterval(timedelay, Sensors);
}

void run_code(){
    Blynk.run();
    timer.run();
}
