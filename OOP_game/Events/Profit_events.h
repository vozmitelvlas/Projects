#pragma once
#include "Event.h"
class Profit_events: public Event{
    
    void execute(void *ptr, InfoLog *log_out_info) = 0;
};