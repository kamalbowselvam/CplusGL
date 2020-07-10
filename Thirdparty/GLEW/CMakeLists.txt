cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(GLEW VERSION 3.3.2 LANGUAGES C)


add_library(glew src/glew.c src/glewinfo.c src/visualinfo.c)

target_include_directories(glew
		PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
