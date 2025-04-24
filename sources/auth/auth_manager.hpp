#pragma once
#include <unordered_map>
#include <string>

namespace fileserver{
    using VfsKeyMap = std::unordered_map<std::string, std::string>;

    class AuthManager{
    public:
        bool register_vfs( std::string const& vfs_name, std::string const& key );
        bool unregister_vfs( std::string const& vfs_name, std::string const& key );
    
    
        bool proof_vfs( std::string const& vfs_name, std::string const& auth_header );


    private:
        VfsKeyMap _vfs_keymap;
    };
}
