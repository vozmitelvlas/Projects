#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <typeinfo>
#include "random"


enum {
    ARMOR = 70,
    GOLD = 0,
    HEALTH = 200
};

class Player{
    int hp;
    int armor;
    int gold;
    int x;
    int y;
    bool end;
public:
    Player(int x = 0, int y = 0, bool end = false): hp(HEALTH), gold(GOLD), armor(ARMOR), x(x), y(y), end(end){};
    int get_hp(){
        return hp;
    }
    void set_hp(int new_hp){
        this->hp = new_hp;
    }

    void set_cache(int new_gold){
        this->gold = new_gold;
    }

    int get_x(){
        return x;
    }
    int get_y(){
        return y;
    }
    void set_coords(int x, int y){
        this->x = x;
        this->y = y;
    }

    int get_armor(){
        return armor;
    }
    void set_armor(int new_armor){
        this->armor = new_armor;
    }
    int get_cache(){
        return gold;
    }
    void set_end(bool end){
        this->end = end;
    }
    bool get_end(){
        return end;
    }
    
};

class Event{
public:
    virtual void execute(void *ptr) = 0;
};

class Profit_events: public Event{
    void execute(void *ptr){
    }
};

class Waste_events: public Event{
    void execute(void *ptr){ 
    }
};

class Game_events: public Event{
    void execute(void *ptr){   
    }
};

class Event_Enemy: public Waste_events{
    void execute(void *ptr) override{
        Player* player = (Player*) ptr;
        int new_hp = player->get_hp() - 50;
        if(player->get_armor() > 15){
            player->set_armor(player->get_armor() - 15);
        }
        else if(player->get_armor() > 0){
            player->set_armor(player->get_armor() - player->get_armor());
        }
        int gold = player->get_cache() + 15;

        player->set_cache(gold);
        player->set_hp(new_hp);
    }
};

class Event_Damage: public Waste_events{
public:
    void execute(void *ptr) override{
        Player* player = (Player*) ptr;

        if(player->get_armor() > 15){
            player->set_armor(player->get_armor() - 15);
            player->set_hp(player->get_hp() - 15);
            return;
        }   
        else if(player->get_armor() > 0){
            int cur_ar = player->get_armor();
            player->set_armor(player->get_armor() - player->get_armor());
            player->set_hp(player->get_hp() - (30 - cur_ar));
            return;
        }
        else{
            int new_hp = player->get_hp() - 25;
            player->set_hp(new_hp);
        }
        
    }
};

class Event_Hp: public Profit_events{
    void execute(void *ptr) override{
        Player* player = (Player*) ptr;
        if(player->get_hp() < 200){
            int new_hp = player->get_hp() + 20;
            int new_ar = player->get_armor() + 5;
            if(new_hp > 200){
                new_hp = 200;
            }
            player->set_hp(new_hp);
            player->set_armor(new_ar);
        }  
    }
};

class Event_Win: public Game_events{
    void execute(void *ptr){
        Player* player = (Player*) ptr;
        if(player->get_cache() > 50 && player->get_hp() > 0){
            player->set_end(true);
            std::cout << "Win!";
        }
    }
};


class Factory{
public:
    virtual Event* CreateEvent() = 0;
};

class FactoryEnemy: public Factory{
public:
    Event* CreateEvent(){
        return new Event_Enemy;
    }
};

class FactoryHp: public Factory{
public:
    Event* CreateEvent(){
        return new Event_Hp;
    }
};

class FactoryDamage: public Factory{
public:
    Event* CreateEvent(){
        return new Event_Damage;
    }
};

class FactoryWin: public Factory{
public:
    Event* CreateEvent(){
        return new Event_Win;
    }
};








class CommandReader{
    public:
    void read(){
        enter = getchar();
    }
    char get_enter(){
        return enter;
    }
    private:
    char enter;
};


class Cell{
    int x, y;
    bool reaction;
    bool wall;
    Event*  event;
    bool enemy;
public:
    
