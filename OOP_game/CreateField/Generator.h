#include "../OBJ/Background/Field.h"
#include "../Events/CreateEvent.h"

class Generator{
public:
    virtual PrintField *fill(int height = 10, int width = 10, InfoLog* log_out_info = nullptr, Player* player = nullptr) = 0;
};