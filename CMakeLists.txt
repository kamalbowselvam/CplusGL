cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(OpenGLExample)

add_subdirectory(Thirdparty/GLFW)
add_subdirectory(Thirdparty/GLEW)
find_package(OpenGL REQUIRED)
add_executable(OpenGLExample src/main.cpp)
add_compile_options(-Wdeprecated-declarations)
target_link_libraries (OpenGLExample glfw glew "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")


target_include_directories(OpenGLExample PUBLIC ${CMAKE_SOURCE_DIR}/include)