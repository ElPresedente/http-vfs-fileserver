#pragma once
#include <memory>
#include <unordered_map>
#include <vfs/ivfs.hpp>

namespace fileserver{
    class AuthManager;

    class VfsManager{
    public:
        VfsManager( AuthManager& auth_manager );

        std::shared_ptr<IVfs> get_vfs( std::string const& name, std::string const& key );

        bool create_filesystem_vfs( std::string const& name, std::string const& key, std::string const& root_path );

    private:
        AuthManager& _auth_manager;

        std::unordered_map<std::string, std::shared_ptr<IVfs>> _file_systems;
    };
}