cmake_minimum_required( VERSION 3.16.3 )
project( 3dGameEngine )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} )

include_directories( "include/" )
file( GLOB SRC_FILES "src/*cpp" )

add_executable( 3dGameEngine ${SRC_FILES} )
