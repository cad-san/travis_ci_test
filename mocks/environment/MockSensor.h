#ifndef D_MOCK_SENSOR_H
#define D_MOCK_SENSOR_H

#include "Sensor.h"
#include <string>

class MockSensor : public Sensor
{
private:
    bool ready_flag_;
    bool active_flag_;
public:
    MockSensor(const std::string& name);
    ~MockSensor();

    bool init();
    bool start();
    bool stop();

    bool isReady() const;
    bool isActive() const;
};

#endif
