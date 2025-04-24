#pragma once

namespace fileserver{
    
    class VfsManager;
    class Configurator;
    class AuthManager;
    class Server{
    public:
        Server( VfsManager& manager, Configurator& configurator, AuthManager& auth )
            : _manager( manager)
            , _configurator( configurator )
            , _auth_manager( auth )
        {}

        int run();

    private:
        VfsManager& _manager;
        Configurator& _configurator;
        AuthManager& _auth_manager;
    };
}
