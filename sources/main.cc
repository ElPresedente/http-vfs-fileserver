#include "auth/auth_manager.hpp"
#include <vfs/vfs_manager.hpp>
#include <auth/auth_manager.hpp>
#include <server/server.hpp>
#include <config/configurator.hpp>

int main(){
    using namespace fileserver;

    Configurator conf{ "config.json" };
    AuthManager auth_mgr;
    VfsManager manager{ auth_mgr };
    Server server{ manager, conf, auth_mgr };

    conf.init_refs( auth_mgr, server, manager );
    return server.run();
}