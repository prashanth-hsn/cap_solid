# CMakeList.txt : CMake project for cutplane_mesa, include source and define
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

project ("cutplane_mesa" LANGUAGES CXX C)

find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

link_directories(${CMAKE_SOURCE_DIR}/3rdparty/glfw-3.3.9/bin)


include_directories( 3rdparty/glm-0.9.9.8)
include_directories( 3rdparty/glfw-3.3.9/include )
include_directories( 3rdparty/glad/include )

add_executable (cutplane_mesa 
"src/main.cpp" 
"src/application.h"
"src/application.cpp"
"3rdparty/glad/src/glad.c" )

target_link_libraries(cutplane_mesa  glfw3 ${OPENGL_LIBRARIES})



