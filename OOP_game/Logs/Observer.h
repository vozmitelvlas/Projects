#pragma once
#include "../Logging/Message.h"
#include "../Logging/Logger.h"

class Observer{
public:
    virtual void update(Message &message) = 0;
};