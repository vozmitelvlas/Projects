#pragma once
#include "GameExp.h"

class FileExp: public GameExp{
public:
    using GameExp::GameExp;
    std::string what() final;
};