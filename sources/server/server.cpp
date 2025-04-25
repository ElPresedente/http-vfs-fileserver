#include "server.hpp"
#include <spdlog/spdlog.h>

#include <auth/auth_manager.hpp>
#include <vfs/vfs_manager.hpp>
#include <config/configurator.hpp>


namespace fileserver{
    Server::Server( VfsManager& manager, Configurator& configurator, AuthManager& auth )
        : _vfs_manager( manager)
        , _configurator( configurator )
        , _auth_manager( auth )
    {
        _server.new_task_queue = [] {
            return new httplib::ThreadPool(8);
        };
        setup_routes();
    }

    void Server::setup_routes(){
        _server.Get( R"(/([^/]+)(/.*)?)", [&]( httplib::Request const& req, httplib::Response& res ) {
            std::string vfs_name = req.matches[1].str();
            std::string path = req.matches[2].str();
            if (path.empty()) path = "";
            spdlog::trace( "Запрос на VFS {} по пути {}", vfs_name, path );
    
            auto auth_header = req.get_header_value("X-Auth-Key");
    
            if ( !_auth_manager.proof_vfs( vfs_name, auth_header )) {
                res.status = 403;
                res.set_content(R"({"error":"Forbidden"})", "application/json");
                return;
            }
    
            auto vfs = _vfs_manager.get_vfs(vfs_name, auth_header);
            if ( !vfs ) {
                res.status = 404;
                res.set_content(R"({"error":"VFS not found"})", "application/json");
                return;
            }
    
            auto files = vfs->list_files( path );
    
            nlohmann::json out = nlohmann::json::array();
            for ( size_t i = 0; i < files.size(); ++i ) {
                const auto& f = files[i];
                out.push_back( f );
            }
    
            res.set_content(out.dump(), "application/json");
        });
    }

    int Server::run( std::string const& host, uint16_t port ){
        spdlog::info( "Старт сервера {}:{}", host, port );


        _server.listen( host, port );
        return 0;
    }
}
