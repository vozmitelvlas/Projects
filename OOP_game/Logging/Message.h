#pragma once

class LogOutInfo;

#include <ostream>
#include <string>
#include "../Info/Enums.h"
#include "../Info/InfoLog.h"

class Message{
public:
    Message(LVL lvl, const std::string &message, InfoLog* info);
    
    std::string get_message();

    InfoLog* get_info();

    LVL getType();

    friend std::ostream &operator<<(std::ostream &os, Message &message);

    std::string get_prefix();

private:
    LVL lvl;
    std::string message;
    InfoLog *info;
    std::string prefix;
};