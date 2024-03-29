cmake_minimum_required(VERSION 3.18)


#-- Preprocess ----------------------------------------------------------------------------

set( CMAKE_CXX_STANDARD             11              )
set( CMAKE_CXX_STANDARD_REQUIRED    True            )
set( CMAKE_FIND_LIBRARY_PREFIXES    "lib"           )
set( CMAKE_FIND_LIBRARY_SUFFIXES    ".a;.dll.a;.so" )
set( CMAKE_USE_RELATIVE_PATHS       True            )
set_property(GLOBAL PROPERTY USE_FOLDERS True)

set ( DEFAULT_CMAKE_INSTALL_PREFIX_PENGU "/usr/local"   )
set ( DEFAULT_CMAKE_INSTALL_PREFIX_WIN32 "C:/dev"       )

set( DEFAULT_VORBIS_INC_PATH    "" )
set( DEFAULT_OGG_INC_PATH       "" )
set( DEFAULT_OGG_LIB_PATH       "" )
set( DEFAULT_VORBIS_LIB_PATH    "" )
set( DEFAULT_OPENAL_INC_PATH    "" )
set( DEFAULT_OPENAL_LIB_PATH    "" )

if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "Binary directory should not be the same as source directory, please specify a different one!" )
endif()

set( OPENAL_LIB_NAME "openal" )
if( WIN32 )
    set( OPENAL_LIB_NAME "OpenAL32" )
endif() #WIN32

find_library( FIND_OGG_RESULT       "ogg"       NAMES "ogg" "Ogg" "oggstatic"       )
find_library( FIND_VORBIS_RESULT    "vorbis"    NAMES "vorbis" "Vorbis"             )
find_library( FIND_OPENAL_RESULT    "openal"    NAMES "openal" "OpenAL" "OpenAL32"  )


#-- CMake Options -------------------------------------------------------------------------


set ( DEPENDENCY_VORBIS_INC_PATH ${DEFAULT_VORBIS_INC_PATH} CACHE STRING "libvorbis include path" )
set ( DEPENDENCY_VORBIS_LIB_PATH ${DEFAULT_VORBIS_INC_PATH} CACHE STRING "libvorbis library path" )
set ( DEPENDENCY_OGG_INC_PATH ${DEFAULT_OGG_INC_PATH} CACHE STRING "libogg include path" )
set ( DEPENDENCY_OGG_LIB_PATH ${DEFAULT_OGG_INC_PATH} CACHE STRING "libogg library path" )
set ( DEPENDENCY_OPENAL_INC_PATH ${DEFAULT_OPENAL_INC_PATH} CACHE STRING "OpenAL include path" )
set ( DEPENDENCY_OPENAL_LIB_PATH ${DEFAULT_OPENAL_INC_PATH} CACHE STRING "OpenAL library path" )

# set(SYSTEM_INCLUDE_PATH "What" CACHE STRING "System include path" )
if( WIN32 )
    set( WIN32_CENTRALIZED_PACKAGES_PATH "C:/dev" CACHE STRING "If you follow linux library structure, you can specify include/lib path for all of them here." )
endif()

function(dpau_add_exe)
    set( TargetName     ${ARGV0} )
    set( TargetGroup    ${ARGV1} )
    
    set(temp0)
    set(temp1)
    set(temp2)
    cmake_parse_arguments(
        PARSE_ARGV 2 srcFiles "${temp0}" "${temp1}" "${temp2}"
    )

    add_executable( ${TargetName} )
    foreach( arg IN LISTS srcFiles_UNPARSED_ARGUMENTS )
        target_sources( ${TargetName} PUBLIC "${arg}" )
    endforeach()

    target_include_directories( ${TargetName}
        PUBLIC "include"
    )
    target_link_libraries( ${TargetName}
        PUBLIC despair-au
        PUBLIC vorbisfile
        PUBLIC vorbis
        PUBLIC ogg
        PUBLIC ${OPENAL_LIB_NAME}
    )
    if( NOT "${TargetGroup}" STREQUAL "_no_group" )
        set_target_properties( ${TargetName} PROPERTIES FOLDER ${TargetGroup} )
    endif()
endfunction()


#-- Project and targets -----------------------------------------------------------------


project(despair-au VERSION 1.0)

set( GLOBAL_INCLUDE_PATH
    ${DEPENDENCY_VORBIS_INC_PATH}
    ${DEPENDENCY_OGG_INC_PATH}
    ${DEPENDENCY_OPENAL_INC_PATH}
    "${WIN32_CENTRALIZED_PACKAGES_PATH}/include"
    )
set( GLOBAL_LIBRARY_PATH
    ${DEPENDENCY_VORBIS_LIB_PATH}
    ${DEPENDENCY_OGG_LIB_PATH}
    ${DEPENDENCY_OPENAL_LIB_PATH}
    "${WIN32_CENTRALIZED_PACKAGES_PATH}/lib"
    )

include_directories( ${GLOBAL_INCLUDE_PATH} )
link_directories( ${GLOBAL_LIBRARY_PATH} )



# target/despari-au
add_library( despair-au
    "src/despair-au.cc"
    "src/despair-au-al-source.cc"
    "src/m3u.cc"
)
target_precompile_headers( despair-au
    PUBLIC "src/despair-au-pch.hh"
)
target_include_directories( despair-au
    PUBLIC "include/${PROJECT_NAME}"
)


# # targets/example-program
# add_executable( example
#     examples/example.cc
# )
# target_include_directories(example PUBLIC
#     "include"
# )
# target_link_libraries( example
#     PUBLIC despair-au
#     PUBLIC vorbisfile
#     PUBLIC vorbis
#     PUBLIC ogg
#     PUBLIC ${OPENAL_LIB_NAME}
# )
# set_target_properties( example
#     PROPERTIES FOLDER examples
# )
dpau_add_exe( example examples examples/example.cc )


# # targets/example/m3u
# add_executable( eg_m3u
#     examples/eg_m3u.cc
# )
# target_include_directories(eg_m3u PUBLIC
#     "include"
# )
# target_link_libraries( eg_m3u
#     PUBLIC despair-au
#     PUBLIC vorbisfile
#     PUBLIC vorbis
#     PUBLIC ogg
#     PUBLIC ${OPENAL_LIB_NAME}
# )
# set_target_properties( eg_m3u
#     PROPERTIES FOLDER examples
# )
dpau_add_exe( eg_m3u examples examples/eg_m3u.cc )

# targets/non-build
add_custom_target( neverbuild SOURCES
    include/despair-au/despair-au.hh
    README.md
)


#-- Install section ---------------------------------------------------------------------


# empty


#-- Print configure result --------------------------------------------------------------


message( STATUS "Install location: ${CMAKE_INSTALL_PREFIX}" )
message( STATUS "inc-path: ${GLOBAL_INCLUDE_PATH}" )
message( STATUS "lib-path: ${GLOBAL_LIBRARY_PATH}" )
if( WIN32 )
    message( STATUS "win32/inc-path: ${WIN32_CENTRALIZED_INCLUDE_PATH}" )
    message( STATUS "win32/lib-path: ${WIN32_CENTRALIZED_LIBRARY_PATH}" )
endif() #WIN32

#dpau_add_exe(targ name1 name2 name3)
