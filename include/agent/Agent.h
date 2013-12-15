#ifndef D_AGENT_H
#define D_AGENT_H

#include "Runner.h"
#include "Behavior.h"

#include <vector>
#include <boost/shared_ptr.hpp>

class Agent : public Runner
{
public:
    static const int INVALID_LAYER;
private:
    std::vector< BehaviorPtr > behaviors_;

    int convertFromIDtoLayer(const unsigned int id) const;
    bool isValidLayer(const unsigned int layer) const;
public:
    Agent();
    virtual ~Agent();

    virtual void init();
    virtual void step();

    int getNumBehaviors() const;
    void addBehavior(const BehaviorPtr& new_behavior);
    void removeBehaviorAt(const unsigned int layer);
    const BehaviorPtr getBehaviorAt(const unsigned int layer) const;
    const BehaviorPtr getBehaviorByID(const unsigned int id) const;
};

typedef boost::shared_ptr<Agent> AgentPtr;

#endif
