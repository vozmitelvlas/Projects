#include "Message.h"

Message::Message(LVL lvl, const std::string &message, InfoLog* info){
    this->message = message;
    this->lvl = lvl;
    this->info = info;
    switch (lvl) {
        case GAME:
            this->prefix = "GAME: ";
            break;
        case ERROR:
            this->prefix = "ERROR: ";
            break;
        case STATUS:
            this->prefix = "STATUS: ";
            break;
    }
}
    
std::string Message::get_message(){
    return this->message;
}

InfoLog* Message::get_info(){
    return this->info;
}

LVL Message::getType(){
    return this->lvl;
}

std::ostream &operator<<(std::ostream &os, Message &message){
    os << message.get_prefix();
    os << message.get_message();
    os << std::endl;
    return os;
}

std::string Message::get_prefix(){
    return this->prefix;
}