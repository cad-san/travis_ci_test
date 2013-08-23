#ifndef D_RUNNER_H
#define D_RUNNER_H

#include <boost/shared_ptr.hpp>

class Runner
{
public:
    virtual ~Runner(){}
    virtual void init() = 0;
    virtual void step() = 0;
};
typedef boost::shared_ptr<Runner> RunnerPtr;

#endif
