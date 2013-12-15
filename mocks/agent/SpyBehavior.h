#ifndef D_SPY_BEHAVIOR_H
#define D_SPY_BEHAVIOR_H

#include "Behavior.h"

class SpyBehavior : public Behavior
{
private:
    bool activation_;
    bool init_state_;
    bool sensing_state_;
    bool perform_state_;
public:
    explicit SpyBehavior(const unsigned int behavior_id);
    ~SpyBehavior();

    void init();
    void sensing();
    void perform();

    bool isActive() const;

    bool initialized();
    bool sensed();
    bool performed();

    void setActivation(const bool activation);
};

#endif

