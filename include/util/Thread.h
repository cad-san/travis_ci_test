#ifndef D_THREAD_H
#define D_THREAD_H

#include "UtilTime.h"
#include "Runner.h"

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

class Thread
{
private:
    typedef boost::mutex::scoped_lock lock;
    typedef boost::shared_ptr<boost::thread> ThreadPtr;

    bool end_flag;
    bool ready_flag;
    bool active_flag;

    ThreadPtr main_thread;
    boost::mutex message_guard;
    boost::condition_variable_any active_request;
    boost::condition_variable_any end_request;

    RunnerPtr runner;
    UtilTime interval;

    void initFlags();

    void requestStarting();
    void notifyStarting();
    void waitStarting();

    void requestStopping();
    void notifyStopping();
    void waitStopping();

    void main();

public:
    Thread(const RunnerPtr& runner);
    virtual ~Thread();

    bool init();
    bool start();
    bool stop();

    const bool isReady() const;
    const bool isActive() const;

    void setIntervalMiliSec(const int interval_msec);

    const UtilTime getIntervalTime() const;

    const UtilTime getBaseTime() const;
    const UtilTime getNextTime(const UtilTime& base) const;
};

#endif
