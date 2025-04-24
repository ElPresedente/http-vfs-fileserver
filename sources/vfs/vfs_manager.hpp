#pragma once
#include <memory>
#include <string_view>
#include <unordered_map>
#include <vfs/ivfs.hpp>

namespace fileserver{
    class VfsManager{
    public:
        std::shared_ptr<IVfs> get_vfs( std::string name, std::string key );

        bool create_filesystem_vfs( std::string_view root_path, std::string key );

    private:
        std::unordered_map<std::string, std::shared_ptr<IVfs>> _file_systems; 
        std::unordered_map<std::string, std::string>           _vfs_to_key;
    };
}