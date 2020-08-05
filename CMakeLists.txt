cmake_minimum_required(VERSION 3.10)

project(datasets_generator)
set(root ${PROJECT_SOURCE_DIR})
set(sources src/character_extractor.cpp src/functions_impl.cpp)
set(includes include/character_extractor.hpp include/functions_impl.hpp)
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
set(CMAKE_CXX_STANDARD 17) # use C++14
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)


include_directories(include ${OpenCV_INCLUDE_DIRS} )

add_library(${PROJECT_NAME}_lib ${sources})
target_link_libraries (${PROJECT_NAME}_lib  ${OpenCV_LIBS})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

source_group(TREE ${root} FILES ${sources} ${includes})