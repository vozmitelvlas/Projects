#include "SaveExp.h"

std::string SaveExp::what(){
    return "Error save game because of\n" + message;
}