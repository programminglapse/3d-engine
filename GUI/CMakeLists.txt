cmake_minimum_required( VERSION 3.16.3 )
project( EngineGUI )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} )

set( INCLUDE_DIRS
	include/
	include/Modules/ )

include_directories( ${INCLUDE_DIRS} )

set( SRC_FILES
	src/CApplication.cpp
	src/main.cpp
	src/Modules/CModuleEditorCamera.cpp )

add_executable( EngineGUI ${SRC_FILES} )
target_link_libraries( EngineGUI Engine )
