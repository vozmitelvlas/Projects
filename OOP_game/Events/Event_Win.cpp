#include "Event_Win.h"
#include "../OBJ/Player/Player.h"
#include <iostream>

void Event_Win::execute(void *ptr, InfoLog *log_out_info){
    Player* player = (Player*) ptr;
    if(player->get_cache() > 40 && player->get_hp() > 0){
        player->set_end(true);
    }
    Message message(GAME, "You win!", log_out_info);
    notify(message);
    
}
