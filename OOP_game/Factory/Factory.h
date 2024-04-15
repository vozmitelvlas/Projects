#pragma once
#include "../Events/Event.h"

class Factory{
public:
    virtual Event* CreateEvent() = 0;
    virtual ~Factory(){};
};