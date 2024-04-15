#include "FactoryHp.h"

Event* FactoryHp::CreateEvent(){
    return new Event_Hp;
}
