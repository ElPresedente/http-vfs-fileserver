#include "spdlog/common.h"
#include <vfs/vfs_manager.hpp>
#include <auth/auth_manager.hpp>
#include <server/server.hpp>
#include <config/configurator.hpp>

#include <spdlog/spdlog.h>
#include <argparse/argparse.hpp>

int main( int argc, const char** argv ){
    using namespace fileserver;

    spdlog::set_level( spdlog::level::trace );

    argparse::ArgumentParser program("http-vfs-fileserver");

    program.add_argument( "-c", "--config" )
        .required()
        .help( "Файл конфигурации сервера" );    
    
    try {
        program.parse_args( argc, argv );
    }
    catch ( std::exception const& err ) {
        spdlog::error( "Неправильные аргументы запуска: {}", err.what() );
        std::cerr << program << std::endl;
        return 1;
    }
        
    std::string config_file = program.get<std::string>( "--config" );

    Configurator conf{ config_file };
    AuthManager auth_mgr;
    VfsManager manager{ auth_mgr };
    Server server{ manager, conf, auth_mgr };

    conf.init_refs( auth_mgr, server, manager );

    conf.read_file();

    return server.run( "0.0.0.0", 8000 );
}