#pragma once
#include "Factory.h"
#include "../Events/Event_Win.h"


class FactoryWin: public Factory{
public:
    Event* CreateEvent() override;
};