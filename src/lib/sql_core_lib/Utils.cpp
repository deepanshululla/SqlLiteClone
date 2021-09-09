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
            if (entry->d_name!="." or entry->d_name!="."){
                list.push_back(entry->d_name);
            }

        }
//        for (const auto & entry : std::filesystem::directory_iterator(directory)){
//            std::cout << entry.path() << std::endl;
//        }

        // delete current and parent directories
//        list.erase(std::find(list.begin(), list.end(), "."));
//        list.erase(std::find(list.begin(), list.end(), ".."));

        closedir(dir);
    }
};


//Utilities