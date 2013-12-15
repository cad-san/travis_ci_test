#ifndef D_BEHAVIOR_H
#define D_BEHAVIOR_H

#include <boost/shared_ptr.hpp>

class Behavior {
protected:
    unsigned int id_;
public:
    Behavior(const unsigned int behavior_id)
    {
        this->id_ = behavior_id;
    }

    virtual ~Behavior(){}

    virtual void init() = 0;
    virtual void sensing() = 0;
    virtual void perform() = 0;

    virtual bool isActive() const = 0;

    unsigned int getID() const { return id_; }
};

typedef boost::shared_ptr<Behavior> BehaviorPtr;

#endif

