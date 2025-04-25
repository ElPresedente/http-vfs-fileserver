cmake_minimum_required(VERSION 3.16)
project(HttpFileServer LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включить предупреждения
add_compile_options(-Wall -Wextra -Wpedantic)

# Пути
include_directories(${CMAKE_SOURCE_DIR}/sources)
include_directories(${CMAKE_SOURCE_DIR}/submodules)

# Сабмодули
add_subdirectory(submodules/spdlog)
add_subdirectory(submodules/json)
add_subdirectory(submodules/cpp-httplib)
add_subdirectory(submodules/argparse)

# Собрать все исходники рекурсивно
file(GLOB_RECURSE SOURCE_FILES
    sources/*.cc
    sources/*.cpp
)

# Основной исполняемый файл
add_executable(http_server ${SOURCE_FILES})
target_link_libraries(http_server
    PRIVATE
        spdlog::spdlog
        nlohmann_json::nlohmann_json
        httplib::httplib
        argparse::argparse
)

# Если будут библиотеки — линковать тут
# target_link_libraries(http_server PRIVATE some_library)

# Можно добавить флаг для дебага/релиза
set(CMAKE_BUILD_TYPE Debug)
