cmake_minimum_required(VERSION 3.20)

project(BookForge
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE BOOKFORGE_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(BookForge
    ${BOOKFORGE_SOURCES}
)

target_include_directories(BookForge
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
