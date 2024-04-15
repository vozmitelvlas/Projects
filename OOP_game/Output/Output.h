#pragma once
class Message;

#include "../Logging/Message.h"

class Output{

public:
    virtual ~Output() = default;

    virtual void print(Message &message) = 0;
};