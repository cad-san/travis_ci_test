#ifndef D_THREADED_SENSOR_H
#define D_THREADED_SENSOR_H

#include "Sensor.h"
#include "SensorController.h"
#include "Thread.h"

class ThreadedSensor : public Sensor
{
private:
    ControllerPtr controllPtr;
    Thread thread;

public:
    ThreadedSensor(const std::string& name, const ControllerPtr& controller);
    virtual ~ThreadedSensor();

    bool init();
    bool start();
    bool stop();

    const bool isReady() const;
    const bool isActive() const;

    void setIntervalMiliSec(const int interval_msec);
};

#endif
