#pragma once
#include "Profit_events.h"

class Event_Hp: public Profit_events{
public:
    void execute(void *ptr, InfoLog *log_out_info) override;
};