cmake_minimum_required( VERSION 3.16.3 )
project( Engine )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} )

set( INCLUDE_DIRS
	include/
	include/Modules/ )

include_directories( ${INCLUDE_DIRS} )

set( SRC_FILES
	src/AApplication.cpp
	src/glad/glad.c
	src/Modules/CModuleWindow.cpp
	src/Modules/CModuleInput.cpp
	src/Modules/CModuleRender.cpp )

add_library( Engine SHARED ${SRC_FILES} )

target_link_libraries( Engine glfw ${CMAKE_DL_LIBS} )
target_include_directories( Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ )
