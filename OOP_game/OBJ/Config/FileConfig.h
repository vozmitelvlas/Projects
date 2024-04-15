#pragma once
#include "Config.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class FileConfig: public Config{
public:
    explicit FileConfig(const std::string& filename);

    void check_and_read() override;

    ~FileConfig() override;

private:
    std::ifstream file;
};