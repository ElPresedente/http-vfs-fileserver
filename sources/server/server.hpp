#pragma once

#include <cpp-httplib/httplib.h>


namespace fileserver{
    
    class VfsManager;
    class Configurator;
    class AuthManager;
    class Server{
    public:
        Server( VfsManager& manager, Configurator& configurator, AuthManager& auth );

        int run( std::string const& host, uint16_t port );

    private:
        void setup_routes();

        VfsManager& _vfs_manager;
        Configurator& _configurator;
        AuthManager& _auth_manager;

        httplib::Server _server;
    };
}
