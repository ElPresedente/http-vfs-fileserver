#include "auth/auth_manager.hpp"
#include <vfs/vfs_manager.hpp>
#include <auth/auth_manager.hpp>
#include <server/server.hpp>


int main(){
    using namespace fileserver;

    AuthManager auth_mgr;

    VfsManager manager{ auth_mgr };



    return 0;
}