project(shapeLib)

cmake_minimum_required(VERSION 2.8)

include(Shapelib.cmake)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Make sure we have C++11 enabled.
# Needed to make sure libraries and executables not built
# through the module system use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SHAPELIB_LIBRARY_NAME})