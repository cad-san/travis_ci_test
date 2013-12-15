#ifndef D_MOCK_SENSOR_CONTROLLER_H
#define D_MOCK_SENSOR_CONTROLLER_H

#include "SensorController.h"

class MockSensorController : public SensorController
{
private:
    bool performed_flag_;
    bool initialized_flag_;
public:
    MockSensorController()
    {
        performed_flag_ = false;
        initialized_flag_ = false;
    }
    void init()
    {
        performed_flag_ = false;
        initialized_flag_ = true;
    }
    void step()
    {
        performed_flag_ = true;
    }

    bool performed()
    {
        return performed_flag_;
    }

    bool initialized()
    {
        return initialized_flag_;
    }
};

#endif
