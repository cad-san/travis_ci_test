#ifndef D_MOCK_RUNNER_H
#define D_MOCK_RUNNER_H

#include <boost/thread.hpp>
#include "Runner.h"

class MockRunner : public Runner
{
private:
    typedef boost::mutex::scoped_lock lock;

    boost::mutex message_guard_;
    boost::condition_variable_any condition_performed_;

    bool performed_flag_;
    bool initialized_flag_;

public:
    MockRunner()
    {
        performed_flag_ = false;
        initialized_flag_ = false;
    }

    void init()
    {
        initialized_flag_ = true;
    }

    void step()
    {
        performed_flag_ = true;
        condition_performed_.notify_one();
    }

    bool performed()
    {
        return performed_flag_;
    }

    bool initialized()
    {
        return initialized_flag_;
    }

    void waitPerforming(const UtilTime& time)
    {
        if(performed_flag_)
            return;

        lock lk(message_guard_);
        condition_performed_.timed_wait(lk, static_cast<boost::xtime>(time));
    }
};
typedef boost::shared_ptr<MockRunner> MockRunnerPtr;

#endif
