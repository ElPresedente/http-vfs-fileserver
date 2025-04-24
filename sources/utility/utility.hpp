#pragma once
#include <chrono>
#include <filesystem>

namespace fileserver::utility{
    inline std::chrono::system_clock::time_point to_system_time( std::filesystem::file_time_type ftime ) {
        return std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
        );
    }
}