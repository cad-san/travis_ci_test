#include "CppUTest/TestHarness.h"
#include "Thread.h"
#include "MockRunner.h"

#include <boost/make_shared.hpp>

TEST_GROUP(Thread)
{
    MockRunnerPtr runner;
    Thread* thread;

    void setup()
    {
        runner = boost::make_shared<MockRunner>();
        thread = new Thread(runner);
    }

    void teardown()
    {
        destroyThead();
    }

    void destroyThead()
    {
        if(thread == NULL)
            return;
        delete thread;
        thread = NULL;
    }

    void waitFirstStep()
    {
        UtilTime expect_time = thread->getNextTime(thread->getBaseTime());
        runner->waitPerforming(expect_time);
    }
};

TEST(Thread, Create)
{
    CHECK_EQUAL(false, thread->isReady());
    CHECK_EQUAL(false, thread->isActive());
}

TEST(Thread, Interval)
{
    UtilTime result;
    thread->setIntervalMiliSec( 500 );
    result = thread->getIntervalTime();

    LONGS_EQUAL(0, result.sec);
    LONGS_EQUAL(500 * UtilTime::MSEC_BASE, result.nsec);
}

TEST(Thread, Control)
{
    thread->setIntervalMiliSec( 500 );

    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->isReady());

    CHECK_EQUAL(true, thread->start());
    CHECK_EQUAL(true, thread->isActive());

    waitFirstStep(); // step()が実行されるまで待つ

    CHECK_EQUAL(true, thread->stop());
    CHECK_EQUAL(false, thread->isActive());

    CHECK_EQUAL(true, runner->initialized());
    CHECK_EQUAL(true, runner->performed());
}

TEST(Thread, StartWithoutInit)
{
    CHECK_EQUAL(false, thread->start());
    CHECK_EQUAL(false, thread->isActive());

    CHECK_EQUAL(false, thread->stop());
    CHECK_EQUAL(false, thread->isActive());

    CHECK_EQUAL(false, runner->initialized());
    CHECK_EQUAL(false, runner->performed());
}

TEST(Thread, StartUntilActive)
{
    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->isReady());

    CHECK_EQUAL(true, thread->start());
    CHECK_EQUAL(true, thread->isActive());

    CHECK_EQUAL(false, thread->start());
    CHECK_EQUAL(true, thread->isActive());
}

TEST(Thread, StopWithoutStart)
{
    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->isReady());

    CHECK_EQUAL(false, thread->stop());
    CHECK_EQUAL(false, thread->isActive());

    CHECK_EQUAL(true, runner->initialized());
    CHECK_EQUAL(false, runner->performed());
}

TEST(Thread, WithoutStop)
{
    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->isReady());

    CHECK_EQUAL(true, thread->start());
    CHECK_EQUAL(true, thread->isActive());

    waitFirstStep(); // step()が実行されるまで待つ

    destroyThead(); // stop()を呼ばずにdelete

    CHECK_EQUAL(true, runner->initialized());
    CHECK_EQUAL(true, runner->performed());
}

TEST(Thread, InitAfterStarted)
{
    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->start());

    CHECK_EQUAL(false, thread->init());

    CHECK_EQUAL(true, thread->stop());
}

TEST(Thread, Start2ndTime)
{
    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->start());
    CHECK_EQUAL(true, thread->stop());

    CHECK_EQUAL(true, thread->start());
    CHECK_EQUAL(true, thread->isActive());

    CHECK_EQUAL(true, thread->stop());
    CHECK_EQUAL(false, thread->isActive());
}
