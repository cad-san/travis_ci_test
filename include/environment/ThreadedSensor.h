#ifndef D_THREADED_SENSOR_H
#define D_THREADED_SENSOR_H

#include "Sensor.h"
#include "SensorController.h"
#include "Thread.h"

class ThreadedSensor : public Sensor
{
private:
    ControllerPtr controller_;
    Thread thread_;

public:
    ThreadedSensor(const std::string& name, const ControllerPtr& controller_ptr);
    virtual ~ThreadedSensor();

    bool init();
    bool start();
    bool stop();

    bool isReady() const;
    bool isActive() const;

    void setIntervalMiliSec(const int interval_msec);
};

typedef boost::shared_ptr<ThreadedSensor> ThreadedSensorPtr;

#endif
