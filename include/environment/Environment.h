#ifndef D_ENVIRONMENT_H
#define D_ENVIRONMENT_H

#include "Sensor.h"
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

class Environment
{
private:
    typedef std::map< std::string, SensorPtr > SensorList;

    SensorList sensor_list_;
public:
    Environment();
    virtual ~Environment();

    void init();
    void start();
    void stop();

    void addSensor(const std::string& name, const SensorPtr& sensor);

    const SensorPtr getSensorByName(const std::string& name) const;
    int getNumSensor() const;
};

typedef boost::shared_ptr<Environment> EnvironmentPtr;

#endif
