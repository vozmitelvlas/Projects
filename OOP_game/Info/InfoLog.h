#pragma once
#include "Enums.h"
#include <vector>
#include <string>

class InfoLog{
public:
    InfoLog(std::vector <OUTPUT> outputs, std::vector <LVL> lvls);

    std::vector <LVL> get_lvls();
    
    std::vector <OUTPUT> get_outputs();

private:
    std::vector <OUTPUT> outputs;
    std::vector <LVL> lvls;
};