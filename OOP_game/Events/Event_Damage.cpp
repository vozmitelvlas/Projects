#include "Event_Damage.h"
#include "../OBJ/Player/Player.h"


void Event_Damage::execute(void *ptr, InfoLog *log_out_info){
    Player* player = (Player*) ptr;

    if(player->get_armor() > 15){
        player->set_armor(player->get_armor() - 15);
        player->set_hp(player->get_hp() - 20);

        Message message(GAME, "stepped on a trap!", log_out_info);
        notify(message);
        return;
    }   
    else if(player->get_armor() > 0){
        int cur_ar = player->get_armor();
        player->set_armor(player->get_armor() - player->get_armor());
        player->set_hp(player->get_hp() - (30 - cur_ar));

        Message message(GAME, "stepped on a trap!", log_out_info);
        notify(message);
        return;
    }
    else{
        int new_hp = player->get_hp() - 25;
        player->set_hp(new_hp);
        Message message(GAME, "stepped on a trap!", log_out_info);
        notify(message);
    }
    
} 
