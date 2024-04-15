#include "Field.h"


Event* Field::create_event(Factory* factory){
    return factory->CreateEvent();
}

Field::Field(int height, int length, InfoLog *info, Player* player){
    this->player = player;
    this->height = height;
    this->length = length;
    this->log_out_info = info;
}
void Field::create_field(){
    for (int i = 0; i < height; i++){
        array.push_back(std::vector<Cell>(length));
        for (int j = 0; j < length; j++){
            array[i][j] = Cell(i, j);
            array[i][j].set_obj(Cell::STANDARD);
        }
    }
    x = this->player->get_x();
    y = this->player->get_y();
    array[y][x].set_reaction(true);

    //set_events(this->player);
}

 void Field::set_events(Player *player){
    CreateEvent build(this, player);
    build.update_events(); 
} 

Field::Field(const Field &field){
    height = field.height;
    length = field.length;
    x = field.x;
    y = field.y;
    for (int i = 0; i < height; i++){
        array.push_back(std::vector<Cell>(length));
        for (int j = 0; j < length; j++){
            array[i][j] = Cell(i, j);
        }
    }
    for (int i = 0; i < height; i++){
        for (int j = 0; j < length; j++) {
            array[i][j] = field.array[i][j]; 
        }
    }
}

Field::Field(Field&& field){
    std::swap(height, field.height);
    std::swap(length, field.length);
    std::swap(x, field.x);
    std::swap(y, field.y);
    for (int i = 0; i < height; i++){
        for (int j = 0; j < length; j++){
            std::swap(array[i][j], field.array[i][j]);
        }
    }
}

Field &Field::operator=(const Field &field){
    if (this != &field){
        for (int i = 0; i < length; i++){
            array[i].clear();
        }
        array.clear();

        height = field.height;
        length = field.length;
        x = field.x;
        y = field.y;
        for (int i = 0; i < field.height; i++){
            array.push_back(std::vector<Cell>(length));
            for (int j = 0; j < field.length; j++){
                array[i][j] = Cell(i, j);
            }
        }
            
        for (int i = 0; i < height; i++){
            array[i].assign(field.array[i].begin(), field.array[i].end());
        }
    }
    return *this;
}

void Field::GoRight(){
    array[y][x].cell_reaction();
    x++;
    if(x == length){
        x = 0;
    }
    if(array[y][x].get_obj() == Cell::BLOCK){
        if(x == 0){        //edge
            x = length - 1;
        }
        else{
            x--;
        }                //edge
        array[y][x].cell_reaction();
        return;
    }
    array[y][x].cell_reaction();
    player->set_coords(x, y);
    array[y][x].use(player);
    
    if(array[y][x].get_obj() == Cell::ENEMY){
        array[y][x].set_obj(Cell::STANDARD);
        array[y][x].set_players_events(nullptr);
    }
    if(this->player->get_hp() <= 0){
        end = true;
    }
    if(player->get_end()){
        end = true;
    }
}
void Field::GoLeft(){
    array[y][x].cell_reaction();
    x--;
    if(x < 0){
        x = length - 1;
    }
    if(array[y][x].get_obj() == Cell::BLOCK){ // edge
        if(x == length - 1){
            x = 0;
        }
        else{
            x++;
        }                      // edge
        array[y][x].cell_reaction();
        return;
    }
    
    array[y][x].cell_reaction();
    player->set_coords(x, y);

    array[y][x].use(player);
    if(array[y][x].get_obj() == Cell::ENEMY){
        array[y][x].set_obj(Cell::STANDARD);
        array[y][x].set_players_events(nullptr);
    }
    if(this->player->get_hp() <= 0){
        end = true;
    }
    if(player->get_end()){
        end = true;
    } 
}
void Field::GoUp(){
    array[y][x].cell_reaction();
    y--;
    if(y < 0){
        y = height - 1;
    }
    if(array[y][x].get_obj() == Cell::BLOCK){ 
        if(y == height - 1){// edge
            y = 0;
        }
        else{
            y++;
        }// edge                  
        array[y][x].cell_reaction();
        return;
    }
    array[y][x].cell_reaction();
    player->set_coords(x, y);

    array[y][x].use(player);
    if(array[y][x].get_obj() == Cell::ENEMY){
        array[y][x].set_obj(Cell::STANDARD);
        array[y][x].set_players_events(nullptr);
    }
    if(this->player->get_hp() <= 0){
        end = true;
    }
    if(player->get_end()){
        end = true;
    }
}
void Field::GoDown(){
    array[y][x].cell_reaction();
    y++;
    if(y == height){
        y = 0;
    }
    if(array[y][x].get_obj() == Cell::BLOCK){
        if(y == 0){// edge
            y = height - 1;
        }
        else{
            y--;
        }// edge               
        array[y][x].cell_reaction();
        return;
    }
    array[y][x].cell_reaction();
    player->set_coords(x, y);

    array[y][x].use(player);
    if(array[y][x].get_obj() == Cell::ENEMY){
        array[y][x].set_obj(Cell::STANDARD);
        array[y][x].set_players_events(nullptr);
    }
    if(this->player->get_hp() <= 0){
        end = true;
    }
    if(player->get_end()){
        end = true;
    }
}

Player* Field::get_player(){
    return this->player;
}

int Field::get_height(){
    return height;
}

int Field::get_length(){
    return length;
}

std::vector<std::vector<Cell>>* Field::get_field(){
    return &array;
}

bool Field::get_end(){
    return end;
}

InfoLog* Field::get_info(){
    return this->log_out_info;
}

void Field::set_player(Player* player){
    this->player = player;
}