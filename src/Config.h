#ifndef SQLLITECLONE_CONFIG_H
#define SQLLITECLONE_CONFIG_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
struct stat st = {0};

struct Config {
    inline std::string get_working_path()
    {
        char temp [ 256 ];
        if ( getcwd(temp, 256) != 0)
            return std::string ( temp );
        int error = errno;
        switch ( error ) {
            // EINVAL can't happen - size argument > 0

            // PATH_MAX includes the terminating nul,
            // so ERANGE should not be returned

            case EACCES:
                throw std::runtime_error("Access denied");

            case ENOMEM:
                // I'm not sure whether this can happen or not
                throw std::runtime_error("Insufficient storage");

            default: {
                std::ostringstream str;
                str << "Unrecognised error" << error;
                throw std::runtime_error(str.str());
            }
        }
    }
    inline std::string get_directory() {
        const char *directory = getenv("DB_DATA");
        if (directory == nullptr) {
            const auto dir = get_working_path()+"/data";
            // create the directory if it doesn't exist
            if (stat(dir.c_str(), &st) == -1) {
                mkdir(dir.c_str(), 0700);
            }
            return get_working_path()+"/data";
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
