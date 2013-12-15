#ifndef D_SENSOR_CONTROLLER_H
#define D_SENSOR_CONTROLLER_H

#include "Runner.h"

class SensorController : public Runner
{
public:
    virtual ~SensorController(){}
    virtual void init() = 0;
    virtual void step() = 0;
};

typedef boost::shared_ptr<SensorController> ControllerPtr;

#endif
