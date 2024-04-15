#pragma once
#include <map>
#include "../../Info/Enums.h"
#include <vector>

class Config{
public:
    virtual ~Config() = default;
    virtual void check_and_read() = 0;
    virtual MOVES get_key(char move);

protected:
    void check_config();

    std::map<MOVES, char> current_moves = {
            {MOVES::UP,    '\0'},
            {MOVES::DOWN,  '\0'},
            {MOVES::LEFT,  '\0'},
            {MOVES::RIGHT, '\0'},
            {MOVES::SAVE, '\0'},
            {MOVES::LOAD, '\0'},
            {MOVES::EXIT,  '\0'}
    };
    const std::map<MOVES, char> default_moves = {
            {MOVES::UP,    'w'},
            {MOVES::DOWN,  's'},
            {MOVES::LEFT,  'a'},
            {MOVES::RIGHT, 'd'},
            {MOVES::SAVE, 'e'},
            {MOVES::LOAD, 'l'},
            {MOVES::EXIT,  'q'}
    };
};