#ifndef SENSORS_H
#define SENSORS_H

void sensorsInit();
void readSensors();

extern float temperature;
extern float humidity;
extern int soilMoisture;

#endif