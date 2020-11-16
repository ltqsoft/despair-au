cmake_minimum_required(VERSION 3.18)


#-- Preprocess ----------------------------------------------------------------------------

set( CMAKE_CXX_STANDARD             11              )
set( CMAKE_CXX_STANDARD_REQUIRED    True            )
set( CMAKE_FIND_LIBRARY_PREFIXES    "lib"           )
set( CMAKE_FIND_LIBRARY_SUFFIXES    ".a;.dll.a;.so" )

set ( DEFAULT_CMAKE_INSTALL_PREFIX_PENGU "/usr/local" )
set ( DEFAULT_CMAKE_INSTALL_PREFIX_WIN32 "C:/dev" )

set( DEFAULT_VORBIS_INC_PATH "" )
set( DEFAULT_OGG_INC_PATH "" )
set( DEFAULT_OGG_LIB_PATH "" )
set( DEFAULT_VORBIS_LIB_PATH "" )
set( DEFAULT_OPENAL_INC_PATH "" )
set( DEFAULT_OPENAL_LIB_PATH "" )

if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "Binary directory should not be the same as source directory, please specify a different one!" )
endif()

set( OPENAL_LIB_NAME "openal" )


if( WIN32 )
    set( OPENAL_LIB_NAME "OpenAL32" )

    find_package( ogg REQUIRED                  )
    find_package( vorbis REQUIRED               )
    find_package( ${OPENAL_LIB_NAME} REQUIRED   )
else()
    find_library( FIND_OGG "ogg" NAMES "ogg" "Ogg" "oggstatic")
    find_library( FIND_VORBIS "vorbis" NAMES "vorbis" "Vorbis" )
    find_library( FIND_OPENAL "openal" NAMES "openal" "OpenAL" )
endif() #WIN32


#-- CMake Options -------------------------------------------------------------------------


set( CMAKE_INSTALL_PREFIX ${DEFAULT_CMAKE_INSTALL_PREFIX_PENGU} CACHE STRING "Target directory for installation." )
set ( DEPENDENCY_VORBIS_INC_PATH ${DEFAULT_VORBIS_INC_PATH} CACHE STRING "libvorbis include path" )
set ( DEPENDENCY_VORBIS_LIB_PATH ${DEFAULT_VORBIS_INC_PATH} CACHE STRING "libvorbis library path" )
set ( DEPENDENCY_OGG_INC_PATH ${DEFAULT_OGG_INC_PATH} CACHE STRING "libvorbis include path" )
set ( DEPENDENCY_OGG_LIB_PATH ${DEFAULT_OGG_INC_PATH} CACHE STRING "libvorbis library path" )
set ( DEPENDENCY_OPENAL_INC_PATH ${DEFAULT_OPENAL_INC_PATH} CACHE STRING "libvorbis include path" )
set ( DEPENDENCY_OPENAL_LIB_PATH ${DEFAULT_OPENAL_INC_PATH} CACHE STRING "libvorbis library path" )


# TODO: check if _build-xxxx directory used.

option( USE_SYSTEM_OPENAL "Don't use OpenAL included in this project, already installed from repository." ON )
if( NOT USE_SYSTEM_OPENAL )
    message( FATAL_ERROR "OpenAL not included yet, the developer was lazy!" )
endif()

# set(SYSTEM_INCLUDE_PATH "What" CACHE STRING "System include path" )
if( WIN32 )
    set( WIN32_SYSTEM_INCLUDE_PATH "C:/dev/include" CACHE STRING "System default include path." )
    set( WIN32_SYSTEM_LIBRARY_PATH "C:/dev/lib"     CACHE STRING "System default library path." )
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

message( STATUS "Install location: ${CMAKE_INSTALL_PREFIX}" )
