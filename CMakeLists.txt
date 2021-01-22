cmake_minimum_required(VERSION 3.17)

# Set version.
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_MICRO 0)

set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO})

project(Balthyse VERSION ${PROJECT_VERSION})

set(SOVERSION ${VERSION_MAJOR})

# standard install locations
include(GNUInstallDirs)


############################################################################
#       Settings
#


# pic - needed on linux ignored on other platofrms
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# put all runtime targets (exe and dll) into bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# put libraries into lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# archives
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# export all on windows. Ignored on other.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set(CMAKE_VERBOSE_MAKEFILE ON)

# setup some paths that will be used for the INSTALL_RPATH paths on systems that
# support it. Adapt the "ORIGIN" to the APPLE use case
if (APPLE)
    set(base @loader_path)
else ()
    set(base $ORIGIN)
endif ()

file(RELATIVE_PATH INSTALL_RPATH_DIRECTORIES
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        )
# make all shared libraries have the same directory, the bin and the lib dirs in RPATH
set(CMAKE_INSTALL_RPATH ${base} ${base}/${INSTALL_RPATH_DIRECTORIES})

# set default visibility to hidden on all platforms (GCC and Clang default is to show
# while visual studio, the default is hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

############################################################################
#       Options
#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CMAKE_CXX_STANDARD}")
endif ()
set(CXX_STANDARD_REQUIRED ON)


############################################################################
#       include src
#


add_subdirectory(Moonfit)

add_subdirectory(Elfaki2020)


############################################################################
#       tests
#
add_subdirectory(googletest)
add_subdirectory(test)

















