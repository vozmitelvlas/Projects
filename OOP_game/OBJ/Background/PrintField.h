#pragma once
#include "Field.h"

class PrintField: public Field{
private:
    using Field::Field;  
public:

    void print();
        
    bool get_end();   
};