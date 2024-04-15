#pragma once
#include "Event.h"
class Waste_events: public Event{
 
   void execute(void *ptr, InfoLog *log_out_info) = 0;

};