#pragma once
#include <string_view>
#include <vfs/ivfs.hpp>

namespace fileserver{
    class FilesystemVfs final : public IVfs{
    public:
        FilesystemVfs( std::string_view root_path )
            : root( root_path )
        {}


    private:
        std::string root;
    };
}
