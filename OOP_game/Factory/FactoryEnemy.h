#pragma once
#include "Factory.h"
#include "../Events/Event_Enemy.h"

class FactoryEnemy: public Factory{
public:
    Event* CreateEvent() final;
};