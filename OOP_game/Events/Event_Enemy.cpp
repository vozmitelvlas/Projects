#include "Event_Enemy.h"
#include "../OBJ/Player/Player.h"


void Event_Enemy::execute(void *ptr, InfoLog *log_out_info){
    
    Player* player = (Player*) ptr;
    int new_hp = player->get_hp() - 49;
    
    if(player->get_armor() > 15){
        player->set_armor(player->get_armor() - 15);
    }

    else if(player->get_armor() > 0){
        player->set_armor(player->get_armor() - player->get_armor());
    }

    int gold = player->get_cache() + 15;

    player->set_cache(gold);
    player->set_hp(new_hp);

    Message message(GAME, "Battle with the enemy!", log_out_info);
    notify(message);
}
