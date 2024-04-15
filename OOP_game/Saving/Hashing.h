#pragma once
#include "fstream"
#include <iostream>
#include "../Exceptions/FileExp.h"
#include "../Exceptions/LoadExp.h"

class Hash{
private:
public:
    int hash(char c){
        return ((int)c) % 90;
    }

    void make_hash(std::string path){
        std::ifstream file;
        file.open(path, std::ios_base::in);

        if(!file.is_open()){
            throw FileExp("Could not open file [" + path + "]");
        }

        char c; 
        int hash_sum = 0;

        while(file.get(c)){
            hash_sum += hash(c);
        }

        file.close();
        std::ofstream file_out;
        file_out.open(path, std::ios_base::app);
        file_out << '#';
        file_out << hash_sum;
        file_out.close();
    }

    int check_hash(std::string path){

        std::ifstream file;
        file.open(path, std::ios_base::in);

        if(!file.is_open()){
            throw FileExp("Could not open file [ " + path + " ]");
        }

        char c; 
        int hash_sum = 0;
        file.get(c);
        while(c != '#'){
            hash_sum += hash(c);
            file.get(c);
            if(file.eof() || file.fail()){
                throw LoadExp("File [" + path + "] was changed!");
            }
        }
        int old_hash;
        file >> old_hash;
        if(old_hash != hash_sum){
            return -1;
        }
        file.close();
        return 0;
    }
};