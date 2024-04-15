#include "ObsStatus.h"

ObsStatus::ObsStatus(Subject *obj){
    obj->attach(this);
}

void ObsStatus::update(Message &message){
    if(message.getType() == STATUS){
        Logger logger(message.get_info());
        logger.print(message);
    }
}