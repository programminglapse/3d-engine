cmake_minimum_required( VERSION 3.16.3 )
project( Engine )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} )

include_directories( "include/" )

set( MAIN_SRC_FILE
	src/main.cpp )
set( GLAD_SRC
	src/glad/glad.c )

file( GLOB SRC_FILES ${MAIN_SRC_FILE} ${GLAD_SRC} )

add_library( Engine SHARED ${SRC_FILES} )

target_link_libraries( Engine glfw ${CMAKE_DL_LIBS} )
target_include_directories( Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ )
