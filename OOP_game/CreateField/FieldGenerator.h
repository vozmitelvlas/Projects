#pragma GCC system_header
#include "../CreateField/Generator.h"

template<class... Rules>
class FieldGenerator: public Generator{
public:
    PrintField* fill(int height = 10, int width = 10, InfoLog* log_out_info = nullptr, Player* player = nullptr){
        PrintField* field = new PrintField(height, width, log_out_info, player);
        CreateEvent create_events(field, player);
        field->create_field();

        (Rules()(create_events), ...);
        return field;
    };
};