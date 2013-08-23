#ifndef D_SPY_BEHAVIOR_H
#define D_SPY_BEHAVIOR_H

#include "Behavior.h"

class SpyBehavior : public Behavior
{
private:
    bool activation;
    bool init_state;
    bool sensing_state;
    bool perform_state;
public:
    explicit SpyBehavior(const unsigned int id);
    ~SpyBehavior();

    void init();
    void sensing();
    void perform();

    const bool isActive() const;

    bool initialized();
    bool sensed();
    bool performed();

    void setActivation(const bool activation);
};

#endif

