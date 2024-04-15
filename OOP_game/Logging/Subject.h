#pragma once
#include "../Logs/Observer.h"
#include "Message.h"
#include <vector>
#include <algorithm>


class Subject{
public:
    void attach(Observer* observer);

    void detach(Observer* observer);

    void notify(Message& message);
private:
    std::vector<Observer*> observers;
};