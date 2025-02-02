#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "SensorBMA423.hpp"

#ifndef SENSOR_SDA
#define SENSOR_SDA  10
#endif

#ifndef SENSOR_SCL
#define SENSOR_SCL  11
#endif

#ifndef SENSOR_IRQ
#define SENSOR_IRQ  14
#endif

SensorBMA423 accel;
uint32_t lastMillis;
bool sensorIRQ = false;


void setFlag()
{
    sensorIRQ = true;
}

void setup()
{
    Serial.begin(115200);
	Serial.println("hi");
    pinMode(SENSOR_IRQ, INPUT);
    attachInterrupt(SENSOR_IRQ, setFlag, RISING);
	Serial.println("bef");
    if (!accel.begin(Wire, BMA423_SLAVE_ADDRESS, SENSOR_SDA, SENSOR_SCL)) {
        Serial.println("Failed to find BMA423 - check your wiring!");
        while (1) {
            delay(1000);
        }
    }

    Serial.println("Init BAM423 Sensor success!");

    //Default 4G ,200HZ
    accel.configAccelerometer();

    // Enable acceleration sensor
    accel.enableAccelerometer();

    // Enable pedometer steps
    accel.enablePedometer();

    // Emptying the pedometer steps
    accel.resetPedometer();

    // Enable sensor features
    accel.enableFeature(SensorBMA423::FEATURE_STEP_CNTR |
                        SensorBMA423::FEATURE_ANY_MOTION |
                        SensorBMA423::FEATURE_ACTIVITY |
                        SensorBMA423::FEATURE_TILT |
                        SensorBMA423::FEATURE_WAKEUP,
                        true);

    // Pedometer interrupt enable
    accel.enablePedometerIRQ();
    // Tilt interrupt enable
    accel.enableTiltIRQ();
    // DoubleTap interrupt enable
    accel.enableWakeupIRQ();
    // Any  motion / no motion interrupt enable
    accel.enableAnyNoMotionIRQ();
    // Activity interruption enable
    accel.enableActivityIRQ();
    // Chip interrupt function enable
    accel.configInterrupt();

}


void loop()
{
    int16_t x, y, z;
    if (sensorIRQ) {
        sensorIRQ = false;
        // The interrupt status must be read after an interrupt is detected
        uint16_t status =   accel.readIrqStatus();
        Serial.printf("Accelerometer interrupt mask : 0x%x\n", status);

        if (accel.isPedometer()) {
            uint32_t stepCounter = accel.getPedometerCounter();
            Serial.printf("Step count interrupt,step Counter:%u\n", stepCounter);
        }
        if (accel.isActivity()) {
            Serial.println("Activity interrupt");
        }
        if (accel.isTilt()) {
            Serial.println("Tilt interrupt");
        }
        if (accel.isDoubleTap()) {
            Serial.println("DoubleTap interrupt");
        }
        if (accel.isAnyNoMotion()) {
            Serial.println("Any motion / no motion interrupt");
        }
    }
    delay(50);
}
