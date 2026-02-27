cmake_minimum_required(VERSION 3.10)
project(SoftRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(SoftRenderer src/main.cpp)

target_link_libraries(SoftRenderer sfml-graphics sfml-window sfml-system)
