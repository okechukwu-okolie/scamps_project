cmake_minimum_required(VERSION 3.10)
project(SCAPMS)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCES 
    src/*.cpp
)

if(WIN32)
    add_executable(SCAPMS WIN32 ${SOURCES})
    target_link_libraries(SCAPMS PRIVATE user32 gdi32)
else()
    message(FATAL_ERROR "SCAPMS currently requires the native Windows GUI API.")
endif()