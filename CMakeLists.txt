cmake_minimum_required(VERSION 3.18)


#-- Preprocess ----------------------------------------------------------------------------


if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "Binary directory should not be the same as source directory, please specify a different one!" )
endif()

set( OPENAL_LIB_NAME "openal" )

if( WIN32 )
    set( OPENAL_LIB_NAME                "OpenAL32" )
    set( CMAKE_PREFIX_PATH              "C:/dev"    CACHE STRING "Where to find include and lib directory, use if you put all your libraries in same place." )
    set( CMAKE_FIND_LIBRARY_PREFIXES    "C:/dev"    CACHE STRING "Where to find dependeny libraries" )
    set( CMAKE_FIND_LIBRARY_SUFFIXES    ".a"        CACHE STRING "Library extensions" )

    find_library(AL_LIBRARY
        NAMES OPENAL_LIB_NAME
        HINTS "${CMAKE_PREFIX_PATH}/lib"
    )
endif() #WIN32


#-- CMake Options -------------------------------------------------------------------------


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if( WIN32 )
    set( CMAKE_INSTALL_PREFIX "C:/dev" CACHE STRING "Target directory for installation." )
endif() #if(WIN32)

# TODO: check if _build-xxxx directory used.

option( USE_SYSTEM_OPENAL "Don't use OpenAL included in this project, already installed from repository." ON )
if( NOT USE_SYSTEM_OPENAL )
    message( FATAL_ERROR "OpenAL not included yet, the developer was lazy!" )
endif()

# set(SYSTEM_INCLUDE_PATH "What" CACHE STRING "System include path" )
if( WIN32 )
    set( WIN32_SYSTEM_INCLUDE_PATH "C:/dev/include" CACHE STRING "System default include path.")
    set( WIN32_SYSTEM_LIBRARY_PATH "C:/dev/lib" CACHE STRING "System default library path." )
endif()


#-- Project and targets -----------------------------------------------------------------


project(despair-au VERSION 1.0)

if( WIN32 )
    include_directories( ${WIN32_SYSTEM_INCLUDE_PATH} )
    link_directories( ${WIN32_SYSTEM_LIBRARY_PATH} )
endif()


# target/despari-au
add_library( despair-au
    src/despair-au.cpp
    src/despair-au-al-source.cpp
    )

target_include_directories( despair-au
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
    )


# targets/example-program
add_executable( example
    examples/example.cpp
    )

target_include_directories(example PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    )

target_link_libraries( example
    PUBLIC despair-au
    PUBLIC vorbisfile
    PUBLIC vorbis
    PUBLIC ogg
    PUBLIC ${OPENAL_LIB_NAME}
    )


# targets/non-build
add_custom_target( neverbuild SOURCES
    include/despair-au.hpp
    README.md
    )
