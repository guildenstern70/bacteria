cmake_minimum_required(VERSION 3.20)
project(bacteria LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

add_executable(bacteria
    src/main.cpp
    src/Game.cpp
    src/Bacteria.cpp
        src/config.h
)

target_include_directories(bacteria PRIVATE
    ${SDL3_INCLUDE_DIRS}
    src
)

target_link_directories(bacteria PRIVATE ${SDL3_LIBRARY_DIRS})
target_link_libraries(bacteria PRIVATE ${SDL3_LIBRARIES})
