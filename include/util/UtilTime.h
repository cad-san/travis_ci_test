#ifndef D_UTIL_TIME_H
#define D_UTIL_TIME_H

#include <boost/thread/xtime.hpp>

struct UtilTime : boost::xtime
{
private:
    typedef boost::xtime::xtime_sec_t util_sec;
    typedef boost::xtime::xtime_nsec_t util_nsec;

    const util_sec add_sec(const UtilTime& base, const UtilTime& addition) const;
    const util_nsec add_nsec(const UtilTime& base, const UtilTime& addition) const;

    const UtilTime convert_time(const double& time) const;

public:
    static const int MSEC_BASE;
    static const int NSEC_BASE;

    UtilTime();
    virtual ~UtilTime();

    UtilTime operator+(const UtilTime& time) const;
    UtilTime& operator=(const UtilTime& time);
    UtilTime& operator+=(const UtilTime& time);

    UtilTime operator+(const double& time) const;
    UtilTime& operator=(const double& time);
    UtilTime& operator+=(const double& time);
};

#endif
