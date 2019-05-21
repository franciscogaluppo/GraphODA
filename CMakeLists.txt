cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Escolha o tipo de build (Debug ou Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Nome do projeto
project(graphODA)
# Versionamento
set (graphODA_VERSION_MAJOR 1)
set (graphODA_VERSION_MINOR 0)

# Headers
include_directories(include)
include_directories(include/views)
include_directories(include/models/graph)
include_directories(include/utils)
include_directories(include/controllers/repl)
include_directories(include/models/dataStructures)

## Dependências
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    find_package(TGUI 0.8 REQUIRED)
else()
    # Se estamos rodando localmente para desenvolvimento, relaxamos as dependências
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_debug_packages" ${CMAKE_MODULE_PATH})
    find_package(SFML COMPONENTS graphics window system REQUIRED)
    find_package(TGUI REQUIRED)
endif()

set(SRC_FILES
        "src/views/GraphDisplay.cpp"
        "src/views/GraphCanvas.cpp"
        "src/views/Interface.cpp"
        "src/models/graph/GraphGen.cpp"
        "src/models/graph/Graph.cpp"
        "src/models/graph/Bipartite.cpp"
        "src/models/graph/Chordal.cpp"
        "src/models/graph/Dag.cpp"
        "src/models/graph/Tree.cpp"
        "${PROJECT_SOURCE_DIR}/src/utils/Assets.cpp"
        "src/controllers/repl/Repl.cpp"
        "src/models/dataStructures/Vector.cpp"
        "src/models/dataStructures/DSU.cpp"
        "${PROJECT_SOURCE_DIR}/src/main.cpp")
set(ASSET_FILES
        "${PROJECT_SOURCE_DIR}/assets/TransparentGrey.txt"
        "${PROJECT_SOURCE_DIR}/assets/CONSOLAB.TTF")
set(DESKTOP_FILE "${PROJECT_SOURCE_DIR}/assets/graphODA.desktop")
set(ICON_FILE "${PROJECT_SOURCE_DIR}/assets/graphODA.png")

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(graphODA ${SRC_FILES})
target_link_libraries(graphODA tgui sfml-graphics sfml-window sfml-system)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS graphODA DESTINATION "bin")
    install(FILES ${DESKTOP_FILE} DESTINATION "share/applications")
    install(FILES ${ICON_FILE} DESTINATION "share/icons/hicolor/256x256/apps")
    install(FILES ${ASSET_FILES} DESTINATION "share/graphODA/assets")
else()
   install(TARGETS graphODA DESTINATION "./")
   install(FILES ${ASSET_FILES} DESTINATION "assets")
endif()
