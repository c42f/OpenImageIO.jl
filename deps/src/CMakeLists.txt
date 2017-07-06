project(JuliaOpenImageIO)

cmake_minimum_required(VERSION 2.8.12)

# Config
set (CMAKE_PREFIX_PATH "/home/cfoster/local/julia-0.6.0-rc2") # FIXME
set (JlCxx_DIR "/home/cfoster/.julia/v0.6/CxxWrap/deps/usr/share/cmake/JlCxx" # FIXME
     CACHE PATH "Location of JlCxx cmake config")
set (OIIO_ROOT "/home/cfoster/src/oiio/dist/linux64" # FIXME
     CACHE PATH "Prefix location of OpenImageIO installation")
set (OIIO_LIBRARY_DIR "${OIIO_ROOT}/lib")

#
set (CMAKE_CXX_FLAGS "-Wall -std=c++11 ${CMAKE_CXX_FLAGS}")

# Find external deps
find_package (JlCxx)
find_library (OIIO_LIBRARY NAMES OpenImageIO PATHS ${OIIO_LIBRARY_DIR} NO_DEFAULT_PATH)

# Linker junk
set (CMAKE_MACOSX_RPATH 1)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_DIR}/../;${OIIO_LIBRARY_DIR}")
# Workaround for a linker error (julia header issue?)
add_definitions (-DJULIA_ENABLE_THREADING)

include_directories ("${OIIO_ROOT}/include")

add_library (JlOpenImageIO SHARED
    typedesc.cpp
    module.cpp
)

target_link_libraries (JlOpenImageIO ${OIIO_LIBRARY} ${CMAKE_DL_LIBS} JlCxx::jlcxx)

install (TARGETS JlOpenImageIO
         RUNTIME DESTINATION "bin"
         LIBRARY DESTINATION "lib")
