#include "PrintField.h"

#include <iostream>

void PrintField::print(){
    std::vector<std::vector<Cell>>* array = Field::get_field();
    std::cout << "\n";
    for (int i = 0; i < Field::get_height(); i++){
        for (int j = 0; j < Field::get_length(); j++) {
            if ((*array)[i][j].get_reaction()) {
                std::cout << "X" << "    ";
            }
            else if((*array)[i][j].get_obj() == Cell::BLOCK){
                std::cout << "#" << "    ";
            }
            else if((*array)[i][j].get_obj() == Cell::ENEMY){
                std::cout << "@" << "    ";
                std::cout << (*array)[i][j].get_obj();
            }
            else
                std::cout << "." << "    ";
        }
        if (i == 0){
            std::cout << "      health == " << Field::get_player()->get_hp();
        }
        if (i == 1){
            std::cout << "      cache == " << Field::get_player()->get_cache();
        }
        if (i == 2){
            std::cout << "      armor == " << Field::get_player()->get_armor();
        }
        std::cout << '\n';
        std::cout << '\n';
    }
}

bool PrintField::get_end(){
    return Field::get_end();
}
