#include <Arduino.h>
#include "sensors.h"
#include "webserver.h"


void setup(){
    Serial.begin(115200);

    sensorsInit();
    startWebServer();
}

void loop() {
    readSensors();
    delay(2000);
}