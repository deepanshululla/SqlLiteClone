#include "Config.h"

std::string Config::get_directory() {
    const char *directory = getenv("DB_DATA");
    if (directory == nullptr) {
        return std::filesystem::current_path().string()+"/data";
    }
    return directory;
}

bool Config::use_single_thread() {
    const char *useSingleThread = getenv("USE_SINGLE_THREAD");
    if (useSingleThread == nullptr) {
        return true;
    }
    if (strcmp(useSingleThread, "true") == 0 || strcmp(useSingleThread, "1") == 0) {
        return true;
    }
    return false;
}
