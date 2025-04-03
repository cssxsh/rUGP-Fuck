cmake_minimum_required(VERSION 3.29)
project(rUGP-Fuck)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MFC_FLAG 2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR_PLATFORM x86)
set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build)

add_compile_options(/utf-8)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_AFX_NOFORCE_LIBS)
add_definitions(-D_WIN32_WINNT=0x0A00)

find_path(DETOURS_INCLUDE_DIRS "detours/detours.h")
find_library(DETOURS_LIBRARY detours REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

add_library(r514783 SHARED plugin.cpp rugp.cpp hook.cpp)

target_include_directories(r514783 PRIVATE ${DETOURS_INCLUDE_DIRS})
target_link_libraries(r514783 PRIVATE ${DETOURS_LIBRARY})
target_link_libraries(r514783 PRIVATE JsonCpp::JsonCpp)
