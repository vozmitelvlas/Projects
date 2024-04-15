#include "ObsError.h"


ObsError::ObsError(Subject *obj){
    obj->attach(this);
}

void ObsError::update(Message &message){
    if(message.getType() == ERROR){
        Logger logger(message.get_info());
        logger.print(message);
    }
}
