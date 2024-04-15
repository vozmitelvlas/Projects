#pragma once
#include "../../OBJ/Background/Field.h"
#include "../../OBJ/Player/Player.h"
#include "../../Events/CreateEvent.h"

template<DIF win>
class Win{
public:
    void operator()(CreateEvent& create_events){
        Field* field = create_events.get_field();
        std::vector<std::vector<Cell>>* array = field->get_field();
        int height = field->get_height();
        int length = field->get_length();
        if (win==LIGHT){
            (*array)[height - 1][length - 1].set_players_events(create_events.create_Event_Win());
            (*array)[height - 1][length - 1].set_obj(Cell::END);
            (*array)[height - 1][length - 1].set_info(field->get_info());

            (*array)[height - 1][0].set_players_events(create_events.create_Event_Win());
            (*array)[height - 1][0].set_obj(Cell::END);
            (*array)[height - 1][0].set_info(field->get_info());
        }
        else{
            (*array)[height - 1][length - 1].set_players_events(create_events.create_Event_Win());
            (*array)[height - 1][length - 1].set_obj(Cell::END);
            (*array)[height - 1][length - 1].set_info(field->get_info());
        }
        
    }
};