#include "CppUTest/TestHarness.h"
#include "ThreadedSensor.h"
#include "MockSensorController.h"

#include <boost/make_shared.hpp>

static const char* dummy_name = "dummy_sensor";

TEST_GROUP(Sensor)
{
    ThreadedSensor* sensor;

    void setup()
    {
        ControllerPtr controller = boost::make_shared<MockSensorController>();
        sensor = new ThreadedSensor(dummy_name, controller);
    }
    void teardown()
    {
        delete sensor;
    }
};

TEST(Sensor, Create)
{
    CHECK_EQUAL(dummy_name, sensor->getName());
    CHECK_EQUAL(false, sensor->isReady());
    CHECK_EQUAL(false, sensor->isActive());
}

TEST(Sensor, Control)
{
    sensor->setIntervalMiliSec( 500 );

    CHECK_EQUAL(true, sensor->init());
    CHECK_EQUAL(true, sensor->isReady());

    CHECK_EQUAL(true, sensor->start());
    CHECK_EQUAL(true, sensor->isActive());

    CHECK_EQUAL(true, sensor->stop());
    CHECK_EQUAL(false, sensor->isActive());
}
