#pragma once
#include <string_view>
#include <vfs/ivfs.hpp>

namespace fileserver{
    class FilesystemVfs final : public IVfs{
    public:
        FilesystemVfs( std::string root_path )
            : IVfs()
            , root_path( root_path )
        {}

        std::vector<File> list_files( std::string_view path [[maybe_unused]] ) final{
            return {};
        }

    private:
        std::string root_path;
    };
}
