#include "LoadExp.h"

std::string  LoadExp::what() {
    return "Error load state because of:\n" + message;
}