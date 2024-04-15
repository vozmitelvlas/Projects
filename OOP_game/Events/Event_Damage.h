#pragma once
#include "Waste_events.h"

class Event_Damage: public Waste_events{
public:
    void execute(void *ptr, InfoLog *log_out_info) override;
};