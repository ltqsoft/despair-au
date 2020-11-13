cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: check if _build-xxxx directory used.

option( USE_SYSTEM_OPENAL "Don't use OpenAL included in this project, already installed from repository" ON )
if( NOT USE_SYSTEM_OPENAL )
    message( FATAL_ERROR "OpenAL not included yet, the developer was lazy!" )
endif()

project(despair-au VERSION 1.0)

add_library( despair-au src/despair-au.cpp )

target_include_directories( despair-au PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    )

add_executable( example examples/example.cpp )

target_include_directories(example PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    )

target_link_libraries( example
    PUBLIC despair-au
    PRIVATE vorbisfile
    PRIVATE vorbis
    PRIVATE ogg
    )
