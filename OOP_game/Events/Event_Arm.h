#pragma once
#include "Profit_events.h"


class Event_Arm: public Profit_events{
public:
    void execute(void *ptr, InfoLog *log_out_info) override;
};