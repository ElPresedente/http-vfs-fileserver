#pragma once
#include <filesystem>
#include <chrono>
#include <vfs/ivfs.hpp>

#include <utility/utility.hpp>

#include <spdlog/spdlog.h>

namespace fileserver{
    class FilesystemVfs final : public IVfs{
    public:
        FilesystemVfs( std::string root_path )
            : IVfs()
            , root_path( root_path )
        {}

        std::vector<File> list_files( std::string path ) final{
            if( path.front() == '/' ){
                path = path.substr( 1 );
            }

            namespace fs = std::filesystem;
            std::vector<File> files;
        
            fs::path full_path = fs::path( root_path ) / path;

            spdlog::info( "VFS path {}" , full_path.string() );
        
            if ( !fs::exists( full_path ) || !fs::is_directory( full_path ))
                return files;
        
            for ( auto&& entry : fs::directory_iterator( full_path )) {
                File file;
                file.name = entry.path().filename().string();
                file.is_directory = entry.is_directory();
        
                if ( !file.is_directory ) {
                    std::error_code ec;
                    file.size = entry.file_size( ec );
                    if ( ec ) file.size = 0;
                } else {
                    file.size = 0;
                }
        
                std::error_code ec;
                auto ftime = entry.last_write_time( ec );
                if ( !ec ) {
                    file.modified = utility::to_system_time( ftime );
                } else {
                    file.modified = std::chrono::system_clock::time_point{};
                }
        
                files.push_back(std::move(file));
            }
        
            return files;
        }

    private:
        std::string root_path;
    };
}
