#pragma once
#include "Factory.h"
#include "../Events/Event_Hp.h"

class FactoryHp: public Factory{
public:
    Event* CreateEvent() override;
};