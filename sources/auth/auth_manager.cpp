#include "auth_manager.hpp"

namespace fileserver{
    bool AuthManager::register_vfs( std::string const& vfs_name, std::string const& key ){
        auto res = _vfs_keymap.find( vfs_name );
        if( res == _vfs_keymap.end() ){
            _vfs_keymap.emplace( std::make_pair( vfs_name, key ));
            return true;
        }
        else{
            return false;
        }
    }

    bool AuthManager::unregister_vfs( std::string const& vfs_name ){
        auto res = _vfs_keymap.find( vfs_name );
        if( res == _vfs_keymap.end() ){
            return false;
        }
        else{
            _vfs_keymap.erase( res );
            return true;
        }
    }

    bool AuthManager::proof_vfs( std::string const& vfs_name, std::string const& auth_header ){
        auto res = _vfs_keymap.find( vfs_name );
        if( res == _vfs_keymap.end() ){
            return false;
        }
        else{
            auto&& key = res->second;
            #warning доделать когда придёт пора авторизации
            (void) auth_header;
            (void) key;
            return true;
        }
    }
}
