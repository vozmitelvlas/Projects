#include "Factory.h"
#include "../Events/Event_Arm.h"

class FactoryArm: public Factory{
public:
    Event* CreateEvent() override;
};