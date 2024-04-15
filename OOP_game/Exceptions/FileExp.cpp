#include "FileExp.h"

std::string  FileExp::what(){
    return "Error open file state because of:\n" + message;
}