    Cell(int x=0, int y=0, bool reaction = false, bool wall = false, bool enemy = false, bool event = false): x(x), y(y), reaction(reaction), wall(wall), enemy(enemy){};
    void cell_reaction(){
        if(reaction)
            reaction = false;
        else 
            reaction = true;
    }
    bool get_reaction(){
        return reaction;
    }
    void set_reaction(bool reaction){
        this->reaction = reaction;
    }

    bool get_wall(){
        return wall;
    }
    void set_wall(bool wall){
        this->wall = wall;
    }
    
    void set_enemy(bool enemy){
        this->enemy = enemy;
    }
    bool get_enemy(){
            return enemy;
    }
    void set_players_events(Event* event){
        this->event = event;
    }

    /* void set_field_events(Waste_events* event){
        this->event = event;
    } */
    
    void use(Player* person){
        if(event != nullptr ){
            event->execute(person);
            if(x + y != 18){
                event = nullptr;
            }
        } 
    }

};

class Field{
private:
public:
    Player player;
    int height, length;
    std::vector<std::vector<Cell>> array;
    int x, y;
    bool end;
    
    Event* get_event(Factory* factory){
        return factory->CreateEvent();
    }

    Field(int height, int length) : height(height), length(length){
        for (int i = 0; i < height; i++){
            array.push_back(std::vector<Cell>(length));
            for (int j = 0; j < length; j++){
                array[i][j] = Cell(i, j);
            }
        }
        x = 0;
        y = 0;
        array[x][y].set_reaction(true);
        array[x][y].set_wall(false);
        for(int i = 0; i < height; i++){
            for(int j = 0; j < length; j++){
                if(i*j%5 == 3){
                    array[i][j].set_wall(true);
                }   
            }
        }
    };

    Field(){
        height = 10;
        length = 10;
        end = false;
        for (int i = 0; i < height; i++){
            array.push_back(std::vector<Cell>(length));
            for (int j = 0; j < length; j++){
                array[i][j] = Cell(i, j);
            }
        }
        x = 0;
        y = 0;
        array[x][y].set_reaction(true);
        array[x][y].set_wall(false);
        for(int i = 0; i < height; i++) {
            int tmp; 
            if(i == 0){
                tmp = 1;
            } 
            else tmp = 0;

            for(int j = tmp; j < length; j++) {
                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_int_distribution<std::mt19937::result_type> dist(1,13);

                Factory* FhP = new FactoryHp;
                Factory* FDm = new FactoryDamage;
                Factory* FEn = new FactoryEnemy;


                Event* eventHp = get_event(FhP);
                Event* eventDmg = get_event(FDm);
                Event* eventEnemy = get_event(FEn);
                

                switch(dist(rng)) {
                    case 1:
                        array[i][j].set_players_events(eventHp);
                        break;
                    case 2:
                        array[i][j].set_players_events(eventDmg);
                        break;
                    case 3:
                        if(i != height - 1 || j != length - 1){
                            array[i][j].set_enemy(true);
                            array[i][j].set_players_events(eventEnemy);
                        }
                        break;
                    case 4:
                        if(i != height - 1 || j != length - 1){
                            array[i][j].set_wall(true);
                        }
                        break;
                    case 5:
                        if(i != height - 1 || j != length - 1){
                                array[i][j].set_wall(true);
                        }
                        break;
                    case 6:
                        break;
                    default:
                        break;
                }
            }
            Event* eventExit = new Event_Win;
            array[height - 1][length - 1].set_players_events(eventExit);
        }
    }

    Field(const Field &field){
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
 
    Field(Field&& field){
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
 
    Field &operator=(const Field &field){
        if (this != &field) {
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

    void GoRight(){
        array[y][x].cell_reaction();
        x++;
        if(x == length){
            x = 0;
        }
        if(array[y][x].get_wall()){
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
        player.set_coords(x, y);
        
        array[y][x].use(&player);
        
        if(array[y][x].get_enemy()){
            array[y][x].set_enemy(false);
            array[y][x].set_players_events(nullptr);
        }
        if(player.get_hp() <= 0){
            end = true;
            std::cout<< "Game over";
        }

        if( (x == length - 1) && (y == height - 1) && (player.get_end()) ){
            end = true;
        }

        
    }
    void GoLeft(){
        array[y][x].cell_reaction();
        x--;
        if(x < 0){
            x = length - 1;
        }
        if(array[y][x].get_wall()){ // edge
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
        player.set_coords(x, y);

        array[y][x].use(&player);
        if(array[y][x].get_enemy()){
            array[y][x].set_enemy(false);
            array[y][x].set_players_events(nullptr);
        }
        if(player.get_hp() <= 0){
            end = true;
            std::cout<< "Game over";
        }
        if( ((x == length - 1) && (y == height - 1) && (player.get_end())) || player.get_hp() <= 0){
            end = true;
        } 
    }
    void GoUp(){
        array[y][x].cell_reaction();
        y--;
        if(y < 0){
            y = height - 1;
        }
        if(array[y][x].get_wall()){ 
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
        player.set_coords(x, y);

        array[y][x].use(&player);
        if(array[y][x].get_enemy()){
            array[y][x].set_enemy(false);
            array[y][x].set_players_events(nullptr);
        }
        if(player.get_hp() <= 0){
            end = true;
            std::cout<< "Game over";
        }
        if( ((x == length - 1) && (y == height - 1) && (player.get_end())) || player.get_hp() <= 0){
            end = true;
        }
    }
    void GoDown(){
        array[y][x].cell_reaction();
        y++;
        if(y == length){
            y = 0;
        }
        if(array[y][x].get_wall()){
            if(y == 0){// edge
                y = length - 1;
            }
            else{
                y--;
            }// edge               
            array[y][x].cell_reaction();
            return;
        }
        array[y][x].cell_reaction();
        player.set_coords(x, y);

        array[y][x].use(&player);
        if(array[y][x].get_enemy()){
            array[y][x].set_enemy(false);
            array[y][x].set_players_events(nullptr);
        }
        if(player.get_hp() <= 0){
            end = true;
            std::cout<< "Game over";
        }
        if( ((x == length - 1) && (y == height - 1) && (player.get_end())) || player.get_hp() <= 0){
            end = true;
        }
    }
};

class PrintField : public Field{
private:
    using Field::Field;
    
    
public:
    void print(){
        system("clear");
        std::cout << "\n";
        for (int i = 0; i < height; i++){
            for (int j = 0; j < length; j++) {
                if (array[i][j].get_reaction()) {
                    std::cout << "X" << "    ";
                }
                
                else if(array[i][j].get_wall()){
                    std::cout << "#" << "    ";
                }

                else if(array[i][j].get_enemy()){
                    std::cout << "@" << "    ";
                }

                else
                    std::cout << "." << "    ";
            }
            if (i == 0){
                std::cout << "      health == " << player.get_hp();
            }
            if (i == 1){
                std::cout << "      cache == " << player.get_cache();
            }
            if (i == 2){
                std::cout << "      armor == " << player.get_armor();
            }
            std::cout << '\n';
            std::cout << '\n';
        }
        
    }
};

class Controller{
public:
    void move(PrintField field){
        CommandReader read;
        field.print();
        while(read.get_enter() != 'q' && !field.end){
            switch (read.get_enter())
            {
            case 'w':
                field.GoUp();
                field.print();
                break;
            case 's':
                field.GoDown();
                field.print();
                break;
            case 'd':
                field.GoRight();
                field.print();
                break;
            case 'a':
                field.GoLeft();
                field.print();
                break;
            default:
                break;
            }
            read.read();   
        }
    }
};

class Mediator{
    CommandReader read;
    std::set<char> turns = {'a', 's', 'd', 'w'};
    Controller cntrl;
public:
    void recycle(char enter){
        if(turns.find(enter) != turns.end()){
           // cntrl.move(field);
        }
        else{
            std::cout << "Unknow command\n";
        }
    }
};

int main(){
    Controller cntrl;
    PrintField field;
    cntrl.move(field);

    return 0;
}