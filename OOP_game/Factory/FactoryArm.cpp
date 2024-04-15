#include "FactoryArm.h"

Event* FactoryArm::CreateEvent(){
    return new Event_Arm;
}
