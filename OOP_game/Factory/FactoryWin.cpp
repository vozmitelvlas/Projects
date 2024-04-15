#include "FactoryWin.h"


Event* FactoryWin::CreateEvent(){
    return new Event_Win;
}
