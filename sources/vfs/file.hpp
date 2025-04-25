#pragma once
#include <string>
#include <chrono>
#include <nlohmann/json.hpp>
#include <utility/utility.hpp>

namespace fileserver{

    struct File{
        std::string name;
        bool is_directory;
        std::uintmax_t size;
        std::chrono::system_clock::time_point modified;
    };

    inline void to_json( nlohmann::json& json, File const& f ){
        json = {
            { "name", f.name },
            { "is_directory", f.is_directory },
            { "size", f.size },
            { "modified", utility::time_point_to_string( f.modified )}
        };
    }
}