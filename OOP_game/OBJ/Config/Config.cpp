#include <iostream>
#include "Config.h"

void Config::check_config(){
    std::vector<char> move_chars;
    for (auto elem: current_moves){
        if (elem.second == '\0'){
            current_moves = default_moves;
            return;
        }
        move_chars.push_back(elem.second);
    }
    
    for (auto elem1: current_moves){
        for (auto elem2: current_moves){
            if(elem1.second == elem2.second && elem1.first != elem2.first){
                current_moves = default_moves;
                return;
            }
        }
    }
}

MOVES Config::get_key(char move) {
    for (auto i: current_moves){
        if (i.second == move){
            return i.first;
        }
    }
    return NOWHERE;
}