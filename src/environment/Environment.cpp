#include "Environment.h"

Environment::Environment()
{
}

Environment::~Environment()
{
}

void Environment::init()
{
    SensorList::iterator it = sensor_list.begin();
    while(it != sensor_list.end())
    {
        it->second->init();
        ++it;
    }
}

void Environment::start()
{
    SensorList::iterator it = sensor_list.begin();
    while(it != sensor_list.end())
    {
        it->second->start();
        ++it;
    }
}

void Environment::stop()
{
    SensorList::iterator it = sensor_list.begin();
    while(it != sensor_list.end())
    {
        it->second->stop();
        ++it;
    }
}

void Environment::addSensor(const std::string& name, const SensorPtr& sensor)
{
    if(sensor.get() == NULL)
        return;

    sensor_list.insert(SensorList::value_type(name, sensor));
}

const int Environment::getNumSensor() const
{
    return sensor_list.size();
}

const SensorPtr Environment::getSensorByName(const std::string& name) const
{
    SensorList::const_iterator it = sensor_list.find(name);
    if(it == sensor_list.end())
        return SensorPtr();

    return it->second;
}
