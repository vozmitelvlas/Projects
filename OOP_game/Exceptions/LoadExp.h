#pragma once
#include "GameExp.h"

class LoadExp: public GameExp{
public:
    using GameExp::GameExp;
    std::string what() final;

};