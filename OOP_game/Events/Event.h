#pragma once
#include "../Info/InfoLog.h"
#include "../Logging/Subject.h"
#include "../Logs/ObsError.h"
#include "../Logs/ObsGame.h"
#include "../Logs/ObsStatus.h"

#include "../Logging/Message.h"


class Event: public Subject{
public:
    virtual void execute(void *ptr, InfoLog *log_out_info) = 0;
    
    virtual ~Event(){};
};