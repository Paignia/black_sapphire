cmake_minimum_required(VERSION 2.8.12)
project(BlackSapphire)

add_definitions("-std=c++11")

include(build_conan/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

macro(HEADER_DIRECTORIES return_list)
	FILE(GLOB_RECURSE new_list *.h)
	SET(dir_list "")
	FOREACH(file_path ${new_list})
		GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
		SET(dir_list ${dir_list} ${dir_path})
	ENDFOREACH()
	LIST(REMOVE_DUPLICATES dir_list)
	SET(${return_list} ${dir_list})
ENDMACRO()

file(GLOB_RECURSE source_list "./src/*.cpp" "./src/*.hpp" "./src/*.h")
add_executable(black_sapphire ${source_list})

HEADER_DIRECTORIES(INC_DIRS)
include_directories(${INC_DIRS})
conan_target_link_libraries(black_sapphire)
