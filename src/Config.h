#ifndef SQLLITECLONE_CONFIG_H
#define SQLLITECLONE_CONFIG_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <filesystem>
#include <cstring>


struct Config {
    static std::string get_directory();
    static bool use_single_thread();
};


#endif //SQLLITECLONE_CONFIG_H
