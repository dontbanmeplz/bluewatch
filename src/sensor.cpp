#include <LilyGoLib.h>
void nothing() {}

void setupSensor()
{
    watch.configAccelerometer();

    watch.enableAccelerometer();

    watch.enablePedometer();

    
    watch.enableFeature(SensorBMA423::FEATURE_STEP_CNTR |
                        SensorBMA423::FEATURE_ANY_MOTION |
                        SensorBMA423::FEATURE_NO_MOTION |
                        SensorBMA423::FEATURE_ACTIVITY |
                        SensorBMA423::FEATURE_TILT |
                        SensorBMA423::FEATURE_WAKEUP,
                        false);
    watch.enableFeature(SensorBMA423::FEATURE_STEP_CNTR |
                        SensorBMA423::FEATURE_TILT,
                        true);


    watch.enablePedometerIRQ();
    watch.enableTiltIRQ();
    
    watch.configInterrupt();

    watch.attachBMA(nothing);

}

