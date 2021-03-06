# cmake -DCMAKE_BUILD_TYPE=Debug
# cmake -DCMAKE_BUILD_TYPE=Release
#
# -fconcepts - works only for gcc and should not be used

set(CMAKE_CXX_FLAGS "-std=c++2a -march=native -Wno-sign-compare -Wall -Werror")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "(Clang|AppleClang)")
    string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-private-field -Wno-missing-braces")
    link_libraries(libc++fs.a)
else ()
    link_libraries(stdc++fs.so)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")

macro(set_output_dirs)
    set(BinDir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set(LibDir ${CMAKE_CURRENT_SOURCE_DIR}/lib)

    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BinDir} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LibDir} )
    foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
        string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
        set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BinDir} )
        set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LibDir} )
    endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
endmacro()

include_directories("/usr/local/include")
include_directories("/usr/include")

list(APPEND COIN_LIBS CoinUtils Cbc Clp OsiClp Cgl)