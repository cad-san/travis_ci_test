#include "Thread.h"
#include <boost/version.hpp>

static const int INTERVAL_TIME = 500;

#if BOOST_VERSION >= 105000
#define TIME_UTC boost::TIME_UTC_
#else
#define TIME_UTC boost::TIME_UTC
#endif

Thread::Thread(const RunnerPtr& runner)
{
    initFlags();
    this->setIntervalMiliSec(INTERVAL_TIME);
    this->runner = runner;
}

Thread::~Thread()
{
    if(isActive())
        stop();
}

bool Thread::init()
{
    /* Activeのとき無効 */
    if(isActive())
        return false;

    /* Runnerの初期化 */
    if(runner != NULL)
        runner->init();

    initFlags();

    this->ready_flag = true;

    return true;
}

bool Thread::start()
{
    /* 未初期化時無効 */
    if(!isReady())
        return false;

    requestStarting();
    waitStarting();

    return true;
}

bool Thread::stop()
{
    /* Activeでないときは無効 */
    if(!isActive())
        return false;

    requestStopping();
    waitStopping();

    return true;
}

void Thread::main()
{
    UtilTime expect_time = getBaseTime();

    /* スレッド開始 */
    notifyStarting();
    for(;;)
    {
        lock lk(message_guard);

        /* 終了判定 */
        if(end_flag)
            break;

        /* Stepの実行 */
        if(runner != NULL)
            runner->step();

        /* Intervalに基づき待機 */
        expect_time = getNextTime(expect_time);
        if(end_request.timed_wait(lk, static_cast<boost::xtime>(expect_time)))
            break;
    }
    notifyStopping();
    /* スレッド終了 */
}

void Thread::requestStarting()
{
    /* 未初期化時無効 */
    if(!isReady())
        return;

    this->main_thread = ThreadPtr(new boost::thread(&Thread::main, this));
}

void Thread::waitStarting()
{
    /* 未初期化時はブロック */
    if(end_flag)
        return;

    lock lk(message_guard);
    while(!isActive())
        active_request.wait(lk);
}

void Thread::notifyStarting()
{
    lock kl(message_guard);
    active_flag = true;
    active_request.notify_one();
}

void Thread::requestStopping()
{
    /* Activeでないときは無効 */
    if(!isActive())
        return;

    lock kl(message_guard);
    end_flag = true;
    end_request.notify_one();
}

void Thread::notifyStopping()
{
    lock kl(message_guard);
    active_flag = false;
    active_request.notify_one();
}

void Thread::waitStopping()
{
    /* 終了要求未発行ならブロック */
    if(!end_flag)
        return;

    main_thread->join();
}

void Thread::initFlags()
{
    this->ready_flag = false;
    this->active_flag = false;
    this->end_flag = false;
}

const bool Thread::isReady() const
{
    return ready_flag;
}

const bool Thread::isActive() const
{
    return active_flag;
}

void Thread::setIntervalMiliSec(const int interval_msec)
{
    interval = static_cast<double>(interval_msec) / 1000;
}

const UtilTime Thread::getIntervalTime() const
{
    return interval;
}

const UtilTime Thread::getBaseTime() const
{
    UtilTime base;
    boost::xtime_get(&base, TIME_UTC);
    return base;
}

const UtilTime Thread::getNextTime(const UtilTime& base) const
{
    return base + interval;
}
