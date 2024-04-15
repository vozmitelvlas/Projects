#include "CreateEvent.h"

CreateEvent::CreateEvent(Field* field, Player* player){
    this->field = field;
    this->player = player;
}

void CreateEvent::update_events(){
    std::vector<std::vector<Cell>>* array = field->get_field();
    int height = field->get_height();
    int length = field->get_length();
    Event *ev;
    for (int i = 0; i < height; i++){
        int tmp; 
        if(i == 0){
            tmp = 1;
        } 
        else tmp = 0;
        for(int j = tmp; j < length; j++){

            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(1, length+height-7);
            switch(dist(rng)){
                case 1:
                    (*array)[i][j].set_players_events(new Event_Hp());
                    (*array)[i][j].set_info(field->get_info());
                    (*array)[i][j].set_obj(Cell::HP);
                    break;
                case 2:
                    (*array)[i][j].set_players_events(new Event_Damage());
                    (*array)[i][j].set_info(field->get_info());
                    (*array)[i][j].set_obj(Cell::DMG);
                    break;
                case 3:
                    if(i != height - 1 || j != length - 1){
                        (*array)[i][j].set_players_events(new Event_Enemy());
                        (*array)[i][j].set_info(field->get_info());
                        (*array)[i][j].set_obj(Cell::ENEMY);
                    }
                    break;
                case 4:
                    if(i != height - 1 || j != length - 1){
                        (*array)[i][j].set_obj(Cell::BLOCK);
                    }
                    break;
                case 5:
                    if(i != height - 1 || j != length - 1){
                        (*array)[i][j].set_obj(Cell::BLOCK);
                    }
                    break;
                case 6:
                    (*array)[i][j].set_players_events(new Event_Arm());
                    (*array)[i][j].set_info(field->get_info());
                    (*array)[i][j].set_obj(Cell::ARMOR);
                    break;
                case 7:
                default:
                    break;
            }
        }
        (*array)[height - 1][length - 1].set_players_events(new Event_Win());
        (*array)[height - 1][length - 1].set_obj(Cell::END);
        (*array)[height - 1][length - 1].set_info(field->get_info());
    }
}


Event *CreateEvent::create_Event_Hp(){
    return new Event_Hp();
};

Event *CreateEvent::create_Event_Enemy(){
    return new Event_Enemy();
};

Event *CreateEvent::create_Event_Damage(){
    return new Event_Damage();
};

Event *CreateEvent::create_Event_Arm(){
    return new Event_Arm();
};

Event *CreateEvent::create_Event_Win(){
    return new Event_Win();
};

Field *CreateEvent::get_field(){
    return this->field;
};