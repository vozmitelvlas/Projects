#pragma once
#include <exception>
#include <string>

class GameExp: public std::exception{
protected:

    std::string message;

public:
    explicit GameExp(std::string);
    virtual std::string what() = 0;
};