#include "vfs_manager.hpp"

#include <spdlog/spdlog.h>

namespace fileserver{

    std::shared_ptr<IVfs> VfsManager::get_vfs( std::string name, std::string key ){
        auto res = _file_systems.find( name );
        if( res == _file_systems.end() ){
            return nullptr;
        }
        auto key_res = _vfs_to_key.find( name );
        if( key_res == _vfs_to_key.end() ){
            spdlog::error( "Файловая система {} найдена, но её ключ не найден", name );
            return nullptr;
        }
    }


}