#ifndef SQLLITECLONE_CONFIG_H
#define SQLLITECLONE_CONFIG_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <filesystem>
#include <cstring>


struct Config {
    inline std::string get_directory() {
        const char *directory = getenv("DB_DATA");
        if (directory == nullptr) {
            return std::filesystem::current_path().string()+"/data";
        }
        return directory;
    };
    inline bool use_single_thread() {
        const char *useSingleThread = getenv("USE_SINGLE_THREAD");
        if (useSingleThread == nullptr) {
            return true;
        }
        if (strcmp(useSingleThread, "true") == 0 || strcmp(useSingleThread, "1") == 0) {
            return true;
        }
        return false;
    };
};



#endif //SQLLITECLONE_CONFIG_H
