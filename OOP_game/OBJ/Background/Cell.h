#pragma once
#include "../../Events/Event.h"
#include "../Player/Player.h"
#include "../../Logging/Subject.h"
#include "../../Info/Enums.h"

class Cell{
public:
    enum OBJECT{
        STANDARD,
        BLOCK,
        ARMOR,
        HP,
        ENEMY,
        DMG,
        END
    };

    Cell(int x=0, int y=0, bool reaction = false);
    //Cell() = default;
    void cell_reaction();
    bool get_reaction();
    void set_reaction(bool reaction);

    void set_players_events(Event* event);

    

    void use(Player* person);

    void set_obj(OBJECT obj);

    OBJECT get_obj();

    void set_info(InfoLog *log_out_info);

private:
    InfoLog *log_out_info;
    int x, y;
    bool reaction;
    bool wall;
    Event*  event;
    OBJECT object;

};