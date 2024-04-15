#pragma once
#include "../Logging/Subject.h"
#include "Observer.h"
class ObsStatus: public Observer{
public:

    ObsStatus(Subject *obj);
    
    void update(Message &message) override;

};