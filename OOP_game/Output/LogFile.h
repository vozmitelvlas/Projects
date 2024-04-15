#pragma once
#include "Output.h"
#include <fstream>
#include <string>

class LogFile: public Output{

public:

    LogFile(std::string name);
    
    void print(Message &message) override;

    ~LogFile();

private:
    std::ofstream file;
};