#include "Thread.h"
#include <boost/version.hpp>

static const int INTERVAL_TIME = 500;

#if BOOST_VERSION >= 105000
#define TIME_UTC boost::TIME_UTC_
#else
#define TIME_UTC boost::TIME_UTC
#endif

Thread::Thread(const RunnerPtr& runner_ptr)
{
    initFlags();
    this->setIntervalMiliSec(INTERVAL_TIME);
    this->runner_ = runner_ptr;
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
    if(runner_ != NULL)
        runner_->init();

    initFlags();

    this->ready_flag_ = true;

    return true;
}

bool Thread::start()
{
    /* Activeのとき無効 */
    if(isActive())
        return false;

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
        lock lk(message_guard_);

        /* 終了判定 */
        if(end_flag_)
            break;

        /* Stepの実行 */
        if(runner_ != NULL)
            runner_->step();

        /* Intervalに基づき待機 */
        expect_time = getNextTime(expect_time);
        if(end_request_.timed_wait(lk, static_cast<boost::xtime>(expect_time)))
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

    lock lk(message_guard_);
    this->end_flag_ = false;
    this->main_thread_ = ThreadPtr(new boost::thread(&Thread::main, this));
}

void Thread::waitStarting()
{
    /* 未初期化時はブロック */
    if(end_flag_)
        return;

    lock lk(message_guard_);
    while(!isActive())
        active_request_.wait(lk);
}

void Thread::notifyStarting()
{
    lock kl(message_guard_);
    active_flag_ = true;
    active_request_.notify_one();
}

void Thread::requestStopping()
{
    /* Activeでないときは無効 */
    if(!isActive())
        return;

    lock kl(message_guard_);
    end_flag_ = true;
    end_request_.notify_one();
}

void Thread::notifyStopping()
{
    lock kl(message_guard_);
    active_flag_ = false;
    active_request_.notify_one();
}

void Thread::waitStopping()
{
    /* 終了要求未発行ならブロック */
    if(!end_flag_)
        return;

    main_thread_->join();
}

void Thread::initFlags()
{
    this->ready_flag_ = false;
    this->active_flag_ = false;
    this->end_flag_ = false;
}

bool Thread::isReady() const
{
    return ready_flag_;
}

bool Thread::isActive() const
{
    return active_flag_;
}

void Thread::setIntervalMiliSec(const int interval_msec)
{
    interval_ = static_cast<double>(interval_msec) / 1000;
}

const UtilTime Thread::getIntervalTime() const
{
    return interval_;
}

const UtilTime Thread::getBaseTime() const
{
    UtilTime base;
    boost::xtime_get(&base, TIME_UTC);
    return base;
}

const UtilTime Thread::getNextTime(const UtilTime& base) const
{
    return base + interval_;
}
