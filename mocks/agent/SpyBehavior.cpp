#include "SpyBehavior.h"

SpyBehavior::SpyBehavior(const unsigned int behavior_id)
    : Behavior(behavior_id)
{
    this->activation_ = true;
    this->init_state_ = false;
    this->sensing_state_ = false;
    this->perform_state_ = false;
}

SpyBehavior::~SpyBehavior()
{
}

bool SpyBehavior::initialized()
{
    return init_state_;
}

bool SpyBehavior::sensed()
{
    return sensing_state_;
}

bool SpyBehavior::performed()
{
    return perform_state_;
}

void SpyBehavior::init()
{
    init_state_ = true;
}

void SpyBehavior::sensing()
{
    perform_state_ = false;
    sensing_state_ = true;
}

void SpyBehavior::perform()
{
    if(sensing_state_)
        perform_state_ = true;
    else
        perform_state_ = false;
}

bool SpyBehavior::isActive() const
{
    return activation_ && sensing_state_;
}

void SpyBehavior::setActivation(const bool new_activation)
{
    this->activation_ = new_activation;
}
