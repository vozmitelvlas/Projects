#include "FactoryDamage.h"



Event* FactoryDamage::CreateEvent(){
    return new Event_Damage;
}
