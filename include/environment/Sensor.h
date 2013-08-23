#ifndef D_SENSOR_H
#define D_SENSOR_H

#include <string>

class Sensor
{
protected:
    std::string sensor_name;
public:
    Sensor(const std::string& name)
    {
        this->sensor_name = name;
    }
    virtual ~Sensor() {};

    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;

    virtual const bool isReady() const = 0;
    virtual const bool isActive() const = 0;

    const std::string getName() const { return sensor_name; };
};

#endif
