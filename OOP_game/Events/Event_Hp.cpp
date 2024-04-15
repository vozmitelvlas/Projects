#include "Event_Hp.h"
#include "../OBJ/Player/Player.h"


void Event_Hp::execute(void *ptr, InfoLog *log_out_info){
    Player* player = (Player*) ptr;
    if(player->get_hp() < 200){
        int new_hp = player->get_hp() + 20;
        if(new_hp > 200){
            new_hp = 200;
        }
        player->set_hp(new_hp);
    }
    Message message(GAME, "you picked up the first aid kit!", log_out_info);
    notify(message);
}
