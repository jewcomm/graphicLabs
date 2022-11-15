cmake_minimum_required(VERSION 3.22)
project(laba1graphs)

set(CMAKE_CXX_STANDARD 14)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR E:/SFML/SFML-2.5.1-mingw-64/lib/cmake/SFML/)

find_package(SFML 2.5.1 COMPONENTS system graphics audio network REQUIRED)

include_directories(E:/SFML/SFML-2.5.1-mingw-64/include)

add_executable(laba1graphs main.cpp)
target_link_libraries(laba1graphs sfml-graphics sfml-audio)