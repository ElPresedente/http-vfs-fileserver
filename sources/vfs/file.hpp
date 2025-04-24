#pragma once
#include <string>
#include <chrono>

namespace fileserver{

    struct File{
        std::string name;
        bool is_directory;
        std::uintmax_t size;
        std::chrono::system_clock::time_point modified;
    };
}