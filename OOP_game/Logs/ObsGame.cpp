#include "ObsGame.h"


ObsGame::ObsGame(Subject *obj){
    obj->attach(this);
}

void ObsGame::update(Message &message){
    if(message.getType() == GAME){
        Logger logger(message.get_info());
        logger.print(message);
    }
}
