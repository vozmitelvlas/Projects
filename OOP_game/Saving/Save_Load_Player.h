#pragma once
#include "../OBJ/Player/Player.h"
#include "fstream"
#include "Hashing.h"

#include "../Exceptions/FileExp.h"
#include "../Exceptions/GameExp.h"
#include "../Exceptions/LoadExp.h"
#include "../Exceptions/SaveExp.h"

class SavePlayer: public Hash{
public:

    void save_data_player(Player* player);
    Player* load_data_player(Player* player);

private:

    std::ofstream file_input;
    std::ifstream file_output;
    std::string filepath = "SAVE.txt";
};