#ifndef D_MOCK_RUNNER_H
#define D_MOCK_RUNNER_H

#include <boost/thread.hpp>
#include "Runner.h"

class MockRunner : public Runner
{
private:
    typedef boost::mutex::scoped_lock lock;

    boost::mutex message_guard;
    boost::condition_variable_any condition_performed;

    bool performed_flag;
    bool initialized_flag;

public:
    MockRunner()
    {
        performed_flag = false;
        initialized_flag = false;
    }

    void init()
    {
        initialized_flag = true;
    }

    void step()
    {
        performed_flag = true;
        condition_performed.notify_one();
    }

    bool performed()
    {
        return performed_flag;
    }

    bool initialized()
    {
        return initialized_flag;
    }

    void waitPerforming(const UtilTime& time)
    {
        if(performed_flag)
            return;

        lock lk(message_guard);
        condition_performed.timed_wait(lk, static_cast<boost::xtime>(time));
    }
};
typedef boost::shared_ptr<MockRunner> MockRunnerPtr;

#endif
