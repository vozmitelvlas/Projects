#pragma once
#include "../OBJ/Background/Field.h"
#include "../OBJ/Player/Player.h"
#include "../OBJ/Background/Cell.h"
#include "../Info/InfoLog.h"
#include "../OBJ/Background/PrintField.h"
#include "fstream"
#include "../Events/CreateEvent.h"
#include "Hashing.h"

#include "../Exceptions/FileExp.h"
#include "../Exceptions/GameExp.h"
#include "../Exceptions/LoadExp.h"
#include "../Exceptions/SaveExp.h"

#include "../Logging/Subject.h"


class SaveField: public Hash{
public:

    void save_data_field(Field* field);
    PrintField* load_data_field(Player* player, InfoLog* log_out_info); 

private:

    std::ofstream file_input;
    std::ifstream file_output;
    std::string filepath = "SAVE.txt";
};