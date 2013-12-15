#ifndef D_SENSOR_H
#define D_SENSOR_H

#include <string>
#include <boost/shared_ptr.hpp>

class Sensor
{
protected:
    std::string sensor_name_;
public:
    Sensor(const std::string& name)
    {
        this->sensor_name_ = name;
    }
    virtual ~Sensor() {}

    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;

    virtual bool isReady() const = 0;
    virtual bool isActive() const = 0;

    const std::string getName() const { return sensor_name_; }
};

typedef boost::shared_ptr<Sensor> SensorPtr;

#endif
