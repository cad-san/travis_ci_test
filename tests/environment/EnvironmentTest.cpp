#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "UtilAssert.h"

#include "Environment.h"
#include "MockSensor.h"

#include <boost/make_shared.hpp>

static const char* dummy_name_01 = "dummy_01";
static const char* dummy_name_02 = "dummy_02";

typedef boost::shared_ptr<MockSensor> MockSensorPtr;
typedef std::vector<MockSensorPtr> MockSensorList;

TEST_GROUP(Environment)
{
    Environment* env;
    void setup()
    {
        env = new Environment();
    }
    void teardown()
    {
        mock().clear();
        delete env;
    }

    int createSensors(std::string names[], unsigned int size, MockSensorList* sensors)
    {
        if(names == NULL || size < 1)
            return -1;

        if(sensors == NULL)
            return -1;

        sensors->clear();
        for(unsigned int i = 0; i < size; i++)
            sensors->push_back( createSensorPtr(names[i]) );
        return 0;
    }

    MockSensorPtr createSensorPtr(const std::string& name)
    {
        return boost::make_shared<MockSensor>(name);
    }

    void addSensorsToEnv(MockSensorList* sensors)
    {
        for(unsigned int i = 0; i < sensors->size(); i++)
            env->addSensor(sensors->at(i)->getName(), sensors->at(i));
    }

    void checkSensorsInEnv(std::string names[], MockSensorList* sensors)
    {
        LONGS_EQUAL(sensors->size(), env->getNumSensor());

        for(unsigned int i = 0; i < sensors->size(); i++)
            SHARED_PTRS_EQUAL(sensors->at(i), env->getSensorByName(names[i]));
    }

    void expectOneCallOfInitIn(const MockSensorPtr& sensor)
    {
        mock().expectOneCall("Sensor#init()").onObject(sensor.get());
    }

    void expectOneCallOfStartIn(const MockSensorPtr& sensor)
    {
        mock().expectOneCall("Sensor#start()").onObject(sensor.get());
    }

    void expectOneCallOfStopIn(const MockSensorPtr& sensor)
    {
        mock().expectOneCall("Sensor#stop()").onObject(sensor.get());
    }

    void checkExpectations()
    {
        mock().checkExpectations();
    }
};

TEST(Environment, AddSensor)
{
    MockSensorPtr sensor = createSensorPtr(dummy_name_01);
    env->addSensor(dummy_name_01, sensor);
    LONGS_EQUAL(1, env->getNumSensor());
}

TEST(Environment, AddMultipleSensor)
{
    MockSensorList sensors;
    std::string names[] = {dummy_name_01, dummy_name_02};

    createSensors(names, 2, &sensors);

    addSensorsToEnv(&sensors);

    checkSensorsInEnv(names, &sensors);
}

TEST(Environment, NoSensorInEnvironment)
{
    LONGS_EQUAL(0, env->getNumSensor());
    CHECK_SHARED_PTR_NULL(env->getSensorByName("not_exist_sensor"));
}

TEST(Environment, AddNullSensor)
{
    MockSensorPtr null_sensor( static_cast<MockSensor*>(NULL) );
    env->addSensor(dummy_name_01, null_sensor);
    LONGS_EQUAL(0, env->getNumSensor());
    CHECK_SHARED_PTR_NULL(env->getSensorByName(dummy_name_01));
}

TEST(Environment, SingleSensorControl)
{
    MockSensorPtr sensor = createSensorPtr(dummy_name_01);
    env->addSensor(dummy_name_01, sensor);

    expectOneCallOfInitIn(sensor);
    env->init();

    expectOneCallOfStartIn(sensor);
    env->start();

    expectOneCallOfStopIn(sensor);
    env->stop();

    checkExpectations();
}

TEST(Environment, MultipleSensorControl)
{
    MockSensorList sensors;
    std::string names[] = {dummy_name_01, dummy_name_02};

    createSensors(names, 2, &sensors);

    addSensorsToEnv(&sensors);

    expectOneCallOfInitIn(sensors[0]);
    expectOneCallOfInitIn(sensors[1]);
    env->init();

    expectOneCallOfStartIn(sensors[0]);
    expectOneCallOfStartIn(sensors[1]);
    env->start();

    expectOneCallOfStopIn(sensors[0]);
    expectOneCallOfStopIn(sensors[1]);
    env->stop();

    checkExpectations();
}

