/* #include "Controller.h"
#include "PrintField.h" */
#include "../Control/CommandReader.h"
#include "../../Info/InfoLog.h"
#include "../Config/Config.h"
#include "../Config/FileConfig.h"

int main(){

    Config* cfg = new FileConfig("settings.txt");
    cfg->check_and_read();
    
    CommandReader reader(cfg);
    reader.set_level();
    reader.set_output();
    reader.set_difficulty();

    InfoLog* logout_info = new InfoLog(reader.get_outputs(), reader.get_levels());

    reader.begin(logout_info);
    Controller cntrl(logout_info, &reader, reader.get_difficulty(), reader.get_width(), reader.get_height());
    cntrl.start();
    return 0;
}