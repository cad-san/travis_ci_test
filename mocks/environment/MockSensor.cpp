#include "MockSensor.h"
#include "CppUTestExt/MockSupport.h"

MockSensor::MockSensor(const std::string& name) : Sensor(name)
{
    this->ready_flag = false;
    this->active_flag = false;
}

MockSensor::~MockSensor()
{
}

bool MockSensor::init()
{
    ready_flag = true;
    active_flag = false;
    mock().actualCall("Sensor#init()").onObject(this);
    return true;
}

bool MockSensor::start()
{
    active_flag = true;
    mock().actualCall("Sensor#start()").onObject(this);
    return true;
}

bool MockSensor::stop()
{
    active_flag = false;
    mock().actualCall("Sensor#stop()").onObject(this);
    return true;
}

const bool MockSensor::isReady() const
{
    return ready_flag;
}

const bool MockSensor::isActive() const
{
    return active_flag;
}
