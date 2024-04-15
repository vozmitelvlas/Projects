#pragma once
#include "../../OBJ/Background/Field.h"
#include "../../OBJ/Player/Player.h"
#include "../../Events/CreateEvent.h"
#include "random"

template<DIF enemy>
class Enemy{
public:
    void operator()(CreateEvent& create_events){
        Field* field = create_events.get_field();
        std::vector<std::vector<Cell>>* array = field->get_field();
        int height = field->get_height();
        int length = field->get_length();
        for(int i = 0; i < height; i++){
            int tmp; 
            if(i == 0) tmp = 1;
            else tmp = 0;
            for(int j = tmp; j < length; j++){
                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_int_distribution<std::mt19937::result_type> dist(1, length+height-(length+height)%enemy);
                if (dist(rng) == 1){
                    if((i != height - 1 || j != length - 1) && (i != height - 1 || j != 0)){
                        (*array)[i][j].set_players_events(create_events.create_Event_Enemy());
                        (*array)[i][j].set_info(field->get_info());
                        (*array)[i][j].set_obj(Cell::ENEMY);
                    }
                }
            }
        }
    }
};