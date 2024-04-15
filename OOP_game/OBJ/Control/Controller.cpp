#include "../Control/Controller.h"


Controller::Controller(InfoLog *log_out_info, CommandReader* read, DIF difficulty, int width, int height){
    this->player = new Player(200, 50, 0, 0, 0);
    this->cplayer = new Player(200, 50, 0, 0, 0);
    this->height = height;
    this->width = width;
    this->difficulty = difficulty;
    this->log_out_info = log_out_info;
    this->read = read;
    this->Sfield = new SaveField();
    this->Splayer = new SavePlayer();
    new ObsGame(this);
    new ObsStatus(this);
}

void Controller::start(){
    Generator* generator;
    
    if (difficulty == LIGHT){
        generator = new FieldGenerator<Win<LIGHT>, Enemy<LIGHT>, Wall<LIGHT>, Arm<LIGHT>, Hp<LIGHT>, Trap<LIGHT>>;
    }
    else{
        generator = new FieldGenerator<Win<HARD>, Enemy<HARD>, Wall<HARD>, Arm<HARD>, Hp<HARD>, Trap<HARD>>;
    }
    this->field = generator->fill(height, width, this->log_out_info, this->player);
    move();
}

void Controller::move(){
    system("clear");
    this->field->print();
    Message message1(GAME, "Changing the position of the player", log_out_info);
    Message message2(STATUS, "Game started!", log_out_info);
    notify(message2);
    MOVES move = read->read_move();
    while(move != MOVES::EXIT && !this->field->get_end()){

        switch (move)
        {
        case MOVES::UP:
            system("clear");
            this->field->GoUp();
            notify(message1);
            this->field->print();
            break;
        case MOVES::DOWN:
            system("clear");
            this->field->GoDown();
            notify(message1);
            this->field->print();
                     
            break;
        case MOVES::RIGHT:
            system("clear");
            this->field->GoRight();
            notify(message1);
            this->field->print();
            
            break;
        case MOVES::LEFT:
            system("clear");
            this->field->GoLeft();
            notify(message1);
            this->field->print();
            break;
        case MOVES::SAVE:
            char answer;
            std::cout << "Are u sure u want to save and quit the current game?(Y/N): "; std::cin >> answer;
            if (answer == 'Y'){
                system("clear");
                try{
                    this->Splayer->save_data_player(player);
                    this->Sfield->save_data_field(field);
                    
                    Message message(GAME, "The download was successful!", log_out_info);
                    notify(message);
                }
                catch(SaveExp& se){
                    Message message(GAME, "could not save game", log_out_info);
                    notify(message);      
                }
                catch(FileExp& fe){
                    Message message(GAME, fe.what(), log_out_info);
                    notify(message);
                }
                catch(...){
                    Message message(GAME, "unknown error restore gamer", log_out_info);
                    notify(message);
                }
            }
            else{
                system("clear");
                this->field->print();
                break;
            }
            this->field->print();
            break;
        case MOVES::LOAD:
            this->cplayer = copy(this->cplayer, this->player);
            std::cout << "Are u sure u want to load the last save game?(Y/N): "; std::cin >> answer;

            if (answer == 'Y'){
                system("clear");
                try{
                    this->player = this->Splayer->load_data_player(this->player);
                    this->field = this->Sfield->load_data_field(this->player, this->log_out_info);

                    Message message(GAME, "The data has been successfully uploaded!", log_out_info);
                    notify(message);

                }
                catch(LoadExp& le){
                    this->player = copy(this->player, this->cplayer);
                    this->field->set_player(this->player);
                    Message message(GAME, le.what(), log_out_info);
                    notify(message);
                }
                catch(FileExp& fe){
                    system("clear");
                    Message message(GAME, fe.what(), log_out_info);
                    notify(message);
                }
                catch(...){
                    Message message(GAME, "unknown error", log_out_info);
                    notify(message);
                }
                this->field->print();
            }
            else{
                system("clear");
                this->field->print();
                break;
                
            }
            break;

        default:
            break;
        }
        move = read->read_move();  
    }
    if(field->get_end()){
        Message message3(STATUS, "Game over\n", log_out_info);
        notify(message3);
    }
}


Player* Controller::copy(Player* player1, Player* player2){
    player1->set_hp(player2->get_hp());
    player1->set_armor(player2->get_armor());
    player1->set_cache(player2->get_cache());
    player1->set_x(player2->get_x());
    player1->set_y(player2->get_y());

    return player1;
}