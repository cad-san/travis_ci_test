#include "MockSensor.h"
#include "CppUTestExt/MockSupport.h"

MockSensor::MockSensor(const std::string& name) : Sensor(name)
{
    this->ready_flag_ = false;
    this->active_flag_ = false;
}

MockSensor::~MockSensor()
{
}

bool MockSensor::init()
{
    ready_flag_ = true;
    active_flag_ = false;
    mock().actualCall("Sensor#init()").onObject(this);
    return true;
}

bool MockSensor::start()
{
    active_flag_ = true;
    mock().actualCall("Sensor#start()").onObject(this);
    return true;
}

bool MockSensor::stop()
{
    active_flag_ = false;
    mock().actualCall("Sensor#stop()").onObject(this);
    return true;
}

bool MockSensor::isReady() const
{
    return ready_flag_;
}

bool MockSensor::isActive() const
{
    return active_flag_;
}
