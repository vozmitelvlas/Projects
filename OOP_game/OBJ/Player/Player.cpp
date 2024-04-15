#include "../Player/Player.h"

Player::Player(int health, int armor, int gold, int x, int y): hp(health), gold(gold), armor(armor), x(x), y(y){};

int Player::get_hp(){
    return hp;
}
void Player::set_hp(int new_hp){
    this->hp = new_hp;
}

void Player::set_cache(int new_gold){
    this->gold = new_gold;
}

int Player::get_x(){
    return x;
}
int Player::get_y(){
    return y;
}
void Player::set_coords(int x, int y){
    this->x = x;
    this->y = y;
}

int Player::get_armor(){
    return armor;
}
void Player::set_armor(int new_armor){
    this->armor = new_armor;
}
int Player::get_cache(){
    return gold;
}
void Player::set_end(bool end){
    this->end = end;
}
bool Player::get_end(){
    return end;
}

void Player::set_y(int y){
    this->y = y;
}
void Player::set_x(int x){
    this->x = x;
}

