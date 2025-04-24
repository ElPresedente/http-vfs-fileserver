#pragma once
#include <string_view>
#include <vector>
#include <vfs/file.hpp>

namespace fileserver{

    class IVfs{
    public:
        IVfs(){}
        virtual std::vector<File> list_files( std::string_view path ) = 0;

        // virtual bool create_directory( std::string_view path );

        // virtual bool delete_file( std::string_view path );

        //etc...
    };
}