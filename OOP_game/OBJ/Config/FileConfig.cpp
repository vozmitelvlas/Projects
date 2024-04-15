#include "FileConfig.h"

FileConfig::FileConfig(const std::string &filename){
    file.open(filename, std::ios_base::in);
}

FileConfig::~FileConfig(){
    file.close();
}

void FileConfig::check_and_read(){
    if (!file.is_open()){
        current_moves = default_moves;
        return;
    }

    std::string str;
    while (getline(file, str)){
        std::string tmp;
        char CHAR = '\0';

        std::istringstream stream(str);
        stream >> tmp >> CHAR;

        if (tmp == "RIGHT=" && CHAR != '\0'){
            current_moves[RIGHT] = CHAR;
        }
        if (tmp == "LEFT=" && CHAR != '\0'){
            current_moves[LEFT] = CHAR;
        }
        if (tmp == "UP=" && CHAR != '\0'){
            current_moves[UP] = CHAR;
        }
        if (tmp == "DOWN=" && CHAR != '\0'){
            current_moves[DOWN] = CHAR;
        }
        if (tmp == "EXIT=" && CHAR != '\0'){
            current_moves[EXIT] = CHAR;
        }
    }
    check_config();
}

