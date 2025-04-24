#include "vfs_manager.hpp"
#include <vfs/filesystem_vfs.hpp>
#include <auth/auth_manager.hpp>

#include <exception>
#include <spdlog/spdlog.h>


namespace fileserver{
    
    VfsManager::VfsManager( AuthManager& auth_manager )
        : _auth_manager( auth_manager )
    {}

    std::shared_ptr<IVfs> VfsManager::get_vfs( std::string const& name, std::string const& auth_header ){
        auto res = _file_systems.find( name );
        if( res == _file_systems.end() ){
            spdlog::trace( "Файловая система {} не найдена", name );
            return nullptr;
        }
        if( _auth_manager.proof_vfs( name, auth_header )){
            return res->second;
        }

        spdlog::trace( "Неправильный ключ" );
        return nullptr;
    }

    bool VfsManager::create_filesystem_vfs( std::string const& name, std::string const& key, std::string const& root_path ){
        auto res = _file_systems.find( name );
        if( res == _file_systems.end() ){
            return false;
        }
        try{
            _file_systems.emplace( std::make_pair( name, new FilesystemVfs( root_path )));

            _auth_manager.register_vfs( name, key );
        }
        catch( std::exception const& e ){
            spdlog::error( "Create filesystem exception {}", e.what() );
            return false;
        }
        return true;
    }
}
