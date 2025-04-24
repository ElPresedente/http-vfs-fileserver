#pragma once
#include <functional>
#include <nlohmann/json.hpp>

namespace fileserver{

    class AuthManager;
    class Server;
    class VfsManager;

    template<typename T_>
    using OptRef = std::optional<std::reference_wrapper<T_>>;

    struct CantOpenFile : std::exception{};

    class Configurator{
    public:
        Configurator( std::string const& cfg_file_path )
            : _cfg_file_path( cfg_file_path )
        {}

        void init_refs( AuthManager& a, Server& s, VfsManager& v ){
            _auth_manager.emplace( a ); _server.emplace( s ); _vfs_manager.emplace( v );
        }

        void read_file();
    
    private:
        std::string _cfg_file_path;
        nlohmann::json _data;
        
        OptRef<AuthManager> _auth_manager;
        OptRef<Server> _server;
        OptRef<VfsManager> _vfs_manager;
    };
}
