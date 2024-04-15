#pragma once
#include "../Logging/Subject.h"
#include "Observer.h"
class ObsError: public Observer{
public:

    ObsError(Subject *obj);
    
    void update(Message &message) override;

};