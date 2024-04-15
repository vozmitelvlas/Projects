#include "Cell.h"


Cell::Cell(int x, int y, bool reaction): x(x), y(y), reaction(reaction){
    this->event = nullptr;
};
void Cell::cell_reaction(){
    if(reaction)
        reaction = false;
    else 
        reaction = true;
}
bool Cell::get_reaction(){
    return reaction;
}
void Cell::set_reaction(bool reaction){
    this->reaction = reaction;
}

void Cell::set_players_events(Event* event){
    if(this->event == nullptr){
        this->event = event;
    }
}

void Cell::use(Player* ptr){
    
    if(event != nullptr){
        new ObsGame(this->event);
        event->execute(ptr, log_out_info);
        event = nullptr;
    } 
}
void Cell::set_obj(OBJECT obj){
    this->object = obj;
}

Cell::OBJECT Cell::get_obj(){
    return object;
}

void Cell::set_info(InfoLog *log_out_info){
    this->log_out_info = log_out_info;
}
