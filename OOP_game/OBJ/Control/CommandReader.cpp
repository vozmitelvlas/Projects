#include "CommandReader.h"

CommandReader::CommandReader(Config* cfg) {
    this->control_config = cfg;
    new ObsError(this);
}

void CommandReader::begin(InfoLog *log_out_info){
    this->info = log_out_info;
    bool ok = true;
    int height = 10;
    int width = 10;
    char sym;
    std::cout << "Хотите ли вы изменить размеры поля?\n[Y/N]: ";
    std::cin>>sym;
    while(ok){
        if(sym == 'N'){
            this->height = height;
            this->width = width;
            ok = false; 
        }
        else if(sym == 'Y'){
            std::cout<<"Введите Высоту: "; 
            std::cin >> height;
            std::cout<<"Введите ширину: "; 
            std::cin >> width;
            if(height > 0 && width > 0){
                this->height = height;
                this->width = width;
                ok = false;
            }
            else{
                Message message1(ERROR, "incorrect input", log_out_info);
                notify(message1);
            }
        }
        else{
            Message message2(ERROR, "incorrect input", log_out_info);
            notify(message2);
            std::cin>>sym;
        }
    }
}

void CommandReader::set_output() {
    char res;
    std::cout << "Output to: \n";
    std::cout << "1: File\n";
    std::cout << "2: CMD\n";
    std::cout << "3: Everywhere\n";
    std::cin >> res;
    switch (res) {
        case '1':
            this->outputs.push_back(OUTPUT::FILEOUT);
            break;
        case '2':
            this->outputs.push_back(OUTPUT::CMD);
            break;
        default:
            this->outputs.push_back(OUTPUT::FILEOUT);
            this->outputs.push_back(OUTPUT::CMD);
            break;
    }
}

void CommandReader::set_level() {
    char res;
    std::cout << "Logging lvl: \n";
    std::cout << "1: Game\n";
    std::cout << "2: Status\n";
    std::cout << "3: Errors\n";
    std::cin >> res;
    switch (res) {
        case '1':
            this->levels.push_back(LVL::STATUS);
            this->levels.push_back(LVL::GAME);
            this->levels.push_back(LVL::ERROR);
            break;
        case '2':
            this->levels.push_back(LVL::STATUS);
            this->levels.push_back(LVL::GAME);
            break;
        case '3':
            this->levels.push_back(LVL::ERROR);
            break;
    }
}

std::vector <OUTPUT> CommandReader::get_outputs(){
    return this->outputs;
}

std::vector <LVL> CommandReader::get_levels(){
    return this->levels;
}

MOVES CommandReader::read_move(){
    if(!control_config)
        return EXIT;
    char key;
    std::cout << "Move: ";
    std::cin >> key;
    return control_config->get_key(key);
}

void CommandReader::set_difficulty(){
    std::cout << "Choose the difficulty of the game:\n";
    std::cout << "Light - 1\nHard - 2\n";
    char dif;
    std::cin >> dif;
    if (dif == '1'){
        this->difficulty = LIGHT;
    }
    else{
        this->difficulty = HARD;
    }
}
int CommandReader::get_width(){
    return this->width;
}
int CommandReader::get_height(){
    return this->height;
}
DIF CommandReader::get_difficulty(){
    return this->difficulty;
}