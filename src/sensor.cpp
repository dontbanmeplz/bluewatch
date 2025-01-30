#include <LilyGoLib.h>

void setupSensor()
{
    watch.configAccelerometer();

    watch.enableAccelerometer();

    watch.enablePedometer();

    watch.configInterrupt();

    watch.enableFeature(SensorBMA423::FEATURE_STEP_CNTR |
                        SensorBMA423::FEATURE_TILT |
                        true);


    watch.enablePedometerIRQ();
    watch.enableTiltIRQ();


    watch.attachBMA(true);

}

