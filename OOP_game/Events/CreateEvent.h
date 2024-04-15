#pragma once
#include "../OBJ/Player/Player.h"
#include "../OBJ/Background/Field.h"


#include "../Events/Event_Arm.h"
#include "../Events/Event_Damage.h"
#include "../Events/Event_Enemy.h"
#include "../Events/Event_Hp.h"
#include "../Events/Event_Win.h"
#include "random"
class Field;

class CreateEvent{
public:
    CreateEvent(Field* field, Player* player);
    void update_events();

    Event* create_Event_Hp();
    Event* create_Event_Enemy();
    Event* create_Event_Damage();
    Event* create_Event_Arm();
    Event* create_Event_Win();
    Field* get_field();
    
private:
    Field* field;
    Player *player;
};