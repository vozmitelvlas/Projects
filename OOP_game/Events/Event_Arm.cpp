#include "Event_Arm.h"
#include "../OBJ/Player/Player.h"

void Event_Arm::execute(void *ptr, InfoLog *log_out_info){
    Player* player = (Player*) ptr;
    if(player->get_armor() < 70){

        int new_armor = player->get_armor() + 20;
        if(new_armor > 70){
            player->set_armor(70);
            return;
        }
        player->set_armor(new_armor);
    }
    Message message(GAME, "you picked up the armor!", log_out_info);
    notify(message);
}