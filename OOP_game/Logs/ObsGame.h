#pragma once
#include "../Logging/Subject.h"
#include "Observer.h"
class ObsGame: public Observer{
public:

    ObsGame(Subject *obj);
    
    void update(Message &message) override;

};