#ifndef D_MOCK_SENSOR_CONTROLLER_H
#define D_MOCK_SENSOR_CONTROLLER_H

#include "SensorController.h"

class MockSensorController : public SensorController
{
private:
    bool performed_flag;
    bool initialized_flag;
public:
    MockSensorController()
    {
        performed_flag = false;
        initialized_flag = false;
    }
    void init()
    {
        performed_flag = false;
        initialized_flag = true;
    }
    void step()
    {
        performed_flag = true;
    }

    bool performed()
    {
        return performed_flag;
    }

    bool initialized()
    {
        return initialized_flag;
    }
};

#endif
