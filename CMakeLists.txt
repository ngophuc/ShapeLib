project(shapeLib)

cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Make sure we have C++11 enabled.
# Needed to make sure libraries and executables not built
# through the module system use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

#Required in shapelib
FIND_PACKAGE(shapelib REQUIRED)
INCLUDE_DIRECTORIES(${shapelib_INCLUDE_DIRS})
#set(GMP_DIR "/usr/local")
#include_directories(${PROJECT_NAME} ${shapelib_DIR}/include)
#link_directories(${PROJECT_NAME} ${shapelib_DIR}/lib)
#find_library(shapelib_LIBRARY NAMES shapelib PATHS "${shapelib_DIR}")

add_definitions(-g)

LINK_DIRECTORIES(${shapelib_LIBRARY_DIRS})
INCLUDE_DIRECTORIES(${shapelib_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${shapelib_LIBRARIES})


