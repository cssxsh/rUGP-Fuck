cmake_minimum_required(VERSION 3.29)
project(rUGP_Fuck)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MFC_FLAG 2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
set(RUGP_GAME_PATH $ENV{RUGP_GAME_PATH})
set(CMAKE_INSTALL_PREFIX "${RUGP_GAME_PATH}/")

add_compile_options(/utf-8)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories("${PROJECT_SOURCE_DIR}/Include")
link_directories("${PROJECT_SOURCE_DIR}/Lib")

add_library(r514783 SHARED plugin.cpp rugp.cpp hook.cpp)
install(TARGETS r514783 DESTINATION Plugins)
