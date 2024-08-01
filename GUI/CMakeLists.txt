cmake_minimum_required( VERSION 3.16.3 )
project( EngineGUI )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} )

include_directories( "include/" )

set( MAIN_SRC_FILE
	src/main.cpp )

file( GLOB SRC_FILES ${MAIN_SRC_FILE} )

add_executable( EngineGUI ${SRC_FILES} )
target_link_libraries( EngineGUI Engine )
