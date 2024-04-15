#pragma once
#include "../Control/Controller.h"
#include "../Background/PrintField.h"
#include "../../Info/Enums.h"
#include "../../Logging/Subject.h"
#include "../../Logs/ObsError.h"
#include "../../Logs/ObsGame.h"
#include "../../Logs/ObsStatus.h"

#include "../Config/Config.h"

class CommandReader: public Subject{
private:
    std::vector <OUTPUT> outputs;
    std::vector <LVL> levels;
    Config *control_config;
    DIF difficulty;
    InfoLog *info;
    int height;
    int width;

public:
    CommandReader(Config *cfg = nullptr);

    void begin(InfoLog *log_out_info);
    
    void set_output();
    void set_level();
    std::vector <OUTPUT> get_outputs();
    std::vector <LVL> get_levels();
    MOVES read_move();
    
    void set_difficulty();
    //void start();

    int get_width();
    int get_height();
    DIF get_difficulty();
};