#include "InfoLog.h"

InfoLog::InfoLog(std::vector <OUTPUT> outputs, std::vector <LVL> lvls){
    this->outputs = outputs;
    this->lvls = lvls;
}

std::vector <LVL> InfoLog::get_lvls(){
    return this->lvls;
}

std::vector <OUTPUT> InfoLog::get_outputs(){
    return this->outputs;
}
