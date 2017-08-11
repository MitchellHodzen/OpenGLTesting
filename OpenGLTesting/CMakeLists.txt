cmake_minimum_required(VERSION 3.1)
project(CMakeDemo)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SDL2 REQUIRED COMPONENTS main)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS} ${CMAKE_BINARY_DIR} include)


file(GLOB SOURCES "src/*.cpp" "src/*.c")
add_executable(CMakeDemo ${SOURCES})
target_link_libraries(CMakeDemo ${SDL2_LIBS} dl)

if(WIN32)
	foreach(DLL ${SDL2_DLLS})
		add_custom_command(TARGET CMakeDemo POST_BUILD COMMAND
			${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:CMakeDemo>)
	endforeach()
endif()

#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
#TARGET_LINK_LIBRARIES(cmakeTest ${SDL2 LIBRARIES})
