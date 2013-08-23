#include "UtilTime.h"

const int UtilTime::MSEC_BASE = 1000 * 1000;
const int UtilTime::NSEC_BASE = 1000 * 1000 * 1000;

UtilTime::UtilTime()
{
    this->sec = 0;
    this->nsec = 0;
}

UtilTime::~UtilTime()
{
}

const UtilTime::util_sec
UtilTime::add_sec(const UtilTime& base, const UtilTime& addition) const
{
    return (base.sec + addition.sec) + (base.nsec + addition.nsec) / NSEC_BASE;
}

const UtilTime::util_nsec
UtilTime::add_nsec(const UtilTime& base, const UtilTime& addition) const
{
    return (base.nsec + addition.nsec) % NSEC_BASE;
}

const UtilTime
UtilTime::convert_time(const double& time) const
{
    UtilTime result;

    result.sec = static_cast<int>(time);
    result.nsec = (time - result.sec) * NSEC_BASE;

    return result;
}

UtilTime UtilTime::operator+(const UtilTime& time) const
{
    UtilTime result;

    result.sec = add_sec(*this, time);
    result.nsec = add_nsec(*this, time);

    return result;
}

UtilTime& UtilTime::operator=(const UtilTime& time)
{
    sec = time.sec;
    nsec = time.nsec;

    return *this;
}

UtilTime& UtilTime::operator+=(const UtilTime& time)
{
    sec = add_sec(*this, time);
    nsec = add_nsec(*this, time);

    return *this;
}

UtilTime UtilTime::operator+(const double& time) const
{
    UtilTime addition = convert_time(time);
    return *this + addition;
}

UtilTime& UtilTime::operator=(const double& time)
{
    *this = convert_time(time);
    return *this;
}

UtilTime& UtilTime::operator+=(const double& time)
{
    UtilTime addition = convert_time(time);
    *this += addition;
    return *this;
}
