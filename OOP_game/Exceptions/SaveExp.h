#pragma once
#include "GameExp.h"

class SaveExp: public GameExp{
public:
    using GameExp::GameExp;
    std::string what() final;

};