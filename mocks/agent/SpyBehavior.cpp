#include "SpyBehavior.h"

SpyBehavior::SpyBehavior(const unsigned int id)
{
    this->id = id;
    this->activation = true;
    this->init_state = false;
    this->sensing_state = false;
    this->perform_state = false;
}

SpyBehavior::~SpyBehavior()
{
}

bool SpyBehavior::initialized()
{
    return init_state;
}

bool SpyBehavior::sensed()
{
    return sensing_state;
}

bool SpyBehavior::performed()
{
    return perform_state;
}

void SpyBehavior::init()
{
    init_state = true;
}

void SpyBehavior::sensing()
{
    perform_state = false;
    sensing_state = true;
}

void SpyBehavior::perform()
{
    if(sensing_state)
        perform_state = true;
    else
        perform_state = false;
}

const bool SpyBehavior::isActive() const
{
    return activation && sensing_state;
}

void SpyBehavior::setActivation(const bool activation)
{
    this->activation = activation;
}