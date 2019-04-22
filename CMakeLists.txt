cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)

# Nome do projeto
project(graphODA)
# Versionamento
set (graphODA_VERSION_MAJOR 1)
set (graphODA_VERSION_MINOR 0)

# Headers
include_directories(include)
include_directories(include/display)
include_directories(include/graph)
include_directories(include/vector)

# Dependências
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 COMPONENTS graphics window system REQUIRED)
find_package(TGUI 0.8 REQUIRED)

set(SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/display/GraphDisplay.cpp
        ${PROJECT_SOURCE_DIR}/src/display/Interface.cpp
        ${PROJECT_SOURCE_DIR}/src/graph/Graph.cpp
        ${PROJECT_SOURCE_DIR}/src/vector/Vector.cpp
        ${PROJECT_SOURCE_DIR}/src/main.cpp)
set(ASSET_FILES
        "${PROJECT_SOURCE_DIR}/assets/temas/TransparentGrey.txt"
        "${PROJECT_SOURCE_DIR}/assets/fontes/CONSOLAB.TTF")
set(DESKTOP_FILE "${PROJECT_SOURCE_DIR}/assets/graphODA.desktop")
set(ICON_FILE "${PROJECT_SOURCE_DIR}/assets/graphODA.png")

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(graphODA ${SRC_FILES} ${ASSET_FILES})
target_link_libraries(graphODA tgui sfml-graphics sfml-window sfml-system)

install(TARGETS graphODA DESTINATION bin)
install(FILES ${DESKTOP_FILE} DESTINATION "share/applications")
install(FILES ${ICON_FILE} DESTINATION "share/icons/hicolor/256x256/apps")
install(FILES ${ASSET_FILES} DESTINATION bin/assets)
