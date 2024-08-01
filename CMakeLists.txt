cmake_minimum_required( VERSION 3.16.3 )
project( 3dGameEngine )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} )

include_directories( "include/" )

set( MAIN_SRC_FILE
	src/main.cpp )
set( GLAD_SRC
	src/glad/glad.c )

file( GLOB SRC_FILES ${MAIN_SRC_FILE} ${GLAD_SRC} )

add_executable( 3dGameEngine ${SRC_FILES} )

target_link_libraries( 3dGameEngine glfw ${CMAKE_DL_LIBS} )
