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

    bool end_flag_;
    bool ready_flag_;
    bool active_flag_;

    ThreadPtr main_thread_;
    boost::mutex message_guard_;
    boost::condition_variable_any active_request_;
    boost::condition_variable_any end_request_;

    RunnerPtr runner_;
    UtilTime interval_;

    void initFlags();

    void requestStarting();
    void notifyStarting();
    void waitStarting();

    void requestStopping();
    void notifyStopping();
    void waitStopping();

    void main();

public:
    Thread(const RunnerPtr& runner_ptr);
    virtual ~Thread();

    bool init();
    bool start();
    bool stop();

    bool isReady() const;
    bool isActive() const;

    void setIntervalMiliSec(const int interval_msec);

    const UtilTime getIntervalTime() const;

    const UtilTime getBaseTime() const;
    const UtilTime getNextTime(const UtilTime& base) const;
};

#endif
