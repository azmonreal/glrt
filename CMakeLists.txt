cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME GLRT)
project(
  ${PROJECT_NAME}
  VERSION 0.1.0
  DESCRIPTION "OpenGL Rendering Toolkit")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(GLRT STATIC ${SOURCES})

target_include_directories(GLRT PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS}
                                           ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT)

add_subdirectory(${PROJECT_SOURCE_DIR}/examples)
