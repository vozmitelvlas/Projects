#include "FactoryEnemy.h"

Event* FactoryEnemy::CreateEvent(){
    return new Event_Enemy;
}
