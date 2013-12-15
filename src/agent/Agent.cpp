#include "Agent.h"

#include <algorithm>

const int Agent::INVALID_LAYER = -1;

Agent::Agent()
{
}

Agent::~Agent()
{
}

void Agent::init()
{
    for(unsigned int i = 0; i < behaviors_.size(); i++)
    {
        behaviors_.at(i)->init();
    }
}

void Agent::step()
{
    Behavior* active_behavior = NULL;
    for(unsigned int i = 0; i < behaviors_.size(); i++)
    {
        // sensingの実行
        behaviors_.at(i)->sensing();
        // 後のBehaviorを優先する
        if(behaviors_.at(i)->isActive())
            active_behavior = behaviors_.at(i).get();
    }

    // ActiveなBehaviorが無いなら何もしない
    if(active_behavior == NULL)
        return;

    active_behavior->perform();
}

int Agent::getNumBehaviors() const
{
    return static_cast<int>(behaviors_.size());
}

void Agent::addBehavior(const BehaviorPtr& new_behavior)
{
    if(new_behavior.get() == NULL)
        return;

    int layer = convertFromIDtoLayer(new_behavior->getID());

    if(layer != INVALID_LAYER)
        removeBehaviorAt(static_cast<unsigned int>(layer));

    behaviors_.push_back(new_behavior);
}

void Agent::removeBehaviorAt(unsigned int layer)
{
    if( !isValidLayer(layer) )
        return;

    BehaviorPtr target = behaviors_.at(layer);
    behaviors_.erase(std::remove(behaviors_.begin(), behaviors_.end(), target),
                    behaviors_.end());
}

const BehaviorPtr Agent::getBehaviorAt(const unsigned int layer) const
{
    if(!isValidLayer(layer))
        return BehaviorPtr();

    return behaviors_.at(layer);
}

const BehaviorPtr Agent::getBehaviorByID(const unsigned int id) const
{
    int layer = convertFromIDtoLayer(id);

    if(layer == INVALID_LAYER)
        return BehaviorPtr();

    return behaviors_.at(static_cast<unsigned int>(layer));
}

int Agent::convertFromIDtoLayer(unsigned int id) const
{
    // 対象のIDを走査する
    for(unsigned int i = 0; i < behaviors_.size(); i++)
    {
        if(behaviors_.at(i)->getID() == id)
            return static_cast<int>(i);
    }
    // ヒットしなかった
    return INVALID_LAYER;
}

bool Agent::isValidLayer(const unsigned int layer) const
{
    return (layer < behaviors_.size());
}

