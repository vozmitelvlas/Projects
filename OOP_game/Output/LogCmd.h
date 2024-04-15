#pragma once
#include "Output.h"
#include <string>
#include <iostream>

class LogCmd: public Output{
public:
    LogCmd() = default;
    void print(Message &message) override;

};