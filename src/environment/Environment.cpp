#include "Environment.h"

Environment::Environment()
{
}

Environment::~Environment()
{
}

void Environment::init()
{
    SensorList::iterator it = sensor_list_.begin();
    while(it != sensor_list_.end())
    {
        it->second->init();
        ++it;
    }
}

void Environment::start()
{
    SensorList::iterator it = sensor_list_.begin();
    while(it != sensor_list_.end())
    {
        it->second->start();
        ++it;
    }
}

void Environment::stop()
{
    SensorList::iterator it = sensor_list_.begin();
    while(it != sensor_list_.end())
    {
        it->second->stop();
        ++it;
    }
}

void Environment::addSensor(const std::string& name, const SensorPtr& sensor)
{
    if(sensor.get() == NULL)
        return;

    sensor_list_.insert(SensorList::value_type(name, sensor));
}

int Environment::getNumSensor() const
{
    return static_cast<int>(sensor_list_.size());
}

const SensorPtr Environment::getSensorByName(const std::string& name) const
{
    SensorList::const_iterator it = sensor_list_.find(name);
    if(it == sensor_list_.end())
        return SensorPtr();

    return it->second;
}
