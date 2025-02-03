#include <LilyGoLib.h>
#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>

//######### TESTING ###########
//https://github.com/lewisxhe/BMA423_Library
//https://vscode.dev/github/dontbanmeplz/bluewatch-master-2/blob/main/.pio/libdeps/twatch-s3/TTGO%20TWatch%20Library/examples/sleep/WakeupFromSensor/WakeupFromSensor.ino
//sleep.cc:52
#ifndef BMA423_SDA
#define BMA423_SDA  10
#endif

#ifndef BMA423_SCL
#define BMA423_SCL  11  
#endif

#ifndef BMA423_IRQ
#define BMA423_IRQ  14
#endif
bool sensIRQ = false;
void nothing() {
    sensIRQ = true;
}
LilyGoLib::SensorBMA423 accel;

void setupSensor()
{

    pinMode(BMA423_IRQ, INPUT);
    attachInterrupt(BMA423_IRQ, nothing, RISING);
    
    if (!accel.begin(Wire, BMA423_SLAVE_ADDRESS, BMA423_SDA, BMA423_SCL)) {
        Serial.println("Failed to find BMA423 - check your wiring!");
        while (1) {
            delay(1000);
        }
    }
    accel.setReampAxes((LilyGoLib::SensorBMA423::SensorRemap)4);
    accel.setStepCounterWatermark(1);
    Serial.println("Init BAM423 Sensor success!");
    accel.configAccelerometer();

    accel.enableAccelerometer();

    accel.enablePedometer();

    
    accel.enableFeature(SensorBMA423::FEATURE_STEP_CNTR, true);
                        
    accel.enableFeature(SensorBMA423::FEATURE_TILT, true);


    accel.enablePedometerIRQ();
    
    accel.configInterrupt();
    
    //accel.attachBMA(nothing);

}

