#include "Logger.h"
#include "../Info/Enums.h"
#include "../Output/LogFile.h"
#include "../Output/LogCmd.h"

void Logger::print(Message &message) {
    for (auto elem1: outs) {
        for(auto elem2: lvls){
            if(message.getType() == elem2){
                elem1->print(message);
            }
        }        
    }
}

Logger::Logger(InfoLog *info) {
    for (auto elem: info->get_outputs()) {
        switch (elem) {
            case FILEOUT:
                outs.push_back(new LogFile("LOGS.txt"));
                break;
            case CMD:
                outs.push_back(new LogCmd);
                break;
        }
    }
    this->lvls = info->get_lvls();
}