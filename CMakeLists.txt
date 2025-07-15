cmake_minimum_required(VERSION 3.15)
project(lazyfooSDL)

set(CMAKE_CXX_STANDARD 17)

# Update this to the SDL3 path if needed
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

include_directories(${SDL3_INCLUDE_DIRS})
link_directories(${SDL3_LIBRARY_DIRS})

add_executable(lazyfooSDL 03-sdlEvents.cpp)

target_link_libraries(lazyfooSDL ${SDL3_LIBRARIES})