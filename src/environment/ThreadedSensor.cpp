#include "ThreadedSensor.h"

ThreadedSensor::ThreadedSensor(const std::string& name,
                               const ControllerPtr& controller_ptr)
    : Sensor(name),
      controller_(controller_ptr),
      thread_(controller_ptr)
{
}

ThreadedSensor::~ThreadedSensor()
{
}

bool ThreadedSensor::init()
{
    return thread_.init();
}

bool ThreadedSensor::start()
{
    return thread_.start();
}

bool ThreadedSensor::stop()
{
    return thread_.stop();
}

bool ThreadedSensor::isReady() const
{
    return thread_.isReady();
}

bool ThreadedSensor::isActive() const
{
    return thread_.isActive();
}

void ThreadedSensor::setIntervalMiliSec(const int interval_msec)
{
    thread_.setIntervalMiliSec(interval_msec);
}
