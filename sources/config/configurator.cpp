#include "configurator.hpp"
#include "spdlog/spdlog.h"

#include <fstream>

#include <auth/auth_manager.hpp>
#include <stdexcept>
#include <vfs/vfs_manager.hpp>

namespace fileserver{

    void Configurator::read_file(){
        std::ifstream in( _cfg_file_path );
        if (!in.is_open()){
            spdlog::critical( "Ошибка при открытии файла конфигурации" );
            throw CantOpenFile{};
        }
    
        in >> _data;
    
        if (!_data.contains("vfs")) return; // ничего не создаём
    
        for (auto& [name, props] : _data["vfs"].items()) {
            std::string key = props["key"];
            std::string root = props["root"];
            
            _auth_manager->get().register_vfs(name, key);
            _vfs_manager->get().create_filesystem_vfs(name, key, root);
        }
    
        return;
    }

    
}
