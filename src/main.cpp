#include <Arduino.h>
#include "sensors.h"
#include "webserver.h"
#include "Blynk_server.h"


void setup(){
    Serial.begin(115200);

    sensorsInit();
    startup();

}

void loop() {
    readSensors();
    delay(2000);
    run_code();
}