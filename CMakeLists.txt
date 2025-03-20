cmake_minimum_required(VERSION 3.29)
project(rUGP-Fuck)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MFC_FLAG 2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_compile_options(/utf-8)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_AFX_NOFORCE_LIBS)

include_directories("${PROJECT_SOURCE_DIR}/Include")
link_directories("${PROJECT_SOURCE_DIR}/Lib")

add_library(r514783 SHARED plugin.cpp rugp.cpp hook.cpp)
install(TARGETS r514783 DESTINATION Plugins)
