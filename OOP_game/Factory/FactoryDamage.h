#pragma once
#include "Factory.h"
#include "../Events/Event_Damage.h"

class FactoryDamage: public Factory{
public:
    Event* CreateEvent() override;
};