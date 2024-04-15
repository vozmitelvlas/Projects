#include "LogFile.h"

LogFile::LogFile(std::string name){
    file.open(name, std::ios_base::out | std::ios_base::app);
}

void LogFile::print(Message &message){
    if(file.is_open()){
        file << message;
    }
}

LogFile::~LogFile(){
    file.close();
}