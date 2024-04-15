#pragma once
#include "../Control/CommandReader.h"
#include "../Background/PrintField.h"
#include "../../Info/Enums.h"
#include "../../Info/InfoLog.h"
#include "../../Logging/Subject.h"
#include "../../Logs/ObsGame.h"
#include "../../Logs/ObsStatus.h"

#include "../../CreateField/Rules/Wall.h"
#include "../../CreateField/Rules/Enemy.h"
#include "../../CreateField/Rules/Arm.h"
#include "../../CreateField/Rules/Hp.h"
#include "../../CreateField/Rules/Trap.h"
#include "../../CreateField/Rules/Win.h"
#include "../../CreateField/FieldGenerator.h"

#include "../../Saving/Save_Load_Player.h"
#include "../../Saving/Save_Load_Field.h"

#include "../../Exceptions/FileExp.h"
#include "../../Exceptions/GameExp.h"
#include "../../Exceptions/LoadExp.h"
#include "../../Exceptions/SaveExp.h"

class CommandReader;
class Controller: public Subject{
public:

    Controller(InfoLog *log_out_info, CommandReader* read, DIF difficulty, int width, int height);
    void move();
    void start();

    Player* copy(Player* player1, Player* player2);

private:
    Player* cplayer;
    PrintField* field;
    Player* player;
    DIF difficulty;
    int width;
    int height;
    CommandReader *read;
    InfoLog *log_out_info;
    SaveField* Sfield;
    SavePlayer* Splayer;
};