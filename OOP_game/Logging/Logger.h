#pragma once
#include "../Info/InfoLog.h"
#include "Message.h"
#include <vector>
#include "../Output/Output.h"

class Logger {
public:
    Logger(InfoLog* info);
    void print(Message &message);

private:
    std::vector<Output *> outs;
    std::vector<LVL> lvls;
};
