#pragma once
#include <vector>
#include "../Background/Cell.h"
#include "../Player/Player.h"
#include "random"
#include "iostream"

#include "../../Factory/FactoryDamage.h"
#include "../../Factory/FactoryEnemy.h"
#include "../../Factory/FactoryHp.h"
#include "../../Factory/FactoryWin.h"
#include "../../Factory/FactoryArm.h"

#include "../../Info/InfoLog.h"
#include "../../Logging/Subject.h"
#include "../../Logs/ObsError.h"
#include "../../Logs/ObsGame.h"
#include "../../Logs/ObsStatus.h"
#include "../../Events/CreateEvent.h"



class Field: public Subject{
    Player* player;
    int height, length;
    std::vector<std::vector<Cell>> array;
    int x, y;
    bool end;
    InfoLog *log_out_info;
    
public:
    void create_factory();
    Event* create_event(Factory* factory);

    Field(int height, int length, InfoLog *info, Player* player);
    void create_field();

    Field(const Field &field);
 
    Field(Field&& field);
 
    Field &operator=(const Field &field);

    void GoRight();
    void GoLeft();
    void GoUp();
    void GoDown();

    Player* get_player();

    int get_height();
    int get_length();

    void set_player(Player* player);

    std::vector<std::vector<Cell>>* get_field();

    bool get_end();

    void set_events(Player *player);

    InfoLog* get_info();
};