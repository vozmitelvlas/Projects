#pragma once
#include "../../Info/Enums.h"
class Player{
private:

    int hp;
    int armor;
    int gold;
    int x;
    int y;
    bool end = false;

public:

    Player(int health = 200, int armor = 50, int gold = 0, int x = 0, int y = 0);
    int get_hp();
    void set_hp(int new_hp);

    void set_cache(int new_gold);
    int get_cache();

    int get_x();
    int get_y();

    void set_coords(int x, int y);
    
    int get_armor();
    void set_armor(int new_armor);
    
    void set_end(bool end);
    bool get_end();

    void set_y(int y);
    void set_x(int x);
    
};