#include <cstring>
#include "Utils.h"


namespace Utilities {
    void Utils::split(std::string s, std::string &delimiter, std::vector<std::string> &list) {
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            list.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        list.push_back(s);
    }

    void Utils::getFileNamesFromDirectory(std::vector<std::string> &list, const std::string &directory) {
        struct dirent *entry;
        DIR *dir = opendir(directory.c_str());
        if (dir == NULL) {
            return;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
                list.push_back(entry->d_name);
            }

        }
        closedir(dir);
    }
};


//Utilities