#pragma once
#include "Game_events.h"

class Event_Win: public Game_events{
    void execute(void *ptr, InfoLog *log_out_info) override;
};