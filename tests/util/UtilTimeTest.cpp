#include "CppUTest/TestHarness.h"
#include "UtilTime.h"

#define MSEC_BASE 1000 * 1000

TEST_GROUP(UtilTime)
{
    void setup()
    {
    }
    void teardown()
    {
    }
};

TEST(UtilTime, SimpleAdd)
{
    UtilTime base;
    UtilTime addition;

    base.sec = 1;
    base.nsec = 1000;
    addition.sec = 1;
    addition.nsec = 1000;

    UtilTime result = base + addition;
    LONGS_EQUAL(2, result.sec);
    LONGS_EQUAL(2000, result.nsec);
}

TEST(UtilTime, AddEqual)
{
    UtilTime base;
    UtilTime addition;

    base.sec = 1;
    base.nsec = 1000;
    addition.sec = 1;
    addition.nsec = 1000;

    base += addition;
    LONGS_EQUAL(2, base.sec);
    LONGS_EQUAL(2000, base.nsec);
}

TEST(UtilTime, AddCarry)
{
    UtilTime base;
    UtilTime addition;

    base.sec = 0;
    base.nsec = 500 * MSEC_BASE;
    addition.sec = 0;
    addition.nsec = 500 * MSEC_BASE;

    base += addition;
    LONGS_EQUAL(1, base.sec);
    LONGS_EQUAL(0, base.nsec);
}

TEST(UtilTime, AddInteger)
{
    UtilTime base;
    UtilTime result;

    // 10.5 sec
    base.sec = 10;
    base.nsec = 500 * MSEC_BASE;

    result = base + 10;
    LONGS_EQUAL(20, result.sec);
    LONGS_EQUAL(500 * MSEC_BASE, result.nsec);
}

TEST(UtilTime, AddEqualWithInteger)
{
    UtilTime base;

    // 10.5 sec
    base.sec = 10;
    base.nsec = 500 * MSEC_BASE;

    base += 10;
    LONGS_EQUAL(20, base.sec);
    LONGS_EQUAL(500 * MSEC_BASE, base.nsec);
}

TEST(UtilTime, AddFloat)
{
    UtilTime base;
    UtilTime result;

    // 10.5 sec
    base.sec = 10;
    base.nsec = 500 * MSEC_BASE;

    result = base + 9.5;
    LONGS_EQUAL(20, result.sec);
    LONGS_EQUAL(0 * MSEC_BASE, result.nsec);
}

TEST(UtilTime, AddEqualFloat)
{
    UtilTime result;

    // 10.5 sec
    result.sec = 10;
    result.nsec = 500 * MSEC_BASE;

    result += 9.5;
    LONGS_EQUAL(20, result.sec);
    LONGS_EQUAL(0 * MSEC_BASE, result.nsec);
}

TEST(UtilTime, Equal)
{
    UtilTime actual;
    UtilTime expect;

    actual.sec = 1;
    actual.nsec = 5 * MSEC_BASE;

    expect.sec = 5;
    expect.nsec = 0 * MSEC_BASE;

    actual = expect;

    LONGS_EQUAL(expect.sec, actual.sec);
    LONGS_EQUAL(expect.nsec, actual.nsec);
}

TEST(UtilTime, EqualNumber)
{
    UtilTime actual;

    actual.sec = 1;
    actual.nsec = 5 * MSEC_BASE;

    actual = 5.0;

    LONGS_EQUAL(5, actual.sec);
    LONGS_EQUAL(0, actual.nsec);
}
