cmake_minimum_required(VERSION 2.8)
project(GraphODA)

# Set versioning
set(GraphODA_VERSION_MAJOR 0)
set(GraphODA_VERSION_MINOR 1)
set(CMAKE_CXX_STANDARD 14)

# SFML deps
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.4 COMPONENTS system graphics REQUIRED)
set(CMAKE_FIND_FRAMEWORK TRUE)

include_directories(src)

add_executable(GraphODA
        src/display/GraphDisplay.cpp
        src/display/Interface.cpp
        src/graph/Graph.cpp
        src/vector/Vector.cpp
        src/main.cpp)
target_link_libraries(GraphODA
        SFML::graphics SFML::audio)