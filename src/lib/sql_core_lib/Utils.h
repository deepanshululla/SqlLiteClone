#ifndef SQLLITECLONE_UTILS_H
#define SQLLITECLONE_UTILS_H

#include <string>
#include <vector>
#include <iostream>

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <filesystem>


namespace Utilities {
    class Utils {
    public:
        Utils()=delete;
        Utils(const Utils& other)=delete;
        Utils& operator=(const Utils& other)=delete;
        Utils(const Utils&& other)=delete;
        Utils& operator=(const Utils&& other)=delete;
        static void split(std::string s, std::string &delimiter, std::vector<std::string> &list);

        static void getFileNamesFromDirectory(std::vector<std::string> &list, const std::string &directory);
    };
}


#endif //SQLLITECLONE_UTILS_H